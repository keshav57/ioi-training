/*
 Created By: Malvika Joshi
 Problem: Staircases
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1017
*/

#include <stdio.h>

long long unsigned ways[501][501];
int N;

long long unsigned knapsack(){
	int i,k;

	for(k = 0;k <= N; k++){
		ways[0][k] = 0;
	}
	ways[0][0] = 1;

	for(i = 1;i <= N; i++){
		for(k = 0; k<= N; k++){
			if(k < i){
				ways[i][k] = ways[i-1][k];
				continue;
			}
			ways[i][k] = ways[i-1][k] + ways[i-1][k-i];
		}
	}

	return ways[N][N]-1;
}

int main(){
	scanf("%d",&N);

#ifdef WINDOWS
	printf("%I64d",knapsack());
#endif

	printf("%lld",knapsack());
	return 0;
}
