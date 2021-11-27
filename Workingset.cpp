#include "policies.h"
#include<iostream>
#include<vector>
#include<unordered_map>
#include<deque>
using namespace std;
void printSet(deque<int>val,int page,bool col)
{
    unordered_map<char,string>umap1;
    vector<int> sval;
    while(!val.empty())
    {
        if(umap1.find(val.back()) == umap1.end())//not found
        {
            //not going to print the duplicate values in the queue
            umap1[val.back()]="pres";
            sval.push_back(val.back());
            val.pop_back();
        }
        else{
            val.pop_back();
        }
        
    }
    //reversing the string to print the present pages in the working set
    for(int i=sval.size()-1;i>=0;i--)
    {
        cout<<"|"<<sval[i];
    }
    cout<<"|";
}
pair<int,float> workingset(vector<int>val,int ws,bool showContent)
{
    unordered_map<int,int>umap1;
    deque<int> q;
    int hit=0;
    int miss=0;
    bool col=false;
    for(int i=0;i<val.size();i++)
    {
        if(q.size()!=ws)
        {
            if(umap1.find(val[i])!=umap1.end())//if found
            {
                umap1[val[i]]++;
                hit++;
                col=true;
                
            }
            else{
                umap1[val[i]]=1;
                q.push_back(val[i]);
                miss++;
                if(showContent)
                {
                    cout<<val[i]<<"--->";
                    printSet(q,val[i],col);
                    cout<<endl<<endl;
                }
                // cout<<val[i]<<"---->";
                // printQueue(q);
            }
        }
        else{
            if(umap1.find(val[i])!=umap1.end())//if found
            {
                hit++;
                col=true;
                umap1[val[i]]++;
                umap1[q.front()]--;
                if(umap1[q.front()] == 0)
                {
                    umap1.erase(q.front());
                }
                q.pop_front();
                q.push_back(val[i]);
                //print the queue
                if(showContent)
                {
                    cout<<val[i]<<"--->";
                    printSet(q,val[i],col);
                    cout<<endl<<endl;
                }
                // cout<<val[i]<<"---->";
                // printQueue(q);

            }
            else{
                miss++;
                col=false;
                umap1[val[i]]=1;
                umap1[q.front()]--;
                if(umap1[q.front()] == 0)
                {
                    umap1.erase(q.front());
                }
                q.pop_front();
                q.push_back(val[i]);
                if(showContent)
                {
                    cout<<val[i]<<"--->";
                    printSet(q,val[i],col);
                    cout<<endl<<endl;
                }
            }
           
        }
    }
    float Hit_Ratio = (float)hit/(float)(hit+miss);
    if(showContent)
    {
        cout<<endl;
        printf("Hit Ratio: %.2f\n", Hit_Ratio);
    }
    return {ws,Hit_Ratio};

}
// int main()
// {
//     //vector<int>val={'e','d','a','c','c','d','b','c','e','c','e','a','b'};
// vector<int>val={1,2,3,4,4,2,5,4,1,4,1,3,5};
// int windowsize=4;
//  pair<int,float>x = workingset(val,windowsize,false);
// cout<<"number of hits:"<<x.second<<endl;
// return 0;
// }