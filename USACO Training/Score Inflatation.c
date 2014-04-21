/*
 Created By: Malvika Joshi
 Problem: inflate
 Link: http://cerberus.delos.com:791/usacoprob2?S=inflate&a=jpZoGhbbFFQ
*/

#include <stdio.h>

typedef struct { int points, minutes; } catagory;

catagory A[10001];
int knapsack[10001] = {0};
int N,K;

int main(){
	int i,temp,j;

	scanf("%d%d",&K,&N);
	for(i = 1;i <= N; i++){
		scanf("%d%d",&A[i].points,&A[i].minutes);
	}

	for(i = 1;i <= N; i++){
		for(j = 0; j <= K; j++){
			if(A[i].minutes > j) continue;
			temp = knapsack[j-A[i].minutes] + A[i].points;
			knapsack[j] = temp > knapsack[j] ? temp: knapsack[j];
		}
	}

	printf("%d\n",knapsack[K]);
	return 0;
}
