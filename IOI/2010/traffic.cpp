#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>

#define NMAX 1000010

using namespace std;

vector<int> adj[NMAX];
int weight[NMAX];
int size[NMAX];

int N,tot;

pair<int,int> dfs(int v, int p){
	int con,i,u;
	pair<int,int> best;

	size[v] = weight[v];
	best = make_pair(tot,v);
	con = 0;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(u == p) continue;
		best = min(best,dfs(u,v));
		size[v] += size[u];
		con = max(con,size[u]);
	}

	con = max(con,tot-size[v]);

	return min(best,make_pair(con,v));
}

int main(){
	int i,j;

	scanf("%d",&N);

	for(i =0 ; i < N; ++i){
		scanf("%d",&weight[i]);
		tot += weight[i];
	}

	while(--N){
		scanf("%d%d",&i,&j);
		adj[i].push_back(j);
		adj[j].push_back(i);
	}

	printf("%d\n",dfs(0,-1).second);
	return 0;
}
