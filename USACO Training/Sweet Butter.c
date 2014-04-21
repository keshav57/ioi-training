/*
 Created By: Malvika Joshi
 Problem: butter
 Link: http://cerberus.delos.com:791/usacoprob2?a=3zLnjccTCIq&S=butter
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define inf 1800000

typedef struct { int to,dist; } edge;
typedef struct { edge edges[800]; int n;  } vertex;

int compare(const void* a, const void* b){
	const edge *p1 = (edge*)a;
	const edge *p2 = (edge*)b;
	return p1->dist-p2->dist;
}

vertex V[800];
int D[800];
int Q[800];
int Cow[2900] = {0};
int enqueued[800];
int N,H,T,C,M;

int bfs(int src){
	int v,i,temp,k;
	memset(D,inf,sizeof(int)*800);
	memset(enqueued,0,sizeof(int)*800);

	D[src] = 0;
	H = 0;
	T = 0;
	Q[T++] = src;

	while(H < T){
		v = Q[H++];
		enqueued[v] = 0;
		for(i = 0; i < V[v].n; i++){
			temp = D[v] + V[v].edges[i].dist;
			k = V[v].edges[i].to;
			if(temp < D[k]){
				D[k] = temp;
				if(!enqueued[k]){
					Q[T++] = k;
					enqueued[k] = 1;
				}
			}
		}
	}

	int sum = 0;
	for(i = 0;i < N; i++) sum += D[i] * Cow[i];

	return sum;
}

int main(){
	int i,p,a,b,temp,min = inf;

	scanf("%d%d%d",&C,&N,&M);

	for(i = 0;i < C; i++){
		scanf("%d",&p);
		Cow[--p]++;
	}

	for(i = 0;i < N; i++){
		V[i].n = 0;
	}

	for(i = 0;i < M; i++){
		scanf("%d%d%d",&a,&b,&p);
		a--;
		b--;
		V[a].edges[V[a].n].to = b;
		V[a].edges[V[a].n++].dist = p;
		V[b].edges[V[b].n].to = a;
		V[b].edges[V[b].n++].dist = p;
	}

	for(i = 0;i < N; i++){
		qsort(V[i].edges,V[i].n,sizeof(edge),compare);
	}

	for(i = 0;i < N; i++){
		temp = bfs(i);
		if(temp < min)  min = temp;
	}

	printf("%d\n",min);

	return 0;
}
