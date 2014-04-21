/*
 Created By: Malvika Joshi
 Problem: Binary Lexicographic Sequence
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1081
*/

#include <stdio.h>

int num[50][2];
int  N,K;

int init(){
	int i;
	num[1][0] = 1;
	num[1][1] = 1;

	for(i = 2;i <= N; i++){
		num[i][0] = num[i-1][0] + num[i-1][1];
		num[i][1] = num[i-1][0];
	}

	return num[N][0]+num[N][1];
}

void print(int k, int n){
	if(n == 0) return;
	if(k < num[n][0]){
		printf("0");
		print(k,n-1);
	}else{
		printf("1");
		print(k-num[n][0],n-1);
	}
}

int main(){
	scanf("%d%d",&N,&K);
	int n = init();
	if(K > n){
		printf("-1");
		return 0;
	}
	print(K-1,N);
	return 0;
}
