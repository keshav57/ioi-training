/*
 Created By: Malvika Joshi
 Problem: Optimal Milking (December-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=365
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>

#define NMAX 40010
#define TMAX (1<<17)

using namespace std;
typedef long long lli;

class segment_tree{
private:

	lli in_range[TMAX];
	lli wo_left[TMAX];
	lli wo_right[TMAX];
	lli wo_both[TMAX];
	int lookup[NMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	void tree_init(int node, int s, int e, int *A){
		if(s == e){
			in_range[node] = A[s];
			lookup[s] = node;
			return;
		}

		int l,r;

		l = left(node), r = right(node);

		tree_init(l,s,(s+e)/2,A);
		tree_init(r,(s+e)/2+1,e,A);

		in_range[node] = max(in_range[l]+wo_left[r], wo_right[l]+in_range[r]);

		wo_left[node] = max(wo_left[l]+wo_left[r], wo_both[l]+in_range[r]);
		wo_right[node] = max(wo_right[r]+wo_right[l], wo_both[r]+in_range[l]);

		wo_both[node] = max(wo_both[l]+wo_right[r],wo_left[l]+wo_both[r]);
	}

public:

	void init(int n, int *A){
		N = n;
		memset(in_range,0,sizeof(lli)*TMAX);
		memset(wo_left,0,sizeof(lli)*TMAX);
		memset(wo_right,0,sizeof(lli)*TMAX);
		memset(wo_both,0,sizeof(lli)*TMAX);
		tree_init(0,0,N-1,A);
	}

	lli query(){
		return in_range[0];
	}

	void update(int i, int val){
		int x,l,r;

		x = lookup[i];
		in_range[x] = val;

		while(x){
			x = parent(x);
			l = left(x);
			r = right(x);

			in_range[x] = max(in_range[l]+wo_left[r], wo_right[l]+in_range[r]);

			wo_left[x] = max(wo_left[l]+wo_left[r], wo_both[l]+in_range[r]);
			wo_right[x] = max(wo_right[r]+wo_right[l], wo_both[r]+in_range[l]);

			wo_both[x] = max(wo_both[l]+wo_right[r],wo_left[l]+wo_both[r]);
		}
	}

};

segment_tree tree;

int A[NMAX];
int N,Q;

int main(){
	int i;
	lli tot;

	scanf("%d%d",&N,&Q);

	for(i = 0; i < N; ++i){
		scanf("%d",&A[i]);
	}

	tree.init(N,A);

	tot = 0ll;

	while(Q--){
		scanf("%d",&i);
		--i;
		scanf("%d",&A[i]);
		tree.update(i,A[i]);
		tot += tree.query();
	}

	printf("%lld\n",tot);

	return 0;
}
