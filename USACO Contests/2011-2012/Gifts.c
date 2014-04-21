/*
 Created By: Malvika Joshi
 Problem: Gifts (US Open-2012 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=103
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
	int p,s;
}cost;

cost G[MAX_N+10];
int B,N;

inline int max(int a, int b){ return a > b ? a :b; }

int compare(const void *a, const void *b){
	return *(int*)a-*(int*)b;
}

int max_cows(){
	int i,budget,cow;

	int total[MAX_N];

	budget = B;
	cow = 0;

	for(i = 0; i < N;i++){
		total[i] = G[i].p+G[i].s;
	}

	qsort(total,N,sizeof(int),compare);

	for(i = 0 ;i < N; i++){
		if(total[i] > budget) break;
		++cow;
		budget-=total[i];
	}

	return cow;
}


int main(){

	int i,maxc;

	scanf("%d%d",&N,&B);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&G[i].p,&G[i].s);
	}

	maxc = 0;
	for(i = 0; i < N; i++){
		G[i].p /= 2;
		maxc = max(maxc,max_cows());
		G[i].p *= 2;
	}

	printf("%d\n",maxc);

	return 0;
}
