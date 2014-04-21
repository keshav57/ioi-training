/*
 Created By: Malvika Joshi
 Problem: Theb Triangle (IOI-1994)
 Link: http://www.ioinformatics.org/locations/ioi94/contest/day1prb1/problem.shtml
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

#define NMAX 110

using namespace std;

int rows[NMAX][NMAX];
int dp[NMAX][NMAX];

int N;

int compute(){
	int i,k;

	for(i = 0; i < N; ++i){
		dp[N-1][i] = rows[N-1][i];
	}

	for(k = N-2; k >= 0; --k){
		for(i = 0; i <= k; ++i){
			dp[k][i] = max(dp[k+1][i],dp[k+1][i+1])+rows[k][i];
		}
	}

	return dp[0][0];
}

int main(){
	int k,i;

	scanf("%d",&N);

	for(k = 0; k < N; ++k){
		for(i = 0; i <= k; ++i){
			scanf("%d",&rows[k][i]);
		}
	}

	printf("%d\n",compute());

	return 0;
}
