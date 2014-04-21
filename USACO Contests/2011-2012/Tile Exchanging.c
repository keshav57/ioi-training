/*
 Created By: Malvika Joshi
 Problem: Tile Exchanging (November-2011 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=90
*/

#include <stdio.h>
#include <math.h>

#define MAXN 15
#define MAXM 10010
#define INF  100000

inline int min(int a, int b){ return a < b ? a : b; }

int cost[MAXM][MAXN];
int A[MAXN];
int N,M;

int DP(){
	int i,k,m;

	for(m = 1; m <= M; ++m) cost[m][0] = INF;

	for(i = 1; i <= N; ++i){
		for(m = 0; m <= M; m++){
			cost[m][i] = INF;
			for(k = 0; k*k <= m; k++){
				cost[m][i] = min(cost[m][i],cost[m-(k*k)][i-1]+(A[i]-k)*(A[i]-k));
			}
		}
	}

	return cost[M][N] >= INF ? -1 : cost[M][N];
}

int main(){
	int i;

	scanf("%d%d",&N,&M);
	for(i = 1; i <=  N; i++){
		scanf("%d",&A[i]);
	}

	printf("%d\n",DP());

	return 0;
}
