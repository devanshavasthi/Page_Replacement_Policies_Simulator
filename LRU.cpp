#include "policies.h"
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void replace_frame(int to_replace,int with,vector<int> &s)
{
    for(int i=0;i<s.size();i++)
    {
        if(s[i] == to_replace)
        {
            s[i] = with;
        }
    }
}


// void printSet(vector<int> &vec, int hit, int miss, int num)
// {
//     for(int i=0;i<vec.size();i++)
//     {
//         if(vec[i] == num && hit == 1)
//         {
//             cout<<"\033[0;37m|"<<"\033[0;32m"<<vec[i]<<" ";
//         }

//         else if(vec[i] == num && miss ==1)
//         {
//             cout<<"\033[0;37m|"<<"\033[0;31m"<<vec[i]<<" ";
//         }

//         else
//         cout<<"\033[0;37m|"<<"\033[0;37m"<<vec[i]<<" ";
//     }
//     cout<<"\033[0;37m|";
// }


pair<int,float> lru(vector<int> &v, int frames, bool showContent)
{
    unordered_map<int,int> lrused;
    // unordered_set<int>  pages;
    vector<int> to_print;

    int page_fault=0;

    int index=0;
    while(index < v.size())
    {
        int hit=0,miss=0;
        if(frames > lrused.size())
        {
            if (lrused.find(v[index])==lrused.end())
            {
                lrused.insert({v[index],index});
                page_fault++;
                to_print.push_back(v[index]);
                miss=1;
            }

            else{
            hit=1;
            lrused[v[index]] = index;
            }
            // frames--;
        }

        else
        {
            int temp=2147483647;
            int first;
            if (lrused.find(v[index]) == lrused.end())
            {
                for(auto it : lrused)
                {
                    if(it.second < temp){
                    temp = it.second;
                    first = it.first;
                    }
                }

                replace_frame(first,v[index],to_print);

                lrused.erase(first);
                // pages.erase(first);

                // pages.insert(v[index]);

                page_fault++;

                lrused.insert({v[index],index});
                miss=1;
            }

            else{
            hit=1;
            lrused[v[index]] = index;
            }
        }

        // cout<<v[index]<<"--->";
        // print_stuff(to_print,hit,miss,v[index]);
        // cout<<endl<<endl;
        if(showContent)
        {
        cout<<v[index]<<"--->";
        printSet(to_print,hit,miss,v[index]);
        cout<<endl<<endl;
        }
        index++;
    }

    int hit2 = v.size() - page_fault;
    float Hit_Ratio = (float)hit2/(float)(hit2+page_fault);
    if(showContent)
    {
        cout<<endl;
        printf("Hit Ratio: %.2f\n", Hit_Ratio);
    }

    // float Hit_Ratio = (float)hit/(float)(hit+miss);
    // printf("Hit Ratio: %.2f\n", Hit_Ratio);
    // cout<<page_fault;
    return {frames, Hit_Ratio};
}



// int main()
// {
//     vector<int> v = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
//     int frames;
//     cout<<"Frames: ";
//     cin>>frames;
//     pair<int,int>x = lru(v,frames,false);
// }