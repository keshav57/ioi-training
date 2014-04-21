/*
 Created By: Malvika Joshi
 Problem: sort3
 Link: http://cerberus.delos.com:791/usacoprob2?a=YnrI700o9Fg&S=sort3
*/

#include <stdio.h>
#include <stdlib.h>

int A[1000];
int S[1000];
int occ[3] = {0};
int N;

inline void swap(int i,int j){
	int t = A[i];
	A[i] = A[j];
	A[j] = t;
}

int main(){
	int i,j,swaps = 0,k,found;

	scanf("%d",&N);
	for(i= 0;i < N; i++){
		scanf("%d",&A[i]);
		occ[A[i]-1]++;
	}

	i = 0;
	j = 0;
	while(j  < 3 && i < N){
		if(!occ[j]) j++;
		S[i++] = j+1;
		occ[j]--;
	}

	for(i = 0;i < N;i++){
		if(S[i] == A[i]) continue;
		found = 0;
		for(j = 0;j < N; j++){
			if(A[j] == S[j] || A[j] != S[i]) continue;
			k = j;
			if(A[i] == S[j]){
				break;
			}
		}
		swap(i,k);
		swaps++;
	}

	printf("%d\n",swaps);

	exit(0);
}
