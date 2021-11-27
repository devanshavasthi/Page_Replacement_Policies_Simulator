/*
 * Name: Fifo.cpp
 * Description: Implementation of the first in first out Page Replacement Algorithm
 * Author: Kaustuv
 */
#include "policies.h"
#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;

void printSet(unordered_map<int,string>&fr, int page, bool col){
   // unordered_map<int,string> :: iterator it;
    for(auto it : fr)
        if(page == it.first and col)
            cout<<"\033[0;37m|"<<"\033[0;32m"<<(it.first);
        else if(page == it.first)
            cout<<"\033[0;37m|"<<"\033[0;31m"<<(it.first);
        else
            cout<<"\033[0;37m|"<<"\033[0;37m"<<(it.first);
    cout<<"\033[0;37m|";
}
pair<int,float> fifoPagereplacement(int frames,vector<int>&pageSeq,bool showContent)//number of frames,pages
{
    //create a queue and take pages from the front
    //the time complexity of the code is O(n)
    queue<int> page;
    int miss=0;
    int hit=0;
    unordered_map<int,string> umap;
    int temp;//current pageNumber
    bool col=false;
    for(int p=0;p<pageSeq.size();p++)
    {
        //cin>>temp;
        temp=pageSeq[p];
        if(umap.find(temp)!=umap.end())//if it finds
        {
            hit++;
            col=true;
        }
        else//if it doesnot find
        {
            miss++;
            col=false;
            umap[temp] = "pres";
            //page.push(temp);
            if(page.size()!=frames)
            {
                page.push(temp);//push to the end of the queue
            }
            else{
                //first delete the ele from the map
                umap.erase(page.front());
                page.pop();//first pop the oldest page
                page.push(temp);//then push new page to the end of the queue
            }
        }
        if(showContent)
        {
            cout<<temp<<"--->";
            printSet(umap,temp,col);
            cout<<endl<<endl;
        }
    }
    float Hit_Ratio = (float)hit/(float)(hit+miss);
    if(showContent)
    {
        cout<<endl;
        printf("Hit Ratio: %.2f\n", Hit_Ratio);
    }
    return {frames,Hit_Ratio};
}
       
