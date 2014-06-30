#include "grader.h"
#include "encoder.h"

#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;


#define NMAX 1010
#define MMAX 40

int adj[NMAX][NMAX];
int n[NMAX];

int dist[MMAX][NMAX];

int Q[NMAX];
int H,T;
int visited[NMAX];

int parent[NMAX];


void bfs(int src){
	int i,v;

	H = T = 0;
	Q[T++] = src;
	memset(visited,0,sizeof(visited));
	visited[src] = 1;

	while(H < T){
		v = Q[H++];

		for(i = 0; i< n[v];++i){
			if(visited[adj[v][i]]) continue;
			dist[src][adj[v][i]] = dist[src][v]+1;
			visited[adj[v][i]] = 1;
			Q[T++] = adj[v][i];
		}
	}
}

void dfs(int v, int p){
	parent[v] = p;
	visited[v]  =1;

	int i;

	for(i = 0; i < n[v]; ++i){
		if(visited[adj[v][i]]) continue;
		dfs(adj[v][i],v);
	}
}

int ternary[NMAX*MMAX];

/*
 * dist[i] = dist[parent[i]] + 1 ------ 2
 * dist[i] = dist[parent[i]] - 1 ------ 1
 * dist[i] = dist[parent[i]] ---------- 0
 */

void encode(int nv, int nh, int ne, int *v1, int *v2){
	int i,b,k,num;


	while(ne--){
		adj[v1[ne]][n[v1[ne]]++] = v2[ne];
		adj[v2[ne]][n[v2[ne]]++] = v1[ne];
	}

	dfs(0,-1);


	for(i = 1; i < nv; ++i){
		for(b = 0; b < 10; ++b){
			encode_bit(!!(parent[i]&(1<<b)));
		}
	}


	for(i = 0; i < nh; ++i){
		bfs(i);
	}

	T = 0;


	for(i =0 ; i < nh; ++i){
		for(k = i+1; k < nv; ++k){
			ternary[T++] = (dist[i][k] == dist[i][parent[k]]+1 ? 2 : (dist[i][k] == dist[i][parent[k]]-1));
		}
	}

	for(i = 0; i < T; i += 3){
		num = 0;
		for(b = 2; b >= 0; --b){
			num += (num<<1) + ternary[i+b];
		}

		for(b = 0; b < 5; ++b){
			encode_bit(!!(num&(1<<b)));
		}
	}


}
