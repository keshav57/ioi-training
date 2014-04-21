/*
 Created By: Malvika Joshi
 Problem: humble
 Link: http://cerberus.delos.com:791/usacoprob2?S=humble&a=l22R33vpcwt
 */
#include <stdio.h>

int humble_numbers[100001];
int mul[100] = {0};
int primes[100];
int N,K;

int main(){

	int i,k,min,temp;

	scanf("%d%d",&K,&N);
	for(k = 0;k < K; k++){
		scanf("%d",&primes[k]);
	}

	humble_numbers[0] = 1;

	for(i = 1; i <= N; i++){
		min = -1;
		for(k = 0;k < K; k++){
			if(primes[k]*humble_numbers[mul[k]] == humble_numbers[i-1]){
				mul[k]++;
			}
			temp = primes[k]*humble_numbers[mul[k]];
			if(min == -1 || temp < min) min = temp;
		}
		humble_numbers[i] = min;
	}

	printf("%d\n",humble_numbers[N]);

	return 0;
}
