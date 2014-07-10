#include <iostream>
#include <algorithm>
#include "cave.h"
#include <cstring>
#include <cassert>
#include <cstdio>
#include <utility>

#define NMAX 5010


int state[NMAX];
int conn[NMAX];
int correct_pos[NMAX];

int swt[NMAX];

void toggle(int i, int j){
	for(; i <= j; ++ i){
		state[i] = correct_pos[i] < 0 ? state[i]^1 : correct_pos[i];
	}
}

int N,last;

int search(int low, int high, int cl, int door){
	if(high >= low){
		conn[low] = door;
		swt[door] = low;
		correct_pos[low] = state[low]^cl;
		return low;
	}

	int mid,ccl;

	mid = low+(high-low)/2;

	toggle(low,mid);
	last = tryCombination(state);
	if(last < 0) last = N;

	assert(last >= door);
	ccl = last <= door;

	return ccl^cl ? search(low,mid,ccl,door) : search(mid+1,high,ccl,door);
}

void exploreCave(int N) {
	memset(correct_pos,-1,sizeof(correct_pos));

	int i,last;

	last = tryCombination(state);
	for(i = 0; i < N; ++i){
		int s = search(0,N-1,last,i);
		cout << i << " " << s << endl;
	}

	answer(state,conn);
}
