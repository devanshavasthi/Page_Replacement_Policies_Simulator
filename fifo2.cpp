/*
 * Name: fifo2.cpp
 * Description: Implementation of the First-In First Out with 2nd chance Page
 *              Frame Replacement Algorithm.
 * Author: kyscg
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

FILE *file;

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

void FIFO2Replacement(int frames, vector<int> &pageSeq)
{
    int chanceBit[2][frames];
    int frameptr = 0, pageptr = 0, misses = 0, flag = 0, load = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < frames; j++)
            chanceBit[i][j] = -7;
    int pageSeqsize = pageSeq.size();
    while (pageptr < pageSeqsize)
    {
        for (int i = 0; i < frames; i++)
        {
            if (chanceBit[0][i] == pageSeq[pageptr])
            {
                chanceBit[1][i] = 1;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            do
            {
                if (chanceBit[1][frameptr] == 0)
                {
                    chanceBit[0][frameptr] = pageSeq[pageptr];
                    chanceBit[1][frameptr] = 0;
                    misses++;
                    load = 1;
                }
                else
                    chanceBit[1][frameptr] = 0;
                frameptr++;
                if (frameptr == frames)
                    frameptr = 0;
            } while (load != 1);
        }
        unordered_set<int> frameSet;
        for (int i = 0; i < frames; i++)
            if (chanceBit[0][i] != -7)
                frameSet.insert(chanceBit[0][i]);
        cout << "\033[0;37m" << pageSeq[pageptr] << "--->";
        printSet(frameSet, pageSeq[pageptr], flag);
        printf("\n\n");
        flag = 0;
        load = 0;
        pageptr++;
    }
    printf("\n");
    int hits = pageSeqsize - misses;
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Hit Ratio: %.2f\n", (float)hits / (float)(hits + misses));
}

int main()
{
    int frames, i = 0;
    int pages[99];

    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    if (frames < 1)
    {
        printf("The number of frames should be greater than 1\n");
        return 0;
    }

    file = fopen("pages.txt", "r");
    while (fscanf(file, "%d", &pages[i]) != EOF)
    {
        i++;
        if (i == 99)
            break;
    }
    fclose(file);
    printf("\n");

    vector<int> pageSeq(pages, pages + i);
    FIFO2Replacement(frames, pageSeq);
    return 0;
}
