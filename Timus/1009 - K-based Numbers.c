/*
 Created By: Malvika Joshi
 Problem: K-based Numbers
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1009
*/

#include <stdio.h>

typedef struct { long long unsigned zero,non_zero; } digits;

digits count[20];
int N,K;

long long unsigned DP(){
	int i;
	count[0].zero = 0;
	count[0].non_zero = K-1;

	for(i = 1;i < N; i++){
		count[i].zero = count[i-1].non_zero;
		count[i].non_zero = (count[i-1].non_zero+count[i-1].zero)*(K-1);
	}

	return count[N-1].non_zero+count[N-1].zero;
}

int main(){
	scanf("%d%d",&N,&K);
	printf("%llu",DP());
	return 0;
}

