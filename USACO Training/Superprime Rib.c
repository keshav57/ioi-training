/*
 Created By: Malvika Joshi
 Problem: sprime
 Link: http://cerberus.delos.com:791/usacoprob2?a=vO5sS8b2zo5&S=sprime
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int N;

void generate_superprimes(int k, char num[10]){
	int tonum,i,l;
	tonum = atoi(num);
	l = sqrt(tonum);
	for(i = 2; i <= l+1; i++){
		if(tonum != i &&tonum % i == 0){
			return;
		}
	}
	if(k == N){
		printf("%d\n",tonum);
		return;
	}
	for(i = 1;i < 10; i++){
		if(!k && i == 1) continue;
		num[k] = '0' + i;
		generate_superprimes(k+1,num);
	}
	num[k] = '\0';
}

int main(){

	char num[10];
	freopen("sprime.in","r",stdin);
	freopen("sprime.out","w",stdout);

	scanf("%d",&N);

	generate_superprimes(0,num);

	return 0;
}
