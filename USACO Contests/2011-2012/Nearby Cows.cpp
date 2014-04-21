/*
 Created By: Malvika Joshi
 Problem: Nearby Cows (February-2012 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=120
*/

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>

#define NMAX 100010
#define KMAX 22

using namespace std;

int cows[NMAX];
vector<int> adj[NMAX];
int N,K;

int par[NMAX][KMAX];
int child[NMAX][KMAX];
int sib[NMAX][KMAX];

void dfs(int p, int v){
	int u,i,k;

	if(p >= 0){
		for(k = 1; k <= K; ++k){
			par[v][k] = par[p][k-1]+cows[p];
		}
	}

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(u == p) continue;
		dfs(v,u);
		for(k = 1; k <= K; ++k){
			child[v][k] += child[u][k-1]+cows[u];
		}
	}
}

void dfs1(int p, int v){
	int k,i;


	if(p >= 0){
		for(k = 2; k <= K; ++k){
			sib[v][k] = child[p][k-1]-child[v][k-2]-cows[v];
			sib[v][k] += sib[p][k-1];
		}
	}

	for(i = 0; i < (int)adj[v].size(); ++i){
		if(adj[v][i] == p) continue;
		dfs1(v,adj[v][i]);
	}
}

int main(){
	int i,u,v;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N-1; ++i){
		scanf("%d%d",&u,&v);
		--u,--v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(i = 0; i < N; ++i){
		scanf("%d",&cows[i]);
	}

	dfs(-1,0);
	dfs1(-1,0);

	for(i = 0; i < N; ++i){
		printf("%d\n",par[i][K]+child[i][K]+sib[i][K]+cows[i]);
	}


	return 0;
}
