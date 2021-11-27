/*
 * Name: policies.h
 * Description: Header file for page replacement policies
 * Author: devanshavasthi
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>
using namespace std;

void policy_menu();
void run_all();

pair<int, float> randomReplacement(int frames, vector<int> &pageSeq, bool showContent);
pair<int, float> optimalReplacement(int frames, vector<int> &pageSeq, bool showContent);
pair<int,float> nru(int frames, vector<int> &pages_input, bool showContent);
pair<int, float> fifoPagereplacement(int frames,vector<int>&pageSeq, bool showContent);
pair<int, float> FIFO2Replacement(int frames, vector<int> &pageSeq, bool showContent);
pair<int, float> clockReplacement(int frames, vector <int> &pageSeq, bool showContent);
pair<int,float> lru(vector<int> &v, int frames, bool showContent);
pair<int, float> nfuPageReplacement(int frames,vector<int>page, bool showContent);
pair<int,float> workingset(vector<int>val,int ws,bool showContent);
pair<int,float> aging(int frames, vector<int> &v, bool showContent);
pair<int, float> wsclock(int frames, vector<int> &pageSeq, bool showContent);

void printSet(unordered_set<int> &frameSet, int page, bool col);
void printSet(vector<int> &vec, int hit, int miss, int num);