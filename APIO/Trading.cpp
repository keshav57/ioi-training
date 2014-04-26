/*
 Created By: Malvika Joshi
 Problem: Trading (APIO-2014 Practice)
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>

#define NMAX 300010
#define TMAX ((1<<20)+10)
#define INF (int)(1e9)

using namespace std;

class segment_tree{
private:
	int tree[TMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	int tree_update(int node, int s, int e, int i, int j, int x){
		if(s > j || e < i) return 0;

		if(s >= i && e <= j){
			tree[node] = max(tree[node],x);
			return e-s+1;
		}

		int used;

		used = tree_update(left(node),s,(s+e)/2,i,j,x);
		used += tree_update(right(node),(s+e)/2+1,e,i,j,x+used);

		return used;
	}

	int tree_query(int node, int s, int e, int i){
		if(s > i || e < i) return 0;

		if(s == i && e == i){
			return tree[node];
		}

		int rank,q;

		rank = i-s;

		q = max(	tree_query(left(node),s,(s+e)/2,i), \
					tree_query(right(node),(s+e)/2+1,e,i) );

		return max(q,tree[node]+rank);
	}

public:

	void init(int n){
		for(int i = 0; i < TMAX; ++i) tree[i] = -INF;
		N = n;
	}

	void update(int i, int j, int x){
		tree_update(0,0,N-1,i,j,x);
	}

	int query(int i){
		return tree_query(0,0,N-1,i);
	}
};

segment_tree T;
int N,M;

int main(){
	int i,j,x;

	scanf("%d%d",&N,&M);

	T.init(N);

	while(M--){
		scanf("%d%d%d",&i,&j,&x);
		--i,--j;
		T.update(i,j,x);
	}

	for(i = 0 ; i < N; ++i){
		printf("%d ",T.query(i));
	}
	printf("\n");

	return 0;
}
