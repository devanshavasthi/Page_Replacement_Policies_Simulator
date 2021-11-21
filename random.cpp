/*
 * Name: random.cpp
 * Description: Implementation of the Random Page Frame Replacement Algorithm
 * Author: kyscg
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void replaceIndex(unordered_set<int> &frameSet, vector<int> &pageSeq, int index)
{
    srand(time(0));
    int randomIndex = rand() % frameSet.size();
    int i = 0;
    for (unordered_set<int>::iterator it = frameSet.begin(); it != frameSet.end(); ++it)
    {
        if (i == randomIndex)
        {
            frameSet.erase(*it);
            frameSet.insert(pageSeq[index]);
            break;
        }
        i++;
    }
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

void randomReplacement(int frames, vector<int> &pageSeq)
{
    unordered_set<int> frameSet;
    int hits = 0, misses = 0;
    bool col;
    int pageSeqSize = pageSeq.size();
    for (int i = 0; i < pageSeqSize; i++)
    {
        int frameSetSize = frameSet.size();
        if (frameSetSize < frames)
        {
            col = false;
            misses++;
            frameSet.insert(pageSeq[i]);
        }
        else if (frameSet.find(pageSeq[i]) != frameSet.end())
        {
            hits++;
            col = true;
        }
        else
        {
            col = false;
            misses++;
            replaceIndex(frameSet, pageSeq, i);
        }
        cout << "\033[0;37m" << pageSeq[i] << "--->";
        printSet(frameSet, pageSeq[i], col);
        printf("\n\n");
    }
    printf("\n");
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Hit Ratio: %.2f\n", (float)hits / (float)(hits + misses));
}

int main()
{
    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    if (frames < 1)
    {
        printf("The number of frames should be greater than 1\n");
        return 0;
    }
    vector<int> pageSeq = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
    printf("\n");
    randomReplacement(frames, pageSeq);
    return 0;
}
