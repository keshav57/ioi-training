/*
 Created By: Malvika Joshi
 Problem: Haybale Stacking (January -2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=104
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

int Stack[MAX_N+10];
int N,K;

int compare(const void *a, const void *b){
	return (*(int*)a-*(int*)b);
}

int main(){

	int i,s,e;

	scanf("%d%d",&N,&K);

	for(i = 0; i < K; i++){
		scanf("%d%d",&s,&e);
		++Stack[s-1];
		--Stack[e];
	}

	for(i = 1; i < N; i++){
		Stack[i]+=Stack[i-1];
	}

	qsort(Stack,N,sizeof(int),compare);

	printf("%d\n",Stack[N/2]);

	return 0;
}
