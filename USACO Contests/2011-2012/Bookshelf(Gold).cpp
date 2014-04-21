/*
 Created By: Malvika Joshi
 Problem: Bookshelf (US-Open 2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=138
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

#define NMAX 100010
#define TMAX (1<<18)

#define INF (long long)(1e12)

typedef long long lli;
using namespace std;

class segment_tree{
private:
	lli height[TMAX];
	lli dp[TMAX];

	int lookup[NMAX];
	char blocked[TMAX];

	int N;

	inline int left(int p){ return (p+1)*2-1; }
	inline int right(int p){ return (p+1)*2; }
	inline int parent(int p){ return (p+1)/2-1; }

	void tree_init(int node, int s, int e){
		height[node] = dp[node] = INF;
		blocked[node] = 0;
		if(s == e){
			lookup[s] = node;
			return;
		}

		tree_init(left(node),s,(s+e)/2);
		tree_init(right(node),(s+e)/2+1,e);
	}

	void tree_block(int node, int s, int e, int i, int j, lli k){

		if(s > j || e < i) return;

		if(s >= i && e <= j){
			blocked[node] = 1;
			height[node] = k;
			dp[node] = dp[lookup[s]];
			return;
		}

		assert(!blocked[node]);

		int l,r;

		l = left(node);
		r=  right(node);

		tree_block(l,s,(s+e)/2,i,j,k);
		tree_block(r,(s+e)/2+1,e,i,j,k);

		if(height[l]+dp[l] < height[r]+dp[r]){
			height[node] = height[l];
			dp[node] = dp[l];
		}else{
			height[node] = height[r];
			dp[node] = dp[r];
		}
	}

	lli tree_query(int node, int s, int e, int i, int j, lli k){
		if(s > j || e < i) return INF;

		if(s >= i && e <= j){
			return k >= 0 ? dp[lookup[s]]+k : dp[node]+height[node];
		}

		lli l,r;

		l = left(node);
		r = right(node);

		if(k < 0 && blocked[node]) k = height[node];		//ln 51

		l = tree_query(left(node),s,(s+e)/2,i,j,k);
		r = tree_query(right(node),(s+e)/2+1,e,i,j,k);

		return min(l,r);
	}

public:

	void init(int n){
		N = n;
		tree_init(0,0,N-1);
	}

	lli query(int i, int j){
		return tree_query(0,0,N-1,i,j,-1);
	}

	void block(int i, int j, lli k){
		tree_block(0,0,N-1,i,j,k);
	}

	void update(int x, lli dp_val, lli ht_val){
		int p,l,r;

		p = lookup[x];
		dp[p] = dp_val;
		height[p] = ht_val;

		while(p){
			p = parent(p);
			assert(!blocked[p]);

			l = left(p);
			r = right(p);

			if(height[l]+dp[l] < height[r]+dp[r]){
				height[p] = height[l];
				dp[p] = dp[l];
			}else{
				height[p] = height[r];
				dp[p] = dp[r];
			}
		}
	}
};

int height[NMAX];
int prev[NMAX];

int width[NMAX];
int lim[NMAX];

segment_tree T;

int N,L;

void init(){
	int i,n;
	lli sum;
	int stack[NMAX];

	n = 0;

	for(i = 0; i < N; ++i){
		while(n && height[stack[n-1]] < height[i]){
			--n;
		}
		prev[i] = n ? stack[n-1] : -1;
		stack[n++] = i;
	}

	lim[0] = 0;
	sum = width[0];

	for(i = 1; i < N; ++i){
		sum += width[i];
		lim[i] = lim[i-1];

		while(sum > L){
			sum -= width[lim[i]++];
		}
	}

	T.init(N);
}

lli min_ht[NMAX];

lli dp(){
	int i;

	T.update(0,0,height[0]);
	min_ht[0] = height[0];

	for(i = 1; i < N; ++i){
		T.update(i,min_ht[i-1],height[i]);
		T.block(prev[i]+1,i,height[i]);
		min_ht[i] = T.query(lim[i],i);
	}

	return min_ht[N-1];
}

int main(){

	int i;

	scanf("%d%d",&N,&L);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&height[i],&width[i]);
	}

	init();
	printf("%lld\n",dp());

	return 0;
}
