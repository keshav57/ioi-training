/*
 Created By: Malvika Joshi
 Problem: stamps
 Link: http://cerberus.delos.com:791/usacoprob2?a=jpZoGhbbFFQ&S=stamps
*/

#include <stdio.h>
#define infinity 201

int N,K,L;
int V[51];

int knapsack(void){
	short int can_make[2000001];
	short int min[2000001];

	int i,k;
	can_make[0] = 1;
	min[0] = 0;
	for(k = 1;k <= K; k++){
		can_make[k] = 0;
		min[k] = infinity;
	}

	for(i = 1;i <= N; i++){
		for(k = 0; k <= K; k++){
			if(V[i] > k) continue;
			if(can_make[k-V[i]]){
				can_make[k] = 1;
				if(min[k-V[i]]+1 < min[k]) min[k] = min[k-V[i]]+1;
			}
		}
	}

	for(k = 0; k <= K; k++){
		if(!can_make[k] || min[k] > L){
			return k-1;
		}
	}
	return K;
}

int main(){
	int i,max = 0;

	scanf("%d%d",&L,&N);

	for(i = 1; i <= N; i++){
		scanf("%d",&V[i]);
		if(V[i] > max) max = V[i];
	}

	K = L * max;

	max = knapsack();
	printf("%d\n",max);
	return 0;
}
