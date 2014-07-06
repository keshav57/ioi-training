#include <algorithm>
#include <cassert>
#include <cstring>
#include <set>
#include <vector>
#include "advisor.h"
#include <iostream>

#define NMAX 100010

using namespace std;

int last_occ[NMAX];
vector<int> occ[NMAX];

set<pair<int,int> > next;
int sel[NMAX];

int passive[NMAX];
int start[NMAX];

int deleted;

int get_deleted(){
	return deleted;
}

void ComputeAdvice(int *C, int N, int K, int M) {
	int i,k;

	for(i = 0; i < N; ++i) occ[i].push_back((1e9));

	for(i = N-1; i >= 0; --i){
		occ[C[i]].push_back(i);
	}

	for(i = 0; i < K; ++i){
		next.insert(make_pair(occ[i].back(),i));
		sel[i] = 1;
	}

	memset(last_occ,-1,sizeof(last_occ));

	set<pair<int,int> >::iterator it;

	for(i = 0; i  < N; ++i){
		assert(occ[C[i]].back() == i);
		occ[C[i]].pop_back();

		if(sel[C[i]]){
			next.erase(make_pair(i,C[i]));
			next.insert(make_pair(occ[C[i]].back(),C[i]));
			last_occ[C[i]] = i;
			continue;
		}

		it = next.end(); --it;
		k = it->second;
		next.erase(it);
		++deleted;

		(last_occ[k] < 0 ? start[k] : passive[last_occ[k]]) = 1;

		sel[k] = 0;
		sel[C[i]] = 1;
		next.insert(make_pair(occ[C[i]].back(),C[i]));
		last_occ[C[i]] = i;
	}

	for(it = next.begin(); it != next.end(); ++it){
		k = it->second;
		(last_occ[k] < 0 ? start[k] : passive[last_occ[k]]) = 1;
	}


	for(i = 0; i < K; ++i){
		WriteAdvice(start[i]);
	}

	for(i =0 ; i < N; ++i){
		WriteAdvice(passive[i]);
	}
}
