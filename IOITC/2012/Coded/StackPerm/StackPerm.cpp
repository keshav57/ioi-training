/*
 Created By: Malvika Joshi
 Problem: Stack Permutation (IOITC-2012 Fina-3)
*/

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define MAXN 5010
#define MOD 1000000007

int pos[MAXN][MAXN];
int N;
int stack[MAXN];
int S;
int perm[MAXN];

void init(){
	int i,k;

	for(k = 0; k <= N; ++k) pos[0][k] = 1;

	for(i = 1; i <= N; ++i){
		pos[i][0] = pos[i-1][1];
		for(k = 1; k+i <= N; ++k){
			pos[i][k] = pos[i][k-1] + pos[i-1][k+1];
			pos[i][k] %= MOD;
		}
	}
}



int valid(){
	int i,less,n;

	i = 0;
	n = 1;
	less = 0;
	S = 0;

	while(i < N || S){
		if(S && perm[i] < stack[S-1]) return -1;
		if(perm[i] == stack[S-1]){
			--S;
			++i;
			continue;
		}

		if(S){
			less += pos[N-n+1][S-1];
			less %= MOD;
		}
		stack[S++] = n++;
	}

	return less;
}

int main(){

	int i,Q;

	scanf("%d%d",&N,&Q);

	init();

	while(Q--){
		for(i = 0; i < N; ++i) scanf("%d",&perm[i]);
		printf("%d\n",valid());
	}

	return 0;
}



