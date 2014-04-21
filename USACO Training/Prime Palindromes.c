/*
 Created By: Malvika Joshi
 Problem: pprime
 Link: http://cerberus.delos.com:791/usacoprob2?S=pprime&a=0rwTPSJJCgx
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int prime_pal[1000000];
int P = 0,a,b;

int is_prime(int x){
	int i,l = 1 + (int)sqrt(x);

	for(i = 2;i <= l;i++){
		if(!(x % i)){
			return 0;
		}
	}
	return 1;
}

void generate_pal(char num[10], int k,int i){
	int j;

	if(i == (k+1)/2){
		j = atoi(num);
		if(j <= b && j >= a && is_prime(j)){
			prime_pal[P++] = j;
		}
		return;
	}

	for(j = 0; j < 10; j++){
		if(!i && !j) continue;
		num[i] = '0'+j;
		num[k-i-1] = num[i];
		generate_pal(num,k,i+1);
	}

	return;
}

int digits(int x){
	if(!x) return 0;
	return 1 + digits(x/10);
}

int main(){

	int i,k,da,db;
	char num[10];

	scanf("%d%d",&a,&b);
	da = digits(a);
	db = digits(b);

	for(k = da; k <= db; ++k){
		generate_pal(num,k,0);
	}

	for(i = 0;i < P;i++){
		printf("%d\n",prime_pal[i]);
	}

	return 0;
}
