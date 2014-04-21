/*
 Created By: Malvika Joshi
 Problem: Flags
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1225
*/

#include <stdio.h>

typedef struct { long long unsigned red,white; } strip;

strip S[50];
int N;

long long unsigned DP(){
	int i;
	S[0].red = 0;
	S[0].white = 0;
	S[1].red = 1;
	S[1].white = 1;

	for(i = 2;i <= N; i++){
		S[i].red = S[i-1].white + S[i-2].white;
		S[i].white = S[i-1].red + S[i-2].red;
	}

	return S[N].red+S[N].white;
}

int main(){
	scanf("%d",&N);
	printf("%llu",DP());
	return 0;
}
