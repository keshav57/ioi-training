#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>
#include "secret.h"

#define TMAX ((1<<11)+10)

using namespace std;

class segment_tree{
public:

	vector<int> tree[TMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }

	void tree_init(int node, int s, int e, int dir ,int *A){


		if(s == e){
			tree[node].push_back(A[s]);
			return;
		}

		int l,r;

		l = left(node)  , r = right(node);
		tree_init(l,s,(s+e)/2,-1,A);
		tree_init(r,(s+e)/2+1,e,1,A);

		if(!dir) return;

		int i,tmp;

		i = (dir < 0 ? e : s);
		tree[node].push_back(A[i]);

		for(i += dir; i >= s && i <= e; i += dir){
			tmp = (dir < 0 ? Secret(A[i],tree[node].back()) : Secret(tree[node].back(),A[i]));
			tree[node].push_back(tmp);
		}
	}

	int tree_query(int node, int s, int e, int dir, int i, int j){
		if(s > j || e < i) return -1;

		if(!dir || (dir < 0 && j < e) || (dir > 0 && i > s)){
			int l,r;

			l = tree_query(left(node),s,(s+e)/2,-1,i,j);
			r = tree_query(right(node),(s+e)/2+1,e,1,i,j);
			assert(l >= 0 || r >= 0);
			return l < 0 ? r : ( r < 0 ? l : Secret(l,r));
		}


		if(dir < 0){
			assert(s <= i && e >= i);
			return tree[node][e-i];
		}

		assert(s <= j && e >= j);
		return tree[node][j-s];
	}

public:

	void init(int n,int *A){
		N = n;
		tree_init(0,0,N-1,0,A);
	}

	int query(int i, int j){
		return tree_query(0,0,N-1,0,i,j);
	}

};

segment_tree T;

void Init(int N, int A[]) {
	T.init(N,A);
}

int Query(int L, int R) {
	return T.query(L,R);
}

