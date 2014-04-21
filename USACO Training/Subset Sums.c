/*
 Created By: Malvika Joshi
 Problem: subset
 Link: http://cerberus.delos.com:791/usacoprob2?S=subset&a=sk0Eg2D4Cba
*/

#include <stdio.h>
#include <stdlib.h>

unsigned DP[40][1600];
int N,K;

unsigned subset_sums(){
	int i,k;
	for(k = 0;k < K; k++) DP[0][k] = 0;
	DP[0][0] = 1;

	for(i = 1;i <= N; i++){
		for(k = 0;k <= K; k++){
			if(i > k){
				DP[i][k] = DP[i-1][k];
				continue;
			}
			DP[i][k] = DP[i-1][k] + DP[i-1][k-i];

		}
	}
	return DP[N][K]/2;
}

int main(){

	scanf("%d",&N);

	K = (N * (N+1))/2;
	if(K % 2){
		printf("0\n");
	}else {
		K /= 2;
		printf("%u\n",subset_sums());
	}
	exit(0);
}
