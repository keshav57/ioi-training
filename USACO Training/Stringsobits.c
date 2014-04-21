/*
 Created By: Malvika Joshi
 Problem: kimbits
 Link: http://cerberus.delos.com:791/usacoanal2?a=M1sjMcmpoAb&S=kimbits
*/

#include <stdio.h>

long long set_size[32][32];

void init(void){
	int i,j;

	for(j = 0;j < 32; j++){
		set_size[0][j] = 1;
		set_size[j][0] = 1;
	}

	for(i = 1;i < 32; i++){
		for(j = 1;j  < 32; j++){
			set_size[i][j] = set_size[i-1][j-1] + set_size[i-1][j];
		}
	}
}

void print(long long size, long long ones, long long index){
	if(!size) return;

	if(set_size[size-1][ones] <= index){
		printf("1");
		print(size-1,ones-1,index-set_size[size-1][ones]);
	}else{
		printf("0");
		print(size-1,ones,index);
	}
}

int main(){
	long long n,l,i;
	scanf("%lld%lld%lld",&n,&l,&i);
	init();
	print(n,l,i-1);
	printf("\n");
	return 0;
}
