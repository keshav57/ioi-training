/*
 Created By: Malvika Joshi
 Problem: Threeprime Numbers
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1586
*/

#include <stdio.h>

#define MOD 1000000009

int prime[1000] = {0};
int num[10010][100] = {{0}};
int N;

int is_prime(int x){
	int i;
	for(i = 2;i*i <= x; ++i){
		if(x % i) continue;
		return 0;
	}
	return 1;
}

void init(){
	int i;
	for(i = 100; i < 1000; i++){
		if(is_prime(i)){
			prime[i] = 1;
			num[3][i%100]++;
		}
	}
}

int DP(){
	int i,k,j,sol = 0,lst;
	for(i = 4; i <= N; i++){
		for(j = 11; j < 100; j+=2){
			for(k = 1; k < 10; k+=2){
				lst = j*10+k;
				if(prime[lst]){
					num[i][lst%100] += num[i-1][j];
					num[i][lst%100] %= MOD;
				}
			}
		}
	}


	for(i = 0;i < 100; i++){
		sol += num[N][i];
		sol %= MOD;
	}

	return sol;
}

int main(){
	scanf("%d",&N);
	init();
	printf("%d",DP());
	return 0;
}
