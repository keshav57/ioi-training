/*
 Created By: Malvika Joshi
 Problem: Cow Ids (February-2012 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=116
*/

#include <stdio.h>

int ids[10000001][11];
int N,K;


int init(){
	int i,k;

	ids[0][0] = 1;

	for(i = 1; i <= N; i++){
		ids[i][0] = 1;
		for(k = 1; k <= K; k++){
			ids[i][k] = ids[i-1][k] + ids[i-1][k-1];
		}
		if(ids[i][K] >= N) break;
	}

	return i;
}

void print(int i, int k, int n){
	if(!i){
		printf("\n");
		return;
	}


	if(n <= ids[i-1][k]){
		printf("0");
		print(i-1,k,n);
		return;
	}

	n -= ids[i-1][k];
	printf("1");
	print(i-1,k-1,n);
}

int main(){

	int i;
	scanf("%d%d",&N,&K);

	if(K == 1){
		printf("1");
		for(i = 1; i < N; i++) printf( "0");
		printf("\n");
		return 0;
	}


	i = init();
	print(i,K,N);

	return 0;
}
