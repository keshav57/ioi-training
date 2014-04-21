/*
 Problem: Weighed Sum
*/

#include <stdio.h>
#include <limits.h>

#define und INT_MIN

int DP[20001][2001];
int A[20001] = {0};
int N,M;

inline int max(int a, int b){ return a > b ? a : b;}

void knapsack(){

	int i,j,temp;

	for(i = 0;i < N; i++){
		DP[i][0] = 0;
		DP[0][i] = 0;
	}

	for(i = 1;i <= N;i ++){
		for(j = 1;j <= M; j++){
			temp = DP[i-1][j-1] + A[i]*j;
			if(j > i){
				DP[i][j] = und;
			}if(j == i){
				DP[i][j] = temp;
			}else {
				DP[i][j] = max(DP[i-1][j],temp);
			}
		}
	}

	return;
}

int main(){

	int i;

	scanf("%d%d",&N,&M);

	for(i = 1;i <= N; i++){
		scanf("%d",&A[i]);
	}

	knapsack();

	printf("%d",DP[N][M]);

	return 0;
}
