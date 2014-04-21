/*
 Created By: Malvika Joshi
 Problem: Milliard Vasya's Function
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1353
*/

#include <stdio.h>

long long unsigned num[10][100] = {{0}};
int N;

long long unsigned DP(){
	int s,k,i;

	num[0][0] = 1;

	for(k = 1; k <= 9; ++k){
		for(s = 0; s <= N; s++){
			for(i = 0; i <= 9 &&i <= s; i++){
				num[k][s] += num[k-1][s-i];
			}
		}
	}

	return num[9][N];
}

int main(){
	long long unsigned total;
	scanf("%d",&N);
	total = DP() + (N == 1);
	printf("%llu",total);
	return 0;
}
