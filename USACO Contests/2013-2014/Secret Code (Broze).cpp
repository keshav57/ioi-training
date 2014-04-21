/*
 Created By: Malvika Joshi
 Problem: Secret Code (February-2014 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=396
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define N_MAX 110

using namespace std;

int pos[N_MAX][N_MAX];

char str[N_MAX];
int N;

inline int is_equal(int ps, int pe, int s, int e){
	int i;
	for(i = 0; i+ps <= pe; ++i){
		if(str[ps+i]^str[s+i]){
			return 0;
		}
	}
	return 1;
}

int dp(){
	int i,j,k,len;

	for(i = 0; i < N; ++i) pos[i][i] = 4;

	for(len = 1; len < N; ++len){
		for(i = 0; i+len < N; ++i){
			j = i+len;

			pos[i][j] = 1;
			if(len&1) continue;

			k = i+(j-i)/2-1;


			if(is_equal(i,k,k+1,j-1)) pos[i][j] += pos[k+1][j];
			if(is_equal(i,k,k+2,j)) pos[i][j] += pos[k+1][j];
			k += 2;

			if(is_equal(k,j,i+1,k-1)) pos[i][j] += pos[i][k-1];
			if(is_equal(k,j,i,k-2)) pos[i][j] += pos[i][k-1];
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
