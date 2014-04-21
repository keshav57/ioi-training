/*
 Created By: Malvika Joshi
 Problem:  Rope Folding (February 2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=112;
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 110

int knots[MAXN];
int N,L;

int compare	(const void *a, const void *b){ return *(int*)a-*(int*)b; }

int fold(int i, int j){
	while(--i >= 0 && ++j < N){
		if(knots[i+1]-knots[i] != knots[j]-knots[j-1]) return 0;
	}
	return 1;
}

int main(){
	int i,k;
	scanf("%d%d",&N,&L);

	for(i = 0; i < N; i++) scanf("%d",&knots[i]);

	qsort(knots,N,sizeof(int),compare);

	k  =0;
	for(i = 0; i < N-1; i++){
		k += fold(i,i);
		k += fold(i,i+1);
	}

	printf("%d\n",k-1);

	return 0;
}
