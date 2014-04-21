/*
 Created By: Malvika Joshi
 Problem: Secret Code (February-2014 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=399
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define N_MAX 110
#define MOD 2014

using namespace std;

int pos[N_MAX][N_MAX];

char str[N_MAX];
int N;

inline int is_equal(int ps, int pe, int s, int e){
	int i;
	for(i = 0; i+ps <= pe; ++i){
		if(str[ps+i]^str[s+i]) return 0;
	}
	return 1;
}

int dp(){
	int i,j,k,n,len;

	for(i = 0; i < N; ++i) pos[i][i] = 1;

	for(len = 1; len < N; ++len){
		for(i = 0; i+len < N; ++i){
			j = i+len;

			pos[i][j] = 1;
			n = 1;
			for(k = i; k <= j; ++k,++n){
				if(n >= (j-i+2)/2) break;
				if(is_equal(i,k,k+1,j))	pos[i][j] += pos[k+1][j];
				if(is_equal(i,k,j-n+1,j)) pos[i][j] += pos[k+1][j];;
				pos[i][j] %= MOD;
			}

			n = 1;
			for(k = j; k >= i; --k,++n){
				if(n >= (j-i+2)/2) break;
				if(is_equal(k,j,k-n,k-1)) pos[i][j] += pos[i][k-1];
				if(is_equal(k,j,i,i+n-1)) pos[i][j] += pos[i][k-1];;
				pos[i][j] %= MOD;
			}
		}
	}

	return pos[0][N-1]-1;
}

int main(){

	scanf("%s",str);
	N = strlen(str);
	printf("%d\n",dp());

	return 0;
}
