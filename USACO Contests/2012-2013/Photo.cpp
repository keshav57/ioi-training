/*
 Created By: Malvika Joshi
 Problem: Photo (Us-Open 2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=285
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

#define NMAX 200010
#define MMAX 100010
#define TMAX ((1<<19)+10)

using namespace std;

inline int left(int x){ return (x+1)*2-1; }
inline int right(int x){ return (x+1)*2; }
inline int parent(int x){ return (x+1)/2-1; }

class segment_tree{
private:

	int tree[TMAX];
	int lookup[NMAX];
	int N;

	void tree_init(int s, int e, int node){
		tree[node] = -NMAX;
		if(s == e){
			lookup[s] = node;
			return;
		}

		tree_init(s,(s+e)/2, left(node));
		tree_init((s+e)/2+1,e,right(node));
	}

	int tree_query(int s, int e, int i, int j, int node){
		if(s > j || e < i) return -NMAX;

		if(s >= i && e <= j){
			return tree[node];
		}

		int l,r;

		l = tree_query(s,(s+e)/2,i,j,left(node));
		r = tree_query((s+e)/2+1,e,i,j,right(node));

		return max(l,r);
	}

public:

	void  init(int n){
		N = n;
		tree_init(0,N,0);
	}

	int query(int i, int j){
		return tree_query(0,N,i,j,0);
	}

	void update(int i, int val){
		int x;

		x = lookup[i];
		tree[x] = val;

		while(x){
			x = parent(x);
			tree[x] = max(tree[left(x)],tree[right(x)]);
		}
	}
};

segment_tree T;

int prev[NMAX];
int limit[NMAX];
int N;

pair<int,int> photos[MMAX];
int M;

void init(){
	T.init(N);

	int i,k;

	sort(photos,photos+M);

	for(i = 0; i <= N; ++i){
		prev[i] = i-1;
		limit[i] = 0;
	}

	k = 1;
	for(i = 0; i < M; ++i){
		for(k = max(k,photos[i].first); k <= photos[i].second; ++k){
			prev[k] = photos[i].first-1;
		}
	}

	k = N;
	for(i = M-1; i >= 0; --i){
		for(; k > photos[i].second; --k){
			limit[k] = photos[i].first;
		}
	}
}

int max_spots[NMAX];

int dp(){
	int i,spots;

	max_spots[0] = 0;
	T.update(0,0);

	for(i = 1; i <= N; ++i){
		max_spots[i] = limit[i] <= prev[i] ? T.query(limit[i],prev[i])+1: -NMAX;
		T.update(i,max_spots[i]);
	}

	spots = T.query(photos[M-1].first,N);

	return max(spots,-1);
}


int main(){
	int i;

	scanf("%d%d",&N,&M);

	for(i = 0; i < M; ++i){
		scanf("%d%d",&photos[i].first,&photos[i].second);
	}

	init();
	printf("%d\n",dp());


	return 0;
}

