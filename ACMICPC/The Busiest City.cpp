/*
 Problem: The Busiest City (Regionals 2013 : Asia-Jakarta)
 Link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=596&page=show_problem&problem=4447
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>

#define NMAX 20010

using namespace std;

int sub_size[NMAX];
int N;

vector<int> adj[NMAX];

int dfs(int v, int p){
	sub_size[v] = 1;
	int i;

	for(i = 0; i < (int)adj[v].size(); ++i){
		if(adj[v][i] == p) continue;
		sub_size[v] += dfs(adj[v][i],v);
	}

	return sub_size[v];
}

int sol(int v, int p){
	int paths,i,u;

	paths = (N-sub_size[v])*(sub_size[v]-1);	//outside v's subtree to somewhere inside it

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(p == u) continue;
		paths += sub_size[u]*(N-sub_size[u]-1);
	}

	paths /= 2;

	for(i = 0; i < (int)adj[v].size(); ++i){
		if(adj[v][i] == p) continue;
		paths = max(paths,sol(adj[v][i],v));
	}

	return paths;
}

int T;

int main(){
	int i,t,a,b;

	scanf("%d",&T);

	for(t = 1;t <= T; ++t){
		scanf("%d",&N);

		for(i = 0; i < N; ++i) adj[i].clear();

		for(i = 1; i < N; ++i){
			scanf("%d%d",&a,&b);
			--a,--b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		dfs(0,-1);
		printf("Case #%d: %d\n",t,sol(0,-1));
	}

	return 0;
}
