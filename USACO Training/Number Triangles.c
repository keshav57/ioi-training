/*
 Created By: Malvika Joshi
 Problem: numtri
 Link: http://cerberus.delos.com:791/usacoprob2?a=0rwTPSJJCgx&S=numtri
*/
#include <stdio.h>

int triangle[1000][1000];
int dist[1000][1000];
int R;

inline int max(int a, int b){ return a > b? a : b; }

int compute_routes(){
	int i,j,maxr= 0;
	dist[0][0] = triangle[0][0];

	for(i = 0;i < R-1; i++){
		for(j = 0;j < i+1; j++){
			dist[i+1][j] = max(dist[i+1][j],triangle[i+1][j]+dist[i][j]);
			dist[i+1][j+1] = max(dist[i+1][j+1],triangle[i+1][j+1]+dist[i][j]);
		}
	}

	for(i = 0;i < R; i++){
		maxr = max(maxr,dist[R-1][i]);
	}

	return maxr;
}

int main(){

	int i,j;
	scanf("%d",&R);

	for(i = 0;i < R; i++){
		for(j = 0; j < i+1; j++){
			scanf("%d",&triangle[i][j]);
			dist[i][j] = 0;
		}
	}

	printf("%d\n",compute_routes());

	return 0;
}
