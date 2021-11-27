/*
 * Name: NFU.cpp
 * Description: Implementation of the Not Frequently used Page Replacement Algorithm
 * Author: Kaustuv
 */
#include "policies.h"
#include<iostream>
#include<queue>
#include<unordered_map>
#include<climits>
using namespace std;
void findleastCounter(unordered_map<int,int>&umap,vector<int>&q,int page)
{
    int min=INT_MAX;
    for(auto m:umap)
    {
        if(m.second < min)
        {
            min = m.second;
        }
    }
   // cout<<"minfreq is"<<min<<endl;
    //now see if we have multiple min fre
    vector<int>minfrq;
    for(auto m:umap)
    {
        if(m.second==min)
        {
            minfrq.push_back(m.first);//page number whose fre is same
        }
    }
    //from that page number which is the first
    int minStore=minfrq.size()+q.size();
    for(int i=0;i<minfrq.size();i++)
    {
        for(int j=0;j<q.size();j++)
        {
            if(minfrq[i]==q[j])
            {
                if(j<minStore)
                    minStore = j;
                break;
            }
            else{
                if(j>minStore)
                    break;
            }
        }
    }
   // cout<<"delete index"<<minStore<<endl;
    //then erase it from the vector and delete it from map also
    umap.erase(q[minStore]);
    q.erase(q.begin()+minStore);
    umap[page]=1;//include that new page in the map
    q.push_back(page);//push the page to the queue
}
void printSet(unordered_map<int,int>&fr, int page, bool col){
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
pair<int,float> nfuPageReplacement(int frames,vector<int>page,bool showContent)
{
    unordered_map<int,int>umap;
    vector<int>q;
    int miss=0;
    int hit=0;
    bool col=true;
    for(int i=0;i<page.size();i++)
    {
        if(umap.find(page[i])==umap.end())//not find
        {
            miss++;
            col=false;
            if(q.size()!=frames)
            {
                q.push_back(page[i]);
                umap[page[i]]=1;
            }
            else{
                //first find the least counter and replace
                findleastCounter(umap,q,page[i]);
            }
            
        }
        else{
            umap[page[i]]++;//if finds increment the counter by one
            hit++;
            col=true;
        }
        if(showContent)
        {
            cout<<page[i]<<"--->";
            printSet(umap,page[i],col);
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
