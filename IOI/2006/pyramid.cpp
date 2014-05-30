#include <algorithm>
#include <cstdio>
#include <iostream>
#include <deque>
#include <cstring>
#include <cassert>
#include <utility>

#define NMAX 1010
#define INF (1e8)

using namespace std;

typedef pair<int,int> point;

int A[NMAX][NMAX];
int M,N;

int ins[NMAX][NMAX];
int pref[NMAX][NMAX];

int l1,l2,s1,s2;

inline int get_sum(int i, int j, int k, int l){
	return pref[k][l] + (i&&j ? pref[i-1][j-1] : 0) -\
			(i ? pref[i-1][l] : 0) - (j ? pref[k][j-1] : 0);
}

void init(){
	int i,j;

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			pref[i][j] = A[i][j] + (i ? pref[i-1][j] : 0) +\
					(j ? pref[i][j-1] : 0) - ( i&&j ? pref[i-1][j-1] : 0);
		}
	}

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			if(i+s1 > M || j+s2 > N){
				ins[i][j] = INF;
				continue;
			}

			ins[i][j] = get_sum(i,j,i+s1-1,j+s2-1);
		}
	}
}


point min_rect[NMAX][NMAX];
int min_right[NMAX][NMAX];

deque<int> Q;

int sol[NMAX];
int val[NMAX];


void min_range(int wid, int n, int *val){
	int i,k;

	Q.clear();

	for(i = n-1; i+wid > n; --i){
		while(!Q.empty() && val[Q.back()] > val[i]){
			Q.pop_back();
		}
		Q.push_back(i);
		sol[i] = -1;
	}


	for(; i >= 0; --i){
		k = i+wid-1;
		if(Q.front() == k) Q.pop_front();
		while(!Q.empty() && val[Q.back()] > val[i]){
			Q.pop_back();
		}

		Q.push_back(i);
		sol[i] = Q.front();
	}

}

void init_mins(){
	int i,j;

	for(i = 0; i < M; ++i){
		min_range(l2-s2,N,ins[i]);
		memcpy(min_right[i],sol,sizeof(sol));
	}

	for(j = 0; j < N; ++j){
		for(i = 0; i < M; ++i) val[i] = min_right[i][j] < 0 ? INF : ins[i][min_right[i][j]];
		min_range(l1-s1,M,val);
		for(i = 0; i < M; ++i) min_rect[i][j] = make_pair(sol[i],min_right[sol[i]][j]);
	}
}

int main(){
	int bi,bj,i,j,sum,rec,best;


	scanf("%d%d%d%d%d%d",&N,&M,&l2,&l1,&s2,&s1);

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&A[i][j]);
		}
	}

	init();
	init_mins();

	bi = bj = 0;
	best = 0;

	for(i = 0; i+l1 <= M; ++i){
		for(j = 0; j+l2 <= N; ++j){

			sum = get_sum(i,j,i+l1-1,j+l2-1);
			rec = ins[min_rect[i+1][j+1].first][min_rect[i+1][j+1].second];

			if(sum-rec >= best){
				best = sum-rec;
				bi = i;
				bj = j;
			}
		}
	}

	i = bi;
	j = bj;
	printf("%d %d\n%d %d\n",j+1,i+1,min_rect[i+1][j+1].second+1,min_rect[i+1][j+1].first+1);

	return 0;
}
