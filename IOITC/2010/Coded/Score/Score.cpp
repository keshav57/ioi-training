/*
 Created By: Malvika Joshi
 Problem: Score (IOITC-2009 Test-3) (Used in 2010)
*/

#include <algorithm>
#include <cstdio>
#include <iostream>

#define N_MAX 1000010

using namespace std;
typedef long long lli;

lli pref[N_MAX];
lli max_score[N_MAX];
int range[N_MAX];

int cubes[N_MAX];
int N,K,H,T;

lli dp(){

	int i;

	H = T = 0;

	pref[0] = cubes[0];
	max_score[0] = cubes[0];
	range[T++] = 0;

	for(i = 1; i < K; ++i){
		pref[i] = pref[i-1]+cubes[i];
		max_score[i] = pref[i]-max_score[range[H]];

		while(T && max_score[range[T-1]] > max_score[i]) --T;
		range[T++] = i;
	}

	for(; i <= N; ++i){
		pref[i] = pref[i-1]+cubes[i];
		max_score[i] = pref[i]-max_score[range[H]];

		if(H < T && range[H] == i-K) H++;
		while(T > H && max_score[range[T-1]] >= max_score[i]) --T;
		range[T++] = i;
	}

	return max_score[N];
}

int main(){

	int i;

	scanf("%d%d",&N,&K);

	for(i = 1; i <= N; ++i){
		scanf("%d",&cubes[i]);
	}

	printf("%lld\n",dp());

	return 0;
}
