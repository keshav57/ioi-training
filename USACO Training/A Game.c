/*
 Created By: Malvika Joshi
 Problem: game1
 Link: http://cerberus.delos.com:791/usacoprob2?S=game1&a=rbJKwS8odes
*/

#include <stdio.h>

int sum[200][200];
int sol[200][200];
int A[200];
int N;

void init(){
	int i,j;
	for(i = 0;i < N; i++){
		sum[i][i] = A[i];
	}
	for(i = 0;i < N; i++){
		for(j = i+1; j < N; j++){
			sum[i][j] = sum[i][j-1] + A[j];
		}
	}
}

inline int min(int a, int b){ return a < b ? a : b; }

int findsol(){
	int i,j,k;
	for(i = 0;i < N; i++){
		sol[i][i] = A[i];
	}

	for(j = 1; j < N; j++){
		for(i = 0;i+j < N; i++){
			k = i+j;
			sol[i][k] = sum[i][k] - min(sol[i+1][k],sol[i][k-1]);
		}
	}

	return sol[0][N-1];
}

int main(){
	int i,score;

	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%d",&A[i]);
	}

	init();
	score = findsol();

	printf("%d %d\n",score,sum[0][N-1]-score);

	return 0;
}
