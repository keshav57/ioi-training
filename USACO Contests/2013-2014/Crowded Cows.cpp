/*
 Created By: Malvika Joshi
 Problem: Crowded Cows (November-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=344
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <numeric>
#include <iostream>

#define MAXN 500010

using namespace std;


int crowded[MAXN];
pair<int,int> det[MAXN];

set<pair<int,int > > max_height;


int N,D;

void init(){

	int i,j;

	sort(det,det+N);

	i = j = 0;

	while(i < N){
		while(det[j].first+D < det[i].first && j < i){
			max_height.erase(make_pair(det[j].second,j));
			++j;
		}
		if(!max_height.empty() && max_height.rbegin()->first >= det[i].second*2) crowded[i] = 1;
		max_height.insert(make_pair(det[i].second,i));
		++i;
	}

	i = N-1,j = N-1;

	max_height.clear();
	while(i >= 0){
		while(det[j].first-D > det[i].first && j > i){
			max_height.erase(make_pair(det[j].second,j));
			--j;
		}
		crowded[i] &= (!max_height.empty() && max_height.rbegin()->first >= det[i].second*2);
		max_height.insert(make_pair(det[i].second,i));
		--i;
	}

}

int main(){
	int i;

	scanf("%d%d",&N,&D);
	for(i = 0; i < N; ++i) scanf("%d%d",&det[i].first,&det[i].second);


	init();

	printf("%d\n",accumulate(crowded,crowded+N,0));
	return 0;
}
