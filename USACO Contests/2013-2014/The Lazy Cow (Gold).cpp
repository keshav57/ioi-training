/*
 Created By: Malvika Joshi
 Problem: The Lazy Cow (March-2014 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=418
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <iostream>

#define TMAX ((1<<22)+10)
#define NMAX 100010

using namespace std;

class segment_tree{
private:

	int tree[TMAX];
	int inc[TMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }

	void tree_update(int s, int e, int node, int i, int j, int val){
		assert(node < TMAX);
		if(s > j || e < i) return;

		if(s >= i && e <= j){
			tree[node] += val;
			inc[node] += val;
			assert(inc[node]>=0);
			assert(tree[node]>=0);
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		tree_update(s,(s+e)/2,l,i,j,val);
		tree_update((s+e)/2+1,e,r,i,j,val);
		tree[node] = max(tree[l],tree[r])+inc[node];
	}

public:

	void init(int n){
		N = n;
		memset(tree,0,sizeof(int)*TMAX);
		memset(inc,0,sizeof(int)*TMAX);
	}

	int query(){
		return tree[0];
	}

	void update(int i, int j, int val){
		tree_update(0,N-1,0,i,j,val);
	}
};

segment_tree T;

pair<pair<int,int>, int> det[NMAX];
int N,K;

int main(){
	int i,x,y,g,j,sol;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N; ++i){
		scanf("%d%d%d",&g,&x,&y);
		det[i] = make_pair(make_pair(x-y,x+y),g);
	}

	sort(det,det+N);
	K *= 2;

	j = 0;

	T.init(det[N-1].first.second);

	sol = 0;
	for(i = 0; i < N; ++i){
		while(j < N && det[i].first.first-det[j].first.first > K){
			T.update(max(0,det[j].first.second-K),det[j].first.second,-det[j].second);
			++j;
		}
		T.update(max(0,det[i].first.second-K),det[i].first.second,det[i].second);
		sol = max(sol,T.query());
	}

	printf("%d\n",sol);

	return 0;
}

