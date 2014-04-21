/*
 Created By: Malvika Joshi
 Problem: money
 Link: http://cerberus.delos.com:791/usacoprob2?S=money&a=rQv2h69LAhX
*/

#include <stdio.h>

int V,N;
long long knapsack[10001] = {0};
int coinage[26];

long long num_ways(){

	int i,j;
	knapsack[0] = 1;

	for(i = 1; i <= V; i++){
		for(j = coinage[i]; j <= N; j++){
			knapsack[j] += knapsack[j-coinage[i]];
		}
	}
	return knapsack[N];
}

int main(){
	int i;
	scanf("%d%d",&V,&N);

	for(i = 1;i <= V; i++){
		scanf("%d",&coinage[i]);
	}

	printf("%lld\n",num_ways());

	return 0;
}
