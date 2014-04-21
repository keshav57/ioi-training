/*
 Created By: Malvika Joshi
 Problem: fact4
 Link: http://cerberus.delos.com:791/usacoprob2?a=3zLnjccTCIq&S=fact4
*/

#include <stdio.h>

int  N;
int f[4220];
int fact = 1;

int main(){
	int i,j;

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		f[i] = i+1;
	}

	for(i = 0;i < N; i++){
		for(j = i+1;j < N; j++){
			while(f[i] % 10 == 0){
				f[i] /= 10;
			}
			while(f[j] % 10 == 0){
				f[j] /= 10;
			}
			while(f[i] % 5 == 0 && f[j] % 2 == 0){
				f[j] /= 2;
				f[i] /= 5;
			}
			while(f[j] % 5 == 0 && f[i] % 2 == 0){
				f[j] /= 5;
				f[i] /= 2;
			}
		}
	}

	for(i = 0;i < N; i++){
		fact *= f[i];
		fact %= 10;
	}

	printf("%d\n",fact);
	return 0;
}
