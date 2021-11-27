/*
 * Name: clock.cpp
 * Description: Implementation of the Clock Page Replacement Algorithm
 * Author: devanshavasthi
 */

#include "policies.h"
#include <climits>

// void printSet(unordered_set<int> &frameSet, int page, bool col)
// {
//     unordered_set<int>::iterator it;
//     for (it = frameSet.begin(); it != frameSet.end(); it++)
//         if (page == *it and col)
//             cout << "\033[0;37m|"
//                  << "\033[0;32m" << (*it);
//         else if (page == *it)
//             cout << "\033[0;37m|"
//                  << "\033[0;31m" << (*it);
//         else
//             cout << "\033[0;37m|"
//                  << "\033[0;37m" << (*it);
//     cout << "\033[0;37m|";
// }

pair<int, float> clockReplacement(int n, vector<int> &pageSeq, bool showContent)
{
    int frames[n], use[n], fault, locat, found, load, i, j;
    for (i = 0; i < n; i++)
    { /* Initialize all array elements to 0 */
        frames[i] = INT_MIN;
        use[i] = 0;
    }
    fault = 0;
    locat = 0;
    int pageseqsize = pageSeq.size();
    for (i = 0; i < pageseqsize; i++)
    {
        found = 0;
        for (j = 0; j < n; j++)
        {
            if (pageSeq[i] == frames[j])
            {
                use[j] = 1;
                found = 1;
            }
        }
        if (found == 0)
        {
            do
            { /* if bit is 0 or NULL, load in page */
                if (use[locat] == 0)
                {
                    frames[locat] = pageSeq[i];
                    use[locat] = 1;
                    load = 1;
                    fault++;
                }
                else
                { /* reset use bit */
                    use[locat] = 0;
                }
                locat++; /* Move pointer */

                if (locat == n)
                    locat = 0;
            } while (load != 1);
        }
        unordered_set<int> frameSet;
        for (int k = 0; k < n; k++)
            if (frames[k] != INT_MIN)
                frameSet.insert(frames[k]);
        if (showContent)
        {
            cout << pageSeq[i] << "--->";
            printSet(frameSet, pageSeq[i], found);
            cout << endl
                 << endl;
        }

        load = 0;
        found = 0;
    }

    float hits = (float)pageseqsize - fault;
    float Hit_Ratio = (float)hits / (float)(hits + fault);
    if (showContent)
    {
        cout << endl;
        printf("Hit Ratio: %.2f\n", Hit_Ratio);
    }
    return {n, Hit_Ratio};
}

// int main()
// {
//     int frames;
//     cin >> frames;
//     if (frames == 0)
//         return 0;
//     vector<int> pageSeq = {0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4};
//     cout << endl;
//     clockReplacement(frames, pageSeq, 1);
//     return 0;
// }