/*
 Created By: Malvika Joshi
 Problem: And How!
*/

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#include <cassert>
#include <utility>

#define NMAX 25000
#define KMAX 25

using namespace std;

bool query(const bool *);

bool fix[NMAX];
bool q[NMAX];

int K,N;

void set(int s, int e, bool b){
	for(; s <= e; ++s){
		q[s] = fix[s]|b;
	}
}

int binary_search(int s, int e){
	int high,low,mid;

	low = s;
	high = e;

	set(0,N-1,1);
	set(s,e,0);


	if(query(q)) return 0;

	set(s,e,1);


	while(low < high){
		mid = low+(high-low)/2;
		set(low,mid,0);

		if(query(q)){
			set(low,mid,1);
			low = mid+1;
		}else{
			set(low,mid,1);
			high = mid;
		}
	}

	assert(!fix[low]);
	fix[low] = 1;

	return 1;
}

void solve(int n, bool *ans){
	int i,grp_size;

	N = n;

	grp_size = (N+KMAX-1)/KMAX;

	for(i = 0; i < N; i+=grp_size){
		while(binary_search(i,min(N-1,i+grp_size-1)));
	}

	memcpy(ans,fix,sizeof(bool)*NMAX);
}



