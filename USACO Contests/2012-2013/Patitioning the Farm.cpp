/*
 Created By: Malvika Joshi
 Problem: Partitioning the Farm (February-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=247
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>


#define NMAX 17

using namespace std;

int dp[NMAX][NMAX];
int max_grp[NMAX][NMAX];

int grid[NMAX][NMAX];
int cur[NMAX][NMAX];
int tmp[NMAX];

int N,M,K;

void init(int sel){
	int i,k,j;

	M = 0;

	memset(cur,0,sizeof(int)*NMAX*NMAX);

	for(i = 0; i < N; ++i){
		for(k = 0; k < N; ++k){
			cur[M][k] += grid[i][k];
		}
		if(sel&(1<<i)) ++M;
	}
	++M;

	for(i = 0; i < N; ++i){
		max_grp[i][i] = 0;
		for(k = 0; k < M; ++k){
			tmp[k] = cur[k][i];
			max_grp[i][i] = max(max_grp[i][i],tmp[k]);
		}

		for(j = i-1; j >= 0; --j){
			max_grp[i][j] = 0;
			for(k = 0; k < M; ++k){
				tmp[k] += cur[k][j];
				max_grp[i][j] = max(max_grp[i][j],tmp[k]);
			}
		}
	}
}

int get_min(int rem){
	int i,k,j;

	for(i = 0; i < N; ++i){
		dp[i][0] = max_grp[i][0];
		for(k = 1; k <= rem; ++k){
			dp[i][k] = max_grp[i][0];
			for(j = i-1; j >= 0; --j){
				dp[i][k] = min(dp[i][k],max(dp[j][k-1],max_grp[i][j+1]));
			}
		}
	}

	return dp[N-1][rem];
}

int main(){

	int i,j,sel,sol;

	scanf("%d%d",&N,&K);

	sol = 0;

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&grid[i][j]);
			sol += grid[i][j];
		}
	}


	for(sel = 0; sel < (1<<(N-1)); ++sel){
		i = __builtin_popcount(sel);
		if(i > K) continue;
		if(K-i >= N) continue;
		init(sel);
		sol = min(sol,get_min(K-i));
	}

	printf("%d\n",sol);

	return 0;
}
