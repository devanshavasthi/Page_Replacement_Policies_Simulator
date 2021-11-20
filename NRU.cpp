#include <bits/stdc++.h>
#include <iostream>

using namespace std;


void print_stuff(vector<int> &vec, int hit, int miss, int num)
{
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i] == num && hit == 1)
        {
            cout<<"\033[0;37m|"<<"\033[0;32m"<<vec[i]<<" ";
        }

        else if(vec[i] == num && miss ==1)
        {
            cout<<"\033[0;37m|"<<"\033[0;31m"<<vec[i]<<" ";
        }

        else
        cout<<"\033[0;37m|"<<"\033[0;37m"<<vec[i]<<" ";
    }
    cout<<"\033[0;37m|";
}

void push_to(vector<int> &vec, int to_add, int to_remove)
{
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i] == to_remove)
        {
            // vec.erase(vec.begin() + i);
            vec[i] = to_add;
            return;
        }
    }
}

struct bits
{
    /* data */
    int reference;
    int modified;
};

void nru(int frames, vector<int> &pages_input)
{
    
    unordered_map<int,bits> nru_map;
    // unordered_map<int, int> frame;
    vector<int> vec;
    vector<int> p_vec;
    int page_faluts=0;
    float Hit_ratio;
    float Miss_ratio;
    int hit,miss;

    for(int i=0;i<pages_input.size();i++)
    {
        hit=0,miss=0;
        if(nru_map.find(pages_input[i]) == nru_map.end() && frames > 0)
        {
            frames--;
            // if(i%2)
            // nru_map.insert({pages_input[i],{0,1}});
            // else
            nru_map.insert({pages_input[i],{1,0}});
            vec.push_back(pages_input[i]);
            page_faluts++;
            p_vec.push_back(pages_input[i]);
            miss=1;
        }

        else if(nru_map.find(pages_input[i]) == nru_map.end())
        {
            miss=1;
            int x,flag=0,ind,flag2=0;
            for(int j=0;j<vec.size();j++) // iterate over vector
            {
                if(nru_map[vec[j]].modified == 0 && nru_map[vec[j]].reference == 0)
                {
                    x = vec[j];
                    ind = j;
                    break;
                }

                else if(nru_map[vec[j]].modified == 1 && nru_map[vec[j]].reference == 0 && flag==0)
                {
                    x = vec[j];
                    flag =1;
                    ind = j;
                    //break;
                }

                else if(nru_map[vec[j]].modified == 0 && nru_map[vec[j]].reference == 1 && flag == 0 && flag2==0)
                {
                    x = vec[j];
                    ind = j;
                    flag2=1;
                    //break;
                }

                else if(flag == 0 && flag2==0){
                ind = j;
                x = vec[j];
                }
            }

            nru_map.erase(x); // change in vector too
            // nru_map[pages_input[i]].reference=0;
            // nru_map[pages_input[i]].modified=0;
            vec.erase(vec.begin()+ind);
            nru_map.insert({pages_input[i],{1,0}});
            // for(auto it : nru_map)
            // {
            //     cout<<it.first;
            // }
            // cout<<endl;
            vec.push_back(pages_input[i]);
            push_to(p_vec,pages_input[i],x);
            page_faluts++;
        }

        else
        {
            hit=1;
            nru_map[pages_input[i]].reference = 1;
            for(int ind=0;ind<vec.size();ind++)
            {
                if(vec[ind] == pages_input[i])
                {
                    vec.erase(vec.begin()+ind);
                    vec.push_back(pages_input[i]);
                    break;
                }
            }
        }

        cout<<pages_input[i]<<"--->";
        print_stuff(p_vec,hit,miss,pages_input[i]);
        cout<<endl<<endl;

    }

    Miss_ratio = (float)page_faluts/(float)pages_input.size();
    Hit_ratio = 1.0-Miss_ratio;
    cout<<"Page fault: "<<page_faluts<<endl;
    cout<<"Hit ratio: "<<fixed << setprecision(2)<<Hit_ratio<<endl;
    cout<<"Miss ratio: "<<fixed << setprecision(2)<<Miss_ratio<<endl;
}

int main()
{
    int frames,num_pages;
    cout<<"Frames: ";
    cin>>frames;
    cout<<"Number of pages: ";
    cin>>num_pages;
    vector<int> pages_input(num_pages);
    
    for(int i=0;i<num_pages;i++)
    cin>>pages_input[i];

    nru(frames, pages_input);
}