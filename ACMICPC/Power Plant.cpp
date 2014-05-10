/*
 Problem: Power Plant (Regionals 2013: Asia-Jakarta)
 Link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=596&page=show_problem&problem=4448
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>

#define NMAX 210
#define MMAX 40010

using namespace std;
typedef pair<int,pair<int,int> > edge;

int power_plant[NMAX];
int parent[NMAX];
int height[NMAX];

int find(int x){
	if(parent[x] == x) return x;
	parent[x] = find(parent[x]);
	return parent[x];
}

void merge(int x, int y){
	if(height[y] > height[x]){
		parent[x] = y;
		power_plant[y] |= power_plant[x];
	}else{
		parent[y] = x;
		height[x] += (height[y] == height[x]);
		power_plant[x] |= power_plant[y];
	}
}

void make_set(int x){
	power_plant[x] = 0;
	parent[x] = x;
	height[x] = 1;
}

edge edges[MMAX];
int N,M,K,T;

int main(){
	int i,t,x,y,cost;

	scanf("%d",&T);

	for(t = 1; t <= T; ++t){
		scanf("%d%d%d",&N,&M,&K);

		for(i =0 ; i < N; ++i){
			make_set(i);
		}

		while(K--){
			scanf("%d",&i);
			power_plant[i-1] = 1;
		}

		for(i = 0; i < M; ++i){
			scanf("%d%d%d",&edges[i].second.first,&edges[i].second.second,&edges[i].first);
			--edges[i].second.first,--edges[i].second.second;
		}

		sort(edges,edges+M);

		cost = 0;
		for(i = 0; i < M; ++i){
			x = find(edges[i].second.first);
			y = find(edges[i].second.second);
			if(x == y) continue;
			if(power_plant[x] && power_plant[y]) continue;
			merge(x,y);
			cost += edges[i].first;
		}

		printf("Case #%d: %d\n",t,cost);
	}

	return 0;
}
