/*
 Created By: Malvika Joshi
 Problem: Three Lines (US Open-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=131
*/

#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N 50010

using namespace std;

struct pt { int x,y; };

int compare(int a, int b){ return a > b; }

map<int,vector<int> > X;
map<int,int> rY;
pt C[MAX_N];
int N;

int init(){
	int i,count;
	count = 0;
	for(i = 0; i < N; i++){
		X[C[i].x].push_back(i);
		count += !rY[C[i].y];
		++rY[C[i].y];
	}

	if(rY.size() <= 3 || X.size() <= 3) return 1;

	for(map<int,vector<int> >::iterator it = X.begin(); it != X.end(); ++it){
		for(i = 0; i < it->second.size(); ++i){
			--rY[C[i].y];
			count -= !rY[C[i].y];
		}

		if(count <= 2) return 1;

		for(i = 0; i < it->second.size(); ++i){
			count += !rY[C[i].y];
			rY[C[i].y]++;
		}
	}

	return 0;
}

int main(){
	int i,pos;

	scanf("%d",&N);

	for(i = 0;i < N; i++) scanf("%d%d",&C[i].x,&C[i].y);

	pos = init();

	X.clear();
	rY.clear();

	for(i = 0; i < N; i++) swap(C[i].x,C[i].y);
	pos |= init();

	printf("%d\n",pos);

	return 0;
}
