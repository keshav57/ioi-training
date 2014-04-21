/*
 Created By: Malvika Joshi
 Problem: nocows
 Link: http://cerberus.delos.com:791/usacoprob2?a=BKsrStSpHTO&S=nocows
*/

#include <stdio.h>

int numtrees[201][101];
int N,K;

int get_trees(){
	int i,j,k;

	numtrees[1][0] = 0;
	for(j = 1;j <= K; j++){
		numtrees[1][j] = 1;
	}


	for(j = 1; j <= K; j++){
		for(i = 2; i <= N; i++){
			numtrees[i][j] = 0;
			for(k = 1; k < i-1; k++){
				numtrees[i][j] += numtrees[i-1-k][j-1] * numtrees[k][j-1];
				numtrees[i][j] %= 9901;
			}
		}
	}

	return ((9901 + numtrees[N][K]) - numtrees[N][K-1])%9901;
}

int main(){
	scanf("%d%d",&N,&K);
	printf("%d\n",get_trees());
	return 0;
}

