/*
 Created By: Malvika Joshi
 Problem: Gentlemen
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1244
*/

#include <stdio.h>

int DP[110][100010] = {{0}};
short taken[110][100010] = {{0}};
int weights[110];
int N,W;

int knapsack(){
	DP[0][0] = 1;

	int i,k;

	for(i = 1; i <= N; i++){
		for(k = 0;k <= W; k++){
			if(weights[i] > k){
				DP[i][k] = DP[i-1][k];
				continue;
			}

			if(DP[i-1][k] && DP[i-1][k-weights[i]]){
				DP[i][k] = -1;
			}else if(DP[i-1][k] == -1 || DP[i-1][k-weights[i]] == -1){
				DP[i][k] = -1;
			}else if(DP[i-1][k]){
				DP[i][k] = 1;
			}else if(DP[i-1][k-weights[i]]){
				DP[i][k] = 1;
				taken[i][k] = 1;
			}
		}
	}

	return DP[N][W];
}


void print(int i,int k,int lim){
	int j;
	if(!i && !k){
		for(j = i+1; j < lim; j++){
			printf("%d ",j);
		}
		return;
	}

	if(!taken[i][k]){
		print(i-1,k,lim);
	}else{
		print(i,k-weights[i],i);
		for(j = i+1; j < lim; j++){
			printf("%d ",j);
		}
	}
}

int main(){
	int i,sol;
	scanf("%d%d",&W,&N);
	for(i = 1; i <= N; i++) scanf("%d",&weights[i]);

	sol = knapsack();

	if(sol == 1){
		print(N,W,N+1);
	}else{
		printf("%d",sol);
	}

	return 0;
}
