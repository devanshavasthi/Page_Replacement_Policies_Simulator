/*
 * Name: NFU.cpp
 * Description: Implementation of the Not Frequently used Page Replacement Algorithm
 * Author: Kaustuv
 */
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
void display(vector<int>dis)
{
    for(int i=0;i<dis.size();i++)
        cout<<dis[i]<<" ";
    cout<<endl;
}
int nfuPageReplacement(int frames,vector<int>page)
{
    unordered_map<int,int>umap;
    vector<int>q;
    int pagefault=0;
    for(int i=0;i<page.size();i++)
    {
        if(umap.find(page[i])==umap.end())//not find
        {
            pagefault++;
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
        }
        cout<<page[i]<<"--->";
        display(q);
    }
    return pagefault;
}
int main()
{
    int frames,pageSeq;
    cin>>frames>>pageSeq;//4 21
    //cin>>frames;
    vector<int>pages(pageSeq);//={7,0,1,2,0,3,0,4,2,3,0,3,2};
    int temp;
    for(int i=0;i<pageSeq;i++)
    {
    	cin>>temp;
    	pages[i] = temp;
    }
    //int numPageFaluts = fifoPagereplacement(frames,pageSeq);
    int numPageFaluts = nfuPageReplacement(frames,pages);
    cout<<numPageFaluts<<endl;
}
