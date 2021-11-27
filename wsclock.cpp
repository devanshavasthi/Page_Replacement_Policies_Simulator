/*
 * Name: wsclock.cpp
 * Description: Implementation of the Working Set Clock Frame Replacement
 *              Algorithm.
 * Author: kyscg
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>
#include <sys/time.h>
using namespace std;

FILE *file;

// Threshold for WSClock
unsigned long tt = 100;

unsigned long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec / 1000000 + tv.tv_usec;
}

void printSet(unordered_set<int> &frameSet, int page, bool col)
{
    unordered_set<int>::iterator it;
    for (it = frameSet.begin(); it != frameSet.end(); it++)
        if (page == *it and col)
            cout << "\033[0;37m|"
                 << "\033[0;32m" << (*it);
        else if (page == *it)
            cout << "\033[0;37m|"
                 << "\033[0;31m" << (*it);
        else
            cout << "\033[0;37m|"
                 << "\033[0;37m" << (*it);
    cout << "\033[0;37m|";
}

void wsclock(int frames, vector<int> &pageSeq)
{
    int chanceBit[3][frames];
    int frameptr = 0, pageptr = 0, misses = 0, flag = 0, load = 0;

    // initialize all frames to a negative number (to allow for 0's
    // to be used in input)
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < frames; j++)
            chanceBit[i][j] = INT_MIN;
    // Set all chance bits to 0
    for (int i = 1; i < 2; i++)
        for (int j = 0; j < frames; j++)
            chanceBit[i][j] = 0;
    // Set all access time bits to 0
    for (int i = 2; i < 3; i++)
        for (int j = 0; j < frames; j++)
            chanceBit[i][j] = 0;

    int pageSeqsize = pageSeq.size();
    while (pageptr < pageSeqsize)
    {
        // Check if the page is already in the frame set and set the toggle
        // bit to 1 if it is. Also set the last access time.
        for (int i = 0; i < frames; i++)
        {
            if (chanceBit[0][i] == pageSeq[pageptr])
            {
                chanceBit[1][i] = 1;
                // Set access time bit to current time
                chanceBit[2][i] = getCurrentTime();
                flag = 1;
            }
        }
        if (flag == 0)
        {
            // We only move to the next frame if there is no load in the
            // current iteration.
            do
            {
                // Loads the page into the frames and sets the toggle bit to 0.
                if (chanceBit[1][frameptr] == 0)
                {
                    if (pageptr > frames - 1)
                    {
                        // We check if the page age has crossed the threshold
                        // and if so, we load the page into the frame.
                        unsigned long timern = getCurrentTime();
                        if (timern - chanceBit[2][frameptr] > tt)
                        {
                            chanceBit[0][frameptr] = pageSeq[pageptr];
                            chanceBit[1][frameptr] = 0;
                            misses++;
                            load = 1;
                        }
                    }
                    else
                    {
                        chanceBit[0][frameptr] = pageSeq[pageptr];
                        chanceBit[1][frameptr] = 0;
                        misses++;
                        load = 1;
                    }
                }
                // Invoke a chance and flip the bit back to 0. Also set the
                // access time.
                else
                {
                    chanceBit[1][frameptr] = 0;
                    chanceBit[2][frameptr] = getCurrentTime();
                }
                frameptr++;

                // Cycle back to the beginning
                if (frameptr == frames)
                    frameptr = 0;
            } while (load != 1);
        }

        // Adding frames to a set to print later
        unordered_set<int> frameSet;
        for (int i = 0; i < frames; i++)
            if (chanceBit[0][i] != INT_MIN)
                frameSet.insert(chanceBit[0][i]);

        // Print the set
        cout << "\033[0;37m" << pageSeq[pageptr] << "--->";
        printSet(frameSet, pageSeq[pageptr], flag);
        printf("\n\n");
        flag = 0;
        load = 0;
        pageptr++;
    }

    // Stats
    printf("\n");
    int hits = pageSeqsize - misses;
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Swaps: %d\n", misses - frames);
    printf("Hit Ratio: %.2f\n", (float)hits / (float)(hits + misses));
}

int main()
{
    file = fopen("pages.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    int frames = 0;
    fscanf(file, "%d", &frames);
    vector<int> pageSeq;
    int page;
    while (fscanf(file, "%d", &page) != EOF)
        pageSeq.push_back(page);
    fclose(file);

    if (frames < 1)
    {
        printf("Error: Number of frames must atleast equal 1\n");
        return 1;
    }

    wsclock(frames, pageSeq);
    return 0;
}