/*
 Created By: Malvika Joshi
 Problem: Roadblock (February-2014 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=400
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define MAXN 260
#define MAXM 25010
#define INF 300000000

int adj[MAXN][MAXN];	//graph

int dist[MAXN];		//dist from sortce
int par[MAXN];		//previous

char enq[MAXN];		//Q

int N,M;

pair<int,int> edges[MAXM];
int weight[MAXM];

int deque(){

	int i,v;

	v = -1;
	for(i = 0; i < N; ++i){
		if(!enq[i]) continue;
		if(v < 0 || dist[v] > dist[i]) v = i;
	}

	return v;
}

void dijkstra(int src){
	int i,v;
	int tmp;

	for(i = 0; i < N; ++i) {
		dist[i] = INF;
		par[i] = -1;
		enq[i] = 1;
	}

	dist[src] = 0;

	while(1){
		v = deque();
		if(v < 0) break;
		enq[v] = 0;

		for(i = 0; i < N; ++i){
			if(adj[v][i] == INF) continue;
			tmp = dist[v] + adj[v][i];
			if(dist[i] < tmp) continue;
			par[i] = v;
			dist[i] = tmp;
		}
	}
}

int tar_dist[MAXN];
char col[MAXN];
vector<int> child[MAXN];

void init(){

	dijkstra(N-1);
	memcpy(tar_dist,dist,sizeof(int)*MAXN);

	dijkstra(0);

	for(int i = 0; i < N; ++i){
		if(par[i] < 0) continue;
		child[par[i]].push_back(i);
	}
}

void dfs(int v){
	if(col[v]) return;
	col[v] = 1;
	for(int i = 0; i < child[v].size(); ++i) dfs(child[v][i]);
}

int compute(){

	int i,u,v,k,tmp;
	int maxdist,mindist;

	maxdist = dist[N-1];

	i = N-1;

	while(par[i] >= 0){
		dfs(i);

		mindist = INF;
		for(k = 0; k < M; ++k){
			if(col[edges[k].first] == col[edges[k].second]) continue;
			if(col[edges[k].first]) swap(edges[k].first,edges[k].second);

			u = edges[k].first, v= edges[k].second;
			tmp = weight[k];

			if(u == par[i] && v == i) tmp *= 2;

			mindist = min(mindist,dist[u]+tmp+tar_dist[v]);
		}

		maxdist = max(maxdist,mindist);
		i = par[i];
	}

	return maxdist-dist[N-1];
}

int main(){

	int i,j;

	freopen("rblock.in","r",stdin);
	freopen("rblock.out","w",stdout);

	scanf("%d%d",&N,&M);

	for(i =0 ; i < N; ++i){
		for(j = 0; j < N; ++j){
			adj[i][j] = INF;
		}
	}

	for(i =0 ; i < M; ++i){
		scanf("%d%d%d",&edges[i].first,&edges[i].second,&weight[i]);
		--edges[i].first,--edges[i].second;
		adj[edges[i].first][edges[i].second] = adj[edges[i].second][edges[i].first] = weight[i];
	}

	init();
	printf("%d\n",compute());

	return 0;
}
