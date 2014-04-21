/*
 Created By: Malvika Joshi
 Problem: nuggets
 Link: http://cerberus.delos.com:791/usacoprob2?a=W4POM8EeJNN&S=nuggets
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned NP[100000]; //NP here means 'Not Possible' and not 'Nondeterministic Polynomial time'
int A[10];
int plus[10];
int N = 0,M;

int exists(unsigned target){
	int low,high,mid;
	low = 0;
	high = N-1;

	while(low <= high){
		mid = (high+low)/2;
		if(NP[mid] == target){
			return 1;
		}else if(NP[mid] < target){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}
	return 0;
}

int compare(const void *a, const void *b){ return *(int*)a-*(int*)b; }

int main(){
	int i,flag;
	unsigned min,k,prev = 1;

	scanf("%d",&M);

	for(i = 0;i < M; i++){
		scanf("%d",&A[i]);
		plus[i] = 0;
	}
	qsort(A,M,sizeof(int),compare);


	memset(NP,2000000000,sizeof(unsigned)*100000);

	for(k = 1; k < A[0]; k++) NP[N++] = k;

	if(!N){
		printf("0\n");
		return 0;
	}


	while(1){
		min = 2000000000;
		for(i = 0;i < M; i++){
			if(plus[i] < N && A[i] + NP[plus[i]] == prev){
				plus[i]++;
			}

			if(plus[i] < N && A[i] + NP[plus[i]] < min) min = A[i] + NP[plus[i]];
		}
		if(min >= 2000000000) break ;
		flag = 1;
		for(i = 0;i < M; i++){
			if(A[i] <= min && !exists(min-A[i])){
				flag = 0;
				break;
			}
		}
		if(flag){
			NP[N++] = min;
			if(N >= 100000){
				printf("0\n");
				return 0;
			}
		}
		prev = min;
	}

	printf("%u\n",NP[N-1]);

	return 0;
}
