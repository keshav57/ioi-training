/*
 Created By: Malvika Joshi
 Problem: Balanced Cow Breeds (November-2012 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=193
*/

#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>

#define MOD 2012
#define NMAX 1010

using namespace std;

int unmatched[NMAX];
int pos[NMAX][NMAX];

char seq[NMAX];
int N;

void init(){
	int i,open;

	open = 0;
	for(i = 0; i < N; ++i){
		open += seq[i]^')' ? 1 : -1;
		assert(open >= 0);
		unmatched[i+1] = open;
	}
}

int dp(){
	int i,k;

	pos[N][0] = 1;

	for(i = N-1; i >= 0; --i){
		for(k = 0; k <= unmatched[i]; ++k){
			if(seq[i]^')'){
				pos[i][k] = pos[i+1][k+1]+pos[i+1][k];
				pos[i][k] %= MOD;
				continue;
			}
			pos[i][k] = k ? pos[i+1][k-1]+pos[i+1][k] : pos[i+1][k];
			pos[i][k] %= MOD;
		}
	}

	return pos[0][0];
}

int main(){

	scanf("%s",seq);
	N = strlen(seq);
	init();
	printf("%d\n",dp());
	return 0;
}
