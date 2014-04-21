/*
 Created By: Malvika Joshi
 Problem: Milk Routing (December-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=210
*/

#include <stdio.h>

typedef struct { int u,v,w,c; } edge;
#define inf 1000000000

edge edges[1000];
int dist[500];
int capacity[500];
int latency[500];
int N,M,X;
int e = 0;

inline void addedge(int a, int b, int w, int c){
	edges[e].u = a;
	edges[e].v = b;
	edges[e].w = w;
	edges[e].c = c;
	e++;
}

void bellman(){

	int i,j,c2,c3;
	int c1;

	for(i = 0;i < N; i++){
		dist[i] = inf;
		capacity[i] = inf;
		latency[i] = inf;
	}

	latency[0] = 0;
	dist[0] = 0;

	for(i = 0;i < M-1;i ++){
		for(j = 0;j < e; j++){
			c2 = capacity[edges[j].u] < edges[j].c ? capacity[edges[j].u] : edges[j].c;
			c3 = latency[edges[j].u] + edges[j].w;
			c1 = c3 + X/c2;
			if(c1 < dist[edges[j].v]){
				capacity[edges[j].v] = c2;
				dist[edges[j].v] = c1;
				latency[edges[j].v] = c3;
			}
		}

	}

}

int main(){

	int i,a,b,c,w;
	scanf("%d%d%d",&N,&M,&X);


	for(i = 0;i < M; i++){
		scanf("%d%d%d%d",&a,&b,&w,&c);
		a--;
		b--;
		addedge(a,b,w,c);
		addedge(b,a,w,c);
	}

	bellman();

	printf("%d",dist[N-1]);

	return 0;

}
