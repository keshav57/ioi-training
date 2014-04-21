/*
 Created By: Malvika Joshi
 Problem: Alliance (January-2012 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=111
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>

#define NMAX 100010
#define MOD (int)(1e9+7)

using namespace std;

int visited[NMAX];
int finish[NMAX];

vector<int> adj[NMAX];
int N;

int n;
int dfs(int v, int p){
	if(visited[v]) return 1;

	visited[v] = 1;

	int i,cyc,par;

	cyc = 0;
	par = 1;

	for(i = 0; i < adj[v].size(); ++i){
		if(par && adj[v][i] == p){
			par = 0;
			continue;
		}

		if(finish[adj[v][i]]) continue;
 		cyc += dfs(adj[v][i],v);
	}

	finish[v] = ++n;

	return cyc;
}

int compute(){

	int ways,i,cyc,mul;

	ways = 1;

	for(i = 0; i < N; ++i){
		if(visited[i]) continue;
		n = 0;
		cyc = dfs(i,-1);

		if(cyc > 1) return 0;
		mul = cyc ? 2 : n;

		ways = (1LL*ways*mul)%MOD;
	}

	return ways;
}

int main(){

	int m,a,b;

	scanf("%d%d",&N,&m);

	while(m--){
		scanf("%d%d",&a,&b);
		--a,--b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	printf("%d\n",compute());

	return 0;
}
