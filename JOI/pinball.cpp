#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 100010
#define MMAX 100010
#define TMAX ((1<<18)+10)

using namespace std;

typedef long long lli;

class segment_tree{
private:

	lli tree[TMAX];
	int lookup[NMAX];
	int N;
	int upd[NMAX];


	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){return (x+1)/2-1; }

	void tree_init(int node, int s, int e){
		tree[node] = (1e15);

		if(s == e){
			lookup[s] = node;
			return;
		}

		tree_init(left(node),s,(s+e)/2);
		tree_init(right(node),(s+e)/2+1,e);
	}

	lli tree_query(int node, int s, int e, int i, int j){
		if(s > j || e < i) return (1e15);

		if(s >= i && e <= j){
			return tree[node];
		}

		return min( tree_query(left(node),s,(s+e)/2,i,j), tree_query(right(node),(s+e)/2+1,e,i,j) );
	}

public:

	void init(int n, int *C){
		N = n;
		int i;

		for(i = 0; i < N; ++i){
			upd[i] = C[i];
		}

		sort(upd,upd+N);
		N = unique(upd,upd+N)-upd;

		tree_init(0,0,N-1);
	}

	lli query(int i, int j){
		int ri,rj;

		ri = lower_bound(upd,upd+N,i)-upd;
		rj = upper_bound(upd,upd+N,j)-upd-1;

		return tree_query(0,0,N-1,ri,rj);
	}

	void update(int i, lli val){
		int x;

		x = lower_bound(upd,upd+N,i)-upd;
		assert(x < N && upd[x]==i);
		x = lookup[x];
		tree[x] = min(tree[x],val);


		while(x){
			x = parent(x);
			tree[x] = min(tree[left(x)], tree[right(x)]);
		}
	}
};


segment_tree T;

lli rht[MMAX];
lli lft[MMAX];

int A[MMAX];
int B[MMAX];
int C[MMAX];
int cost[MMAX];
int N,M;

lli compute(){
	int i;
	T.init(M,C);

	for(i = 0; i < M; ++i){
		rht[i] = (B[i] >= N ? 0 : T.query(A[i],B[i])) + cost[i];
		T.update(C[i],rht[i]);
	}

	T.init(M,C);

	for(i = 0;i  < M; ++i){
		lft[i] = (A[i] <= 1 ? 0 : T.query(A[i],B[i])) + cost[i];
		T.update(C[i],lft[i]);
	}

	lli sol;
	sol = (1e15);

	for(i = 0; i < M ;++i){
		sol = min(sol,lft[i]+rht[i]-cost[i]);
	}

	return sol >= (1e15) ? -1 : sol;
}

int main(){

	int i;

	scanf("%d%d",&M,&N);

	for(i = 0; i < M; ++i){
		scanf("%d%d%d%d",&A[i],&B[i],&C[i],&cost[i]);
	}


	printf("%lld\n",compute());
	return 0;
}
