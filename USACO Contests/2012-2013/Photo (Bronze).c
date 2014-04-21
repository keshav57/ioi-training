/*
 Created By: Malvika Joshi
 Problem: Photo (US Open 2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=280
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_K 1000

typedef struct { int id,enemy; } cow;

int N,K;
cow P[MAX_K+10];

inline int min(int a, int b){ return a < b ? a : b; }
inline int max(int a, int b){ return a > b ? a : b; }

int compare(const void* a, const void *b){
	const cow *p1 = a, *p2 = b;
	return p1->id-p2->id;
}


int greedy(){

	int groups,start,end,i;

	qsort(P,K,sizeof(cow),compare);

	start = 0;
	groups = 0;
	i = 0;

	while(start < N){
		end = N;
		for(;i < K && P[i].id < end; ++i){
			end = min(end,P[i].enemy);
		}
		++groups;
		start = end;
	}


	return groups;
}

int main(){

	int i,a,b;

	scanf("%d%d",&N,&K);

	for(i = 0; i < K; ++i){
		scanf("%d%d",&a,&b);
		--a,--b;
		P[i].id = min(a,b);
		P[i].enemy = max(a,b);
	}

	printf("%d\n",greedy());

	return 0;
}
