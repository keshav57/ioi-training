/*
 Created By: Malvika Joshi
 Problem: Email
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1577
*/

#include <stdio.h>
#include <string.h>

#define MOD (int)1e9+7

char A[3010];
char B[3010];
int len[3010][3010];
int num[3010][3010];
int M,N;

int min(int a, int b){ return a < b ? a : b; }

int DP(){
	int i,j,l;

	len[0][0] = 0;
	num[0][0] = 1;

	for(i = 1;i < M; i++){
		len[i][0] = i;
		num[i][0] = 1;
	}

	for(j = 1; j < N; j++){
		len[0][j] = j;
		num[0][j] = 1;
	}

	for(i = 1; i < M; i++){
		for(j = 1;j < N; j++){

			len[i][j] = min(len[i-1][j],len[i][j-1]) +1;
			num[i][j] = 0;

			if(A[i] == B[j]) len[i][j] = len[i-1][j-1]+1;

			l = len[i][j] - 1;

			if(A[i] == B[j] && len[i-1][j-1] == l)	num[i][j] = num[i-1][j-1];
			else{
				if(len[i-1][j] == l) num[i][j] += num[i-1][j];
				if(len[i][j-1] == l) num[i][j] += num[i][j-1];
			}

			num[i][j] %=  MOD;
		}
	}

	return  num[M-1][N-1];
}

int main(){

	A[0] = '#';
	B[0] = '#';

	scanf("%s",A+1);
	scanf("%s",B+1);

	M = strlen(A);
	N = strlen(B);

	printf("%d",DP());

	return 0;
}
