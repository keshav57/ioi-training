/*
 Created By: Malvika Joshi
 Problem: Escape (IOITC-2010 Final-3)
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

#define MAXN 100010
#define MAXT ((1<<18)+10)
#define INF (long long)(1e18);

typedef long long lli;

using namespace std;

class segment_tree{

private:
	int lookup[MAXN];

	lli add[MAXT];
	lli tree[MAXT];

	inline int left(int p){ return (p+1)*2-1; }
	inline int right(int p){ return (p+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

public:

	void init(int node, int s, int e){
		add[node] = 0;
		tree[node] = INF;

		if(s == e){
			lookup[s] = node;
			return;
		}

		init(left(node),s,(s+e)/2);
		init(right(node),(s+e)/2+1,e);
	}

	void point_update(int i, lli val){
		int p;
		p = lookup[i];
		tree[p] = val;

		while(p){
			p = parent(p);
			tree[p] = min(tree[left(p)],tree[right(p)])+add[p];
		}
	}

	void range_update(int node, int s, int e, int i, int j, lli val){
		if(s > j || e < i) return;

		if(s >= i && e <= j){
			add[node] += val;
			tree[node] += val;
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		range_update(l,s,(s+e)/2,i,j,val);
		range_update(r,(s+e)/2+1,e,i,j,val);

		tree[node] = min(tree[l],tree[r]) + add[node];
	}

	lli query(int node, int s, int e, int i, int j){
		if(s > j || e < i) return INF;

		if(s >= i && e <= j) return tree[node];

		lli l,r;

		l = query(left(node),s,(s+e)/2,i,j);
		r = query(right(node),(s+e)/2+1,e,i,j);

		return min(l,r)+add[node];
	}
};


lli pref[MAXN];
vector<pair<int,int> > ends[MAXN];
segment_tree T;

lli min_bribe[MAXN];

int left[MAXN];
int N;

lli dp(){

	int i,k;

	min_bribe[0] = 0;
	T.point_update(0,min_bribe[0]+pref[0]);

	for(i = 1; i < N; ++i){
		for(k = 0; k < (int)ends[i].size(); ++k)
			T.range_update(0,0,N-1,ends[i][k].first,i-1,-ends[i][k].second);

		min_bribe[i] = T.query(0,0,N-1,left[i],i-1);
		T.point_update(i,min_bribe[i]+pref[i]);
	}

	return min_bribe[N-1];
}

int main(){

	int i,j,k,P;

	scanf("%d%d",&N,&P);

	for(i = 1; i < N; ++i){
		scanf("%d",&left[i]);
		--left[i];
	}

	while(P--){
		scanf("%d%d%d",&i,&j,&k);
		--i,--j;
		pref[i] += k;
		pref[j+1] -= k;
		ends[j+1].push_back(make_pair(i,k));
	}

	for(i = 1; i < N; ++i){
		pref[i] += pref[i-1];
	}


	T.init(0,0,N-1);

	printf("%lld\n",dp());

	return 0;
}
