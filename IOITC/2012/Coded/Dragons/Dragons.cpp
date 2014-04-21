/*
 Creatd By: Malvika Joshi
 Problem: Here there be Dragons (IOITC-2012 Test 2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define inf 600000000001

typedef struct { long long x,y; } vertex;

int compare(vertex a, vertex b){ return a.x < b.x; }

inline long long dist(vertex a, vertex b){ return (abs(a.x-b.x) + abs(a.y-b.y)); }

vertex D[400];
long long DP[400][400];
long long N,K,rows,cols;

int main(){
	long long i,j,k;

	scanf("%lld%lld%lld%lld",&rows,&cols,&K,&N);

	N++;
	D[0].x = 0;
	D[0].y = 0;

	for(i = 1;i < N; i++){
		scanf("%lld%lld",&D[i].x,&D[i].y);
	}

	std::sort(D+1,D+N,compare);

	DP[0][0] = 0;

	for(i = 1; i < N; i++){
		DP[i][0] = inf;
	}

	for(k = 1; k <= K; k++){
		DP[0][k] = inf;
	}

	long long min,temp;

	for(k = 1; k <= K; k++){
		for(i = 1; i < N; i++){
			min = inf;
			for(j = 0; j < i; j++){
				temp = DP[j][k-1] + dist(D[i],D[j]);
				if(temp < min){
					min = temp;
				}
			}
			DP[i][k] = min;
		}
	}

	min = inf;

	for(i = 1;i < N; i++){
		if(DP[i][K] < min){
			min = DP[i][K];
		}
	}

	printf("%lld",min);

	return 0;
}
