#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>
#include <utility>

#define NMAX 20010

using namespace std;

int next[NMAX];
int rem[NMAX];
vector<pair<int,int> > moves[NMAX];

int N,V,M,D;

int find_cycle(int w){
	int i,len;

	while(rem[V]) ++V;

	len = 0;
	i = V;
	do{
		rem[i] = 1;
		++D;
		++len;
		moves[M].push_back(make_pair(i,next[i]));
		i = next[i];
		if(len >= w) break;
	}while(i != V);

	if(i == V) return len;

	i = moves[M].back().first;
	moves[M].pop_back();
	rem[V] = 0;
	--D;
	next[V] = next[i];
	moves[M].push_back(make_pair(i,V));

	return len;
}

int pref[NMAX];
int A[NMAX];
int K;

void init(){
	int i;

	for(i = 0; i < N; ++i){
		pref[A[i]]++;
	}

	for(i = 1; i < K; ++i){
		pref[i] += pref[i-1];
	}

	for(i = 0; i < N; ++i){
		next[i] = --pref[A[i]];
	}

}

int W;

int main(){
	int i,w;

	scanf("%d%d%d",&N,&K,&W);

	for(i = 0; i < N; ++i){
		scanf("%d",&A[i]);
		--A[i];
	}

	init();

	w = W;
	while(D < N){
		if(w < 2){
			w = W;
			++M;
		}
		w -= find_cycle(w);
	}
	++M;

	printf("%d\n",M);

	for(int k = 0; k < M; ++k){
		sort(moves[k].begin(),moves[k].end());
		printf("%u ",moves[k].size());
		for(i = 0; i < moves[k].size(); ++i){
			printf("%d %d ",moves[k][i].first+1,moves[k][i].second+1);
		}
		printf("\n");
	}

	return 0;
}
