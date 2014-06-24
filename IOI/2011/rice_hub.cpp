#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <numeric>

#define NMAX 100010
#define INF 1e18

using namespace std;
typedef long long lli;

lli prev[NMAX];
lli next[NMAX];
lli pos[NMAX];

int N;
lli B;

lli min_cost(int k){
	lli mcost,cost;
	int i,p,n;

	mcost = INF;

	p = (k-1)/2;
	n = k/2;

	prev[0] = 0;
	for(i = 1; i < N; ++i){
		prev[i] = prev[i-1] + (pos[i]-pos[i-1])*1LL*min(i,p);
		if(i > p) prev[i] -= (pos[i-1]-pos[i-p-1]);
	}

	next[N-1]  =0;
	for(i = N-2; i >= 0; --i){
		next[i] = next[i+1]+(pos[i+1]-pos[i])*1LL*min(N-i-1,n);
		if(i+n < N-1) next[i] -= (pos[i+n+1]-pos[i+1]);
	}

	for(i = 0; i < N; ++i){
		if(i-p >= 0 && i+n < N){
			cost = next[i]+prev[i];
			mcost = min(cost,mcost);
		}
	}
//	assert(mcost >= 0);
//	cout << mcost << ' ' << k<< endl;
	return mcost;
}

int search(){
	int low,high,mid;

	low = 1;
	high = N;

	while(low < high){
		mid = (high+low+1)/2;

		if(min_cost(mid) <= B){
			low = mid;
		}else{
			high =  mid-1;
		}
	}

	return low;
}

int besthub(int R, int L, int *x, lli b){
	int i;

	N = R;
	B = b;
	for(i = 0; i < N; ++i){
		pos[i] = x[i];
	}

	return search();
}
