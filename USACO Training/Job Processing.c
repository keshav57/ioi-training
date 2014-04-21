/*
 Created By: Malvika Joshi
 Problem: job
 Link: http://cerberus.delos.com:791/usacoprob2?S=job&a=5KaTStaR0xe
*/

#include <stdio.h>

int A[30];
int tA[30];
int fA[1000];
int B[30];
int tB[30];
int fB[1000];
int N,nA,nB;

void init(){
	int i,k,min;
	for(i = 0;i < N; i++){
		min = 0;
		for(k = 1; k < nA; k++){
			if(A[min] > A[k]) min = k;
		}
		fA[i] = A[min];
		A[min] += tA[min];
	}

	printf("%d ",fA[N-1]);

	for(i = 0;i < N; i++){
		min = 0;
		for(k = 1; k < nB; k++){
			if(B[min] > B[k]) min = k;
		}
		fB[i] = B[min];
		B[min] += tB[min];
	}
}

int get_max(){
	int i,max = 0;
	for(i = 0;i < N; i++){
		if(fA[i] + fB[N-i-1] > max){
			max = fA[i] + fB[N-i-1];
		}
	}
	return max;
}

int main(){
	int i;
	scanf("%d%d%d",&N,&nA,&nB);
	for(i = 0;i < nA; i ++) scanf("%d",&tA[i]),A[i] = tA[i];
	for(i = 0;i < nB; i ++) scanf("%d",&tB[i]),B[i] = tB[i];
	init();
	printf("%d\n",get_max());
	return 0;
}
