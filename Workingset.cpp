#include<iostream>
#include<vector>
#include<unordered_map>
#include<deque>
using namespace std;
void printQueue(deque<char>val)
{
    unordered_map<char,string>umap1;
    string sval="";
    while(!val.empty())
    {
        if(umap1.find(val.back()) == umap1.end())//not found
        {
            //not going to print the duplicate values in the queue
            umap1[val.back()]="pres";
            sval=sval+val.back();
            val.pop_back();
        }
        else{
            val.pop_back();
        }
        
    }
    //reversing the string to print the present pages in the working set
    for(int i=sval.size()-1;i>=0;i--)
    {
        cout<<sval[i];
    }
    cout<<endl;
}
int workingset(vector<char>val,int ws)
{
    unordered_map<char,int>umap1;
    deque<char> q;
    int hit=0;
    for(int i=0;i<val.size();i++)
    {
        if(q.size()!=ws)
        {
            if(umap1.find(val[i])!=umap1.end())//if found
            {
                umap1[val[i]]++;
                hit++;
                
            }
            else{
                umap1[val[i]]=1;
                q.push_back(val[i]);
                //print the queue
                cout<<val[i]<<"---->";
                printQueue(q);
            }
        }
        else{
            if(umap1.find(val[i])!=umap1.end())//if found
            {
                hit++;
                umap1[val[i]]++;
                umap1[q.front()]--;
                if(umap1[q.front()] == 0)
                {
                    umap1.erase(q.front());
                }
                q.pop_front();
                q.push_back(val[i]);
                //print the queue
                cout<<val[i]<<"---->";
                printQueue(q);

            }
            else{
                umap1[val[i]]=1;
                umap1[q.front()]--;
                if(umap1[q.front()] == 0)
                {
                    umap1.erase(q.front());
                }
                q.pop_front();
                q.push_back(val[i]);
                //print the queue
                cout<<val[i]<<"---->";
                printQueue(q);
            }
           
        }
    }
    return hit;

}
int main()
{
    vector<char>val={'e','d','a','c','c','d','b','c','e','c','e','a','b'};
    int windowsize=4;
    int hit = workingset(val,windowsize);
    cout<<"number of hits:"<<hit<<endl;
    return 0;
}