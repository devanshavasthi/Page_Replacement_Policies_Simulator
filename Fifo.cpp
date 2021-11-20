/*
 * Name: Fifo.cpp
 * Description: Implementation of the first in first out Page Replacement Algorithm
 * Author: Kaustuv
 */
#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;
//implement fifo page replacement algorithm
void printQueue(queue<int>page)
{
    while (!page.empty())
    {
        cout<<page.front()<<" ";
        page.pop();
    }
    
}
int fifoPagereplacement(int frames,vector<int>&pageSeq)//number of frames,pages
{
    //create a queue and take pages from the front
    //the time complexity of the code is O(n)
    queue<int> page;
    int pageFault=0;
    unordered_map<int,string> umap;
    int temp;//current pageNumber
    // if(frames==0)//if number of frames=0
    //     return pageSeq;
    for(int p=0;p<pageSeq.size();p++)
    {
        //cin>>temp;
        temp=pageSeq[p];
        if(umap.find(temp)!=umap.end())//if it finds
        {
            //HIT
        }
        else//if it doesnot find
        {
            pageFault++;
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
        cout<<temp<<"--->";
        printQueue(page);
        cout<<endl;
    }
   return pageFault;
// int fifoPagereplacement(int frames,int pageSeq)//number of frames,pages
// {
//     //create a queue and take pages from the front
//     //the time complexity of the code is O(n)
//     queue<int> page;
//     int pageFault=0;
//     unordered_map<int,string> umap;
//     int temp;//current pageNumber
//     if(frames==0)//if number of frames=0
//         return pageSeq;
//     for(int p=0;p<pageSeq;p++)
//     {
//         cin>>temp;
//         if(umap.find(temp)!=umap.end())//if it finds
//         {
//             //HIT
//         }
//         else//if it doesnot find
//         {
//             pageFault++;
//             umap[temp] = "pres";
//             //page.push(temp);
//             if(page.size()!=frames)
//             {
//                 page.push(temp);//push to the end of the queue
//             }
//             else{
//                 //first delete the ele from the map
//                 umap.erase(page.front());
//                 page.pop();//first pop the oldest page
//                 page.push(temp);//then push new page to the end of the queue
//             }
//         }
//         cout<<temp<<"--->";
//         printQueue(page);
//         cout<<endl;
//     }
//    return pageFault;

  

}
int main()
{
    int frames,pageSeq;
    cin>>frames>>pageSeq;//4 21
    //cin>>frames;
    vector<int>pages(pageSeq);//={1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
    int temp;
    for(int i=0;i<pageSeq;i++)
    {
    	cin>>temp;
    	pages[i] = temp;
    }
    //int numPageFaluts = fifoPagereplacement(frames,pageSeq);
    int numPageFaluts = fifoPagereplacement(frames,pages);
    cout<<numPageFaluts<<endl;
}
