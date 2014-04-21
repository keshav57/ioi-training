/*
 Created By: Malvika Joshi
 Problem: No Change (November-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=348
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 100010
#define KMAX 18
#define SMAX ((1<<16)+2)

typedef long long lli;

using namespace std;

lli val[KMAX];
int max_purchase[SMAX];
lli pref[NMAX];

int N,K;

lli dp(){
	int i,sel,k;
	lli left,sum;

	left = -1;
	for(sel = 1; sel < (1<<K); ++sel){

		for(i = 0; i < K; ++i){
			if(!(sel&(1<<i))) continue;

			k = max_purchase[sel^(1<<i)];
			k = upper_bound(pref+k,pref+N,pref[k]+val[i])-pref;
			max_purchase[sel] = max(max_purchase[sel],k-1);
		}

		assert(max_purchase[sel] >= 0);
		if(max_purchase[sel] < N-1) continue;

		sum  =0;
		for(i = 0; i < K; ++i){
			if(sel&(1<<i)) continue;
			sum += val[i];
		}

		left = max(left,sum);
	}

	return left;
}

int main(){
	int i;

	scanf("%d%d",&K,&N);

	++N;
	for(i = 0; i < K; ++i){
		scanf("%lld",&val[i]);
	}

	for(i = 1; i < N; ++i){
		scanf("%lld",&pref[i]);
		pref[i] += pref[i-1];
	}

	printf("%lld\n",dp());

	return 0;
}
