#include <algorithm>
#include <iostream>
#include <cstdio>
#include "square.h"

#define NMAX 1010

using namespace std;

int dp[NMAX][NMAX];
int N;

inline int min3(int a, int b, int c){
	return min(a,min(b,c));
}

int findMaxSquare(int material[SIZE][SIZE], int materialSize){
	int i,j,ct,sz;

	N = materialSize;

	ct = 0;
	sz = 0;

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			if(!material[i][j]) continue;

			dp[i][j] = min3( i ? dp[i-1][j] : 0 , j ? dp[i][j-1] : 0 , i&&j ? dp[i-1][j-1] : 0) + 1;

			if(dp[i][j] > sz) sz = dp[i][j],ct = 0;
			ct += dp[i][j] == sz;
		}
	}


	return ct*sz;
}
