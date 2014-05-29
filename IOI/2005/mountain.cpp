#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
#include <numeric>

#define NMAX 200010
#define TMAX ((1<<20)+10)

using namespace std;

class segment_tree{
private:

	int tree[TMAX];
	int inc[TMAX];
	int size[TMAX];
	int sum[TMAX];
	int time[TMAX];

	int lookup[NMAX];

	int N,T;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }

	void tree_init(int node, int s, int e){
		tree[node] = 0;
		inc[node] = 0;
		size[node] = lookup[e]-lookup[s];
		time[node] = 0;
		sum[node] = 0;

		if(s == e-1) return;

		tree_init(left(node),s,(s+e+1)/2);
		tree_init(right(node),(s+e+1)/2,e);
	}

	void tree_update(int node, int s, int e, int i, int j, int k, int diff, int ltime){
		if(time[node] < ltime){
			time[node] = ltime;
			inc[node] = diff;
			tree[node] = max(size[node]*diff,diff);
			sum[node] = size[node]*inc[node];
		}

		if(s >= j || e <= i) return;
		if(s >= i && e <= j){
			tree[node] = max(k,k*size[node]);
			inc[node] = k;
			time[node] = T;
			sum[node] = size[node]*inc[node];
			return;
		}

		int l,r;
		l = left(node);
		r = right(node);

		tree_update(l,s,(s+e+1)/2,i,j,k,inc[node],time[node]);
		tree_update(r,(s+e+1)/2,e,i,j,k,inc[node],time[node]);

		tree[node] = max(tree[l],sum[l]+tree[r]);
		sum[node] = sum[l]+sum[r];
	}

	int search(int node, int s, int e, int k, int diff, int ltime){
		if(time[node] < ltime){
			time[node] = ltime;
			inc[node] = diff;
			tree[node] = max(size[node]*diff,diff);
			sum[node] = size[node]*inc[node];
		}

		if(tree[node] <= k) return lookup[e];

		if(s == e-1){
			int i;
			assert(inc[node] >= 0);
			i = k/inc[node];
			return lookup[s]+i;
		}

		int l,r,tmp;
		l = left(node),r = right(node);

		tmp = search(l,s,(s+e+1)/2,k,inc[node],time[node]);
		if(tmp < lookup[(s+e+1)/2]) return tmp;

		k -= sum[l];
		return search(r,(s+e+1)/2,e,k,inc[node],time[node]);
	}

public:

	void init(int n, int *pts){
		N = n;
		memcpy(lookup,pts,sizeof(int)*N);
		tree_init(0,0,N-1);
	}

	void update(int i, int j, int k){
		T++;
		tree_update(0,0,N-1,i,j,k,0,-1);
	}

	int query(int k){
		return search(0,0,N-1,k,0,-1);
	}
};

int M,N;

pair<pair<int,int>,int > queries[NMAX/2];
int Q;

segment_tree T;

int pts[NMAX];

int main(){
	int i,j,k;
	char c;

	scanf("%d",&M);

	scanf(" %c",&c);
	while(c^'E'){

		if(c == 'Q'){
			scanf("%d",&k);
			queries[Q++] = make_pair(make_pair(-1,-1),k);
		}else{
			scanf("%d%d%d",&i,&j,&k);
			queries[Q++] = make_pair(make_pair(i,j+1),k);
			pts[N++] = i, pts[N++] = j+1;
		}

		scanf(" %c",&c);
	}

	pts[N++] = M+1;
	sort(pts,pts+N);
	N = unique(pts,pts+N)-pts;
	T.init(N,pts);

	for(i = 0; i < Q; ++i){
		if(queries[i].first.first < 0){
			printf("%d\n",T.query(queries[i].second)-1);
			continue;
		}
		j = lower_bound(pts,pts+N,queries[i].first.first)-pts;
		assert(pts[j] == queries[i].first.first);
		queries[i].first.second = lower_bound(pts,pts+N,queries[i].first.second)-pts;
		T.update(j,queries[i].first.second,queries[i].second);
	}

	return 0;
}
