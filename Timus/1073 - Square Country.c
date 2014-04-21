/*
 Created By: Malvika Joshi
 Problem: Square Country
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1073
*/

#include <stdio.h>
#include <math.h>

int pieces[60001];
int N,K;

int min(int a, int b){ return a < b ? a : b; }

int knapsack(){
	int i,k,j;
	for(k = 0;k <= K; k++){
		pieces[k] = k;
	}

	for(i = 2;i <= N; i++){
		j = i*i;
		for(k = j; k <= K; k++){
			pieces[k] = min(pieces[k],pieces[k-j]+1);
		}
	}

	return pieces[K];
}

int main(){
	scanf("%d",&K);
	N = sqrt(K);
	printf("%d",knapsack());
	return 0;
}
