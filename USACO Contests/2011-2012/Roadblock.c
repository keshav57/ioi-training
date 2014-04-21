/*
 Created By: Malvika Joshi
 Problem: Roadblock (December-2011 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 110
#define INF 100000010

int adj[MAXN][MAXN];
int par[MAXN];
int dist[MAXN];
int visited[MAXN];
int N,M;

int deque(){
	int m,w,i;
	w = INF;

	for(i = 0; i < N; i++){
		if(visited[i]) continue;
		if(dist[i] < w) w = dist[i],m = i;
	}

	return m;
}

int dijkstra(int src, int tar){

	int i,v;
	for(i = 0; i < N; i++) dist[i] = INF,visited[i] = 0;
	dist[src] = 0;
	par[src] = -1;

	while(1){
		v = deque();
		visited[v] = 1;
		if(v < 0) return INF;
		if(v == tar) return dist[v];

		for(i = 0; i < N; i++){
			if (dist[i] > dist[v]+adj[v][i]){
				dist[i] = dist[v] + adj[v][i];
				par[i] = v;
			}
		}
	}

	return INF;
}


inline int max(int a, int b){ return a > b ? a : b; }

int main(){

	int path[MAXN];
	int mroute,tmp, i,j,k,w;

	scanf("%d%d",&N,&M);

	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++) adj[i][j] = INF;

	for(i = 0; i < M; i++){
		scanf("%d%d%d",&j,&k,&w);
		--j,--k;
		adj[j][k] = adj[k][j] = w;
	}



	w = dijkstra(0,N-1);
	i = N-1;
	k = 0;
	mroute = w;

	while(i >= 0){
		path[k++] = i;
		i = par[i];
	}

	for(i = 0;i < k-1; i++){
		adj[path[i]][path[i+1]] <<= 1;
		adj[path[i+1]][path[i]] = adj[path[i]][path[i+1]];
		tmp = dijkstra(0,N-1);
		mroute = max(mroute,tmp);
		adj[path[i]][path[i+1]] >>= 1;
		adj[path[i+1]][path[i]] = adj[path[i]][path[i+1]];
	}

	printf("%d\n",mroute-w);

	return 0;
}
