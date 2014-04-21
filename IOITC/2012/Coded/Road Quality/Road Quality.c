/*
 Created By: Malvika Joshi	 
 Problem: Road Quality (IOITC-2012 Test-4)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int i,j;
	long long quality,length;
} edge;

edge Edges[100001];
int P[5000];
int Rank[5000];
int N,M,V = 0;

void make_set(int x){
	P[x] = x;
	Rank[x] = 0;
}

int find(int x){
	if(P[x] != x){
		P[x] = find(P[x]);
	}
	return P[x];
}

void s_union(int x, int y){
	int xroot,yroot;
	xroot = find(x);
	yroot = find(y);

	if(Rank[xroot] < Rank[yroot]){
		P[xroot] = yroot;
	}else if(Rank[xroot] > Rank[yroot]){
		P[yroot] = xroot;
	}else {
		P[yroot] = xroot;
		Rank[xroot]++;
	}
}

int cquality(const void *a, const void *b){
	edge *v1 = (edge*)a;
	edge *v2 = (edge*)b;
	return v2->quality-v1->quality;
}

int clength(const void *a, const void *b){
	edge *v1 = (edge*)a;
	edge *v2 = (edge*)b;
	return v1->length-v2->length;
}

long long kruskal(){
	int i;
	long long min = 0;
	for(i = 0;i < N; i++){
		make_set(i);
	}

	qsort(Edges,M,sizeof(edge),cquality);


	for(i = 0; i < M; i++){
		if(find(Edges[i].i) != find(Edges[i].j)){
			s_union(Edges[i].i,Edges[i].j);
			min = Edges[i].quality;
			V++;
		}
	}

	return min;
}

long long kruskal2(){
	int i;
	long long length = 0;
	for(i = 0;i < N; i++){
		make_set(i);
	}

	qsort(Edges,M,sizeof(edge),clength);


	for(i = 0; i < M; i++){
		if(find(Edges[i].i) != find(Edges[i].j)){
			s_union(Edges[i].i,Edges[i].j);
			length += Edges[i].length;
		}
	}

	return length;
}


int main(){

	int i,j;
	long long l,min;
	scanf("%d%d",&N,&M);

	for(i = 0;i < M; i++){
		scanf("%d%d%lld%lld",&Edges[i].i,&Edges[i].j,&Edges[i].quality,&Edges[i].length);
	}

	min = kruskal();

	if(V != N-1){
		printf("-1");
		return 0;
	}
	printf("%lld ",min);

	j = 0;

	while(Edges[j].quality >= min){
		j++;
	}

	M = j;

	l = kruskal2();

	printf("%lld",l);

	return 0;
}


