/*
 CAR
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

#define NMAX 20010
#define MMAX 52

using namespace std;

vector<int> adj[MMAX];

int occ[MMAX];

int N;

int visited[NMAX];
int del[MMAX];
int W,D;

int rem[NMAX];
int R;

int A[NMAX];
int T;

int V;

vector<pair<int,int> > moves[NMAX];
int round;

int delete_cycle(int w){
	int i;

	D = 0;

	while(rem[R]) ++R;
	i = R;

/*
10 4 4
2 3 3 4 4 2 1 1 3 1
*/

	while(D < w){
		del[D++] = i;
		assert(!adj[A[i]].empty());
		while(visited[adj[A[i]].back()] || rem[adj[A[i]].back()]){
			adj[A[i]].pop_back();
			assert(!adj[A[i]].empty());
		}
		i = adj[A[i]].back();
		visited[i] = 1;

		if(i == R) break;
	}

	assert(D);
	//found a path, only W-1 can be deleted

	if(i != R){
		visited[i] = 0;
		A[del[0]] = A[del[D-1]];

		for(i = 1; i < D; ++i){
			rem[del[i]] = 1;
			--V;
			moves[round-1].push_back(make_pair(del[i-1],del[i]));
			visited[del[i]] = 0;
		}
		visited[del[0]] = 0;
		moves[round-1].push_back(make_pair(del[i-1],del[0]));

		return D;
	}

	for(i = 0; i < D-1; ++i){
		rem[del[i]] = 1;
		--V;
		moves[round-1].push_back(make_pair(del[i],del[i+1]));
		visited[del[i]] = 0;
	}
	rem[del[D-1]] = 1;
	--V;
	moves[round-1].push_back(make_pair(del[i],del[0]));
	visited[del[i]] = 0;

	return D;
}

void init(){
	int i,k;

	for(i =0 ; i < N; ++i){
		occ[A[i]+1]++;
	}

	for(i =1 ; i <= T; ++i){
		occ[i] += occ[i-1];
	}

	for(i = 0; i < N; ++i){
		if(i >= occ[A[i]] && i < occ[A[i]+1]){
			//i is already in its proper place
			--V;
			rem[i] = 1;
		}
	}

	R = 0;
	for(i = 0; i < T; ++i){
		for(k = occ[i]; k < occ[i+1]; ++k){
			adj[i].push_back(k);
		}
	}
}

int main(){
	int i,w,k;

	scanf("%d%d%d",&N,&T,&W);

	for(i= 0 ; i < N; ++i){
		scanf("%d",&A[i]);
		--A[i];
	}

	V = N;
	init();
	w = 0;

	round = 0;
	while(V){
		if(w < 2){
			w = W;
			round++;
		}

		w -= delete_cycle(w);
		assert(w >= 0);
	}

	printf("%d\n",round);
	for(i = 0; i < round; ++i){
		sort(moves[i].begin(),moves[i].end());

		cout << moves[i].size() << " ";
		for(k = 0; k < moves[i].size(); ++k){
			printf("%d %d ",moves[i][k].first+1,moves[i][k].second+1);
		}
		printf("\n");
	}

	return 0;
}
