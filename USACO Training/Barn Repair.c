/*
 Created By: Malvika Joshi
 Problem: barn1
 Link: http://cerberus.delos.com:791/usacoprob2?S=barn1&a=xxfhBCrOcq5
*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void *b){ return *(int*)a - *(int*)b; }

int D[200];
int cows[200];
int M,S,C,N,G = 0;

int main(){
	int i,dist,sol;

	scanf("%d%d%d",&M,&S,&C);

	for(i = 0;i < C; i++){
		scanf("%d",&cows[i]);
	}

	qsort(cows,C,sizeof(int),compare);
	for(i = 1;i < C;i++){
		dist = cows[i]-cows[i-1]-1;
		if(dist){
			D[G] = dist;
			G++;
		}
	}

	qsort(D,G,sizeof(int),compare);

	M--;
	N = G-M;

	sol = 0;
	for(i = 0; i < N; i++){
		sol += D[i];
	}

	printf("%d\n",sol+C);

	return 0;
}
