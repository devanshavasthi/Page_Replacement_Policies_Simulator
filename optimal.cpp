/*
 * Name: optimal.cpp
 * Description: Implementation of the Optimal Page Replacement Algorithm
 * Author: devanshavasthi
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void indexToReplace(unordered_set<int> &fr, vector<int> &pageSeq, int index){
    // this will return the index of frame that has to become the target.
    unordered_set<int> :: iterator it;
    int longest=index+1;
    unordered_set<int> :: iterator ans = fr.begin();
    for(it=fr.begin(); it!=fr.end(); it++){
        int i;
        int flag = 0;
        for(i=index+1; i<pageSeq.size(); i++){
            if(pageSeq[i] == (*it)){
                flag = 1;
                if(i > longest){
                    ans = it;
                    longest = i;
                }
                break;
            }
        }
        if(!flag){
            fr.erase(it);
            fr.insert(pageSeq[index]);
            return;
        }         
    }
    fr.erase(ans);
    fr.insert(pageSeq[index]);
}

void printSet(unordered_set<int> &fr, int page, bool col){
    unordered_set<int> :: iterator it;
    for(it=fr.begin(); it!=fr.end(); it++)
        if(page == *it and col)
            cout<<"\033[0;37m|"<<"\033[0;32m"<<(*it);
        else if(page == *it)
            cout<<"\033[0;37m|"<<"\033[0;31m"<<(*it);
        else
            cout<<"\033[0;37m|"<<"\033[0;37m"<<(*it);
    cout<<"\033[0;37m|";
}

void optimalReplacement(int frames, vector<int> &pageSeq){
    // creating the set for frames.
    // this will give accesing time of O(1).
    unordered_set<int> fr(frames);
    int hit=0, miss=0;
    // running the optimal page replacement algo for all the pages.
    // time complexity will be O(n).
    bool col;
    for(int i=0; i<pageSeq.size(); i++){
        // frames are empty.
        if(fr.size() < frames){
            col=false;
            miss++;
            fr.insert(pageSeq[i]);
        }
        // page encountered in hit.
        else if(fr.find(pageSeq[i]) != fr.end()){
            col=true;
            hit++;
        }
        // page not found and there is miss.
        else{
            col=false;
            miss++;
            indexToReplace(fr, pageSeq, i);
        }
        cout<<pageSeq[i]<<"--->";
        printSet(fr,pageSeq[i],col);
        cout<<endl<<endl;
    }
    cout<<"Hits: "<<hit<<endl;
    cout<<"Misses: "<<miss<<endl;
}

int main(){
    int frames;
    cin>>frames;
    if(frames == 0)
        return 0;
    vector<int> pageSeq = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
    cout<<endl;
    optimalReplacement(frames,pageSeq);
    return 0;
}