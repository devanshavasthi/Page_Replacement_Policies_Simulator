/*
 * Name: clock.cpp
 * Description: Implementation of the Clock Page Replacement Algorithm
 * Author: devanshavasthi
 */

#include <iostream>
#include <vector>
// #include <unordered_set>
using namespace std;

int hits = 0, misses = 0;
int hand = 0;

void indexToReplace(vector <pair<int, bool>> &fr, int frames, vector<int> &pageSeq, int index){
    while (true){
        if(fr[hand].second == false){
            // remove the element and add the new element.
            fr[hand] = {pageSeq[index], true};
            hand = (hand+1) % frames;
            misses++;
            break;
        }
        fr[hand].second = false;
        hand = (hand+1) % frames;
    }
}

bool find(vector <pair<int, bool>> &fr, int num){
    for(int i = 0; i < fr.size(); i++)
        if(fr[i].first == num)
            return true;
    return false;
}

void printSet(vector <pair<int, bool>> &fr, int page, bool col){
    for(int i = 0; i < fr.size(); i++){
        if(page == fr[i].first and col)
            cout<<"\033[0;37m|"<<"\033[0;32m"<<fr[i].first;
        else if(page == fr[i].first)
            cout<<"\033[0;37m|"<<"\033[0;31m"<<fr[i].first;
        else
            cout<<"\033[0;37m|"<<"\033[0;37m"<<fr[i].first;
    }
    cout<<"\033[0;37m|";
}

void clockReplacement(int frames, vector <int> &pageSeq){
    vector <pair<int, bool>> fr;
    bool col;
    int pageSeqSize = pageSeq.size();
    for (int i = 0; i < pageSeqSize; i++){
        int frSize = fr.size();
         if (frSize < frames){
            col = false;
            misses++;
            fr.push_back({pageSeq[i], true});
        }
        else if (find(fr, pageSeq[i])){
            col = true;
            hits++;
        }
        else{
            col = false;
            indexToReplace(fr, frames, pageSeq, i);
        }
        cout << pageSeq[i] << "--->";
        printSet(fr, pageSeq[i], col);
        cout << endl << endl;
    }
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
}

int main(){
    int frames;
    cin >> frames;
    if (frames == 0)
        return 0;
    vector <int> pageSeq = {0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4};
    cout << endl;
    clockReplacement(frames, pageSeq);
    return 0;
}