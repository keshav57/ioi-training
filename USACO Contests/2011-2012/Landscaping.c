/*
 Created By: Malvika Joshi
 Problem: Landscaping (March-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=126
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 110
#define MAXM 2010
#define INF 2000000
#define I 1000

int cost[MAXN][MAXM];
int A[MAXN];
int B[MAXN];
int N,X,Y,Z;

inline int min(int a,int b){ return a < b ? a : b; };

int DP(){
	int i,k,p,extra,tcst,tmp,j;

	for(k = -I; k <= I; k++){
		extra = k+B[0]-A[0];
		cost[i][k+I] =  extra > 0 ? extra*X : -extra*Y;
	}

	for(i = 1; i < N; i++){
		for(k = -I; k <= I; k++){
			extra = k+B[i]-A[i];
			j = k+I;
			cost[i][j] = INF;

			if(extra < 0){
				for(p = 0; p >= extra; --p){
					tmp = extra-p;
					tcst = cost[i-1][p+I] + (tmp > 0 ? tmp*X : -tmp*Y) + abs(p*Z);
					cost[i][j] = min(cost[i][j],tcst);
				}
			}else{
				for(p = 0; p <= extra; ++p){
					tmp = extra-p;
					tcst = cost[i-1][p+I] + (tmp > 0 ? tmp*X : -tmp*Y) + abs(p*Z);
					cost[i][j] = min(cost[i][j],tcst);
				}
			}
		}
	}

	return cost[N-1][I];
}

int main(){
	int i;
	scanf("%d%d%d%d",&N,&X,&Y,&Z);

	for(i = 0; i < N; i++) scanf("%d%d",&A[i],&B[i]);

	printf("%d\n",DP());

	return 0;
}
