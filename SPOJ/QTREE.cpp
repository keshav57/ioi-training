/*
 Created By: Malvika Joshi
 Problem: Query on a Tree
 Link: http://www.spoj.com/problems/QTREE/
*/


//Heavy Light Decomposition

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#include <iostream>
#include <utility>

#define NMAX 10010
#define TMAX (1<<15)
#define LOGN 15

using namespace std;

class segment_tree{
private:
	int tree[TMAX];
	int lookup[NMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	void tree_init(int node, int s, int e, int *A){
		if(s == e){
			tree[node] = A[s];
			lookup[s] = node;
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		tree_init(l,s,(s+e)/2,A);
		tree_init(r,(s+e)/2+1,e,A);

		tree[node] = max(tree[l],tree[r]);
	}

	int tree_query(int node, int s, int e, int i, int j){
		if(s > j || e < i) {
			return -1;
		}
		if(s >= i && e <= j){
			return tree[node];
		}

		int l,r;

		l = tree_query(left(node),s,(s+e)/2,i,j);
		r = tree_query(right(node),(s+e)/2+1,e,i,j);

		return max(l,r);
	}

public:

	void init(int n, int *A){
		N = n;
		memset(tree,-1,sizeof(int)*TMAX);
		tree_init(0,0,N-1,A);
	}

	int query(int i, int j){
		return tree_query(0,0,N-1,i,j);
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

class sparse_table{
private:
	int ancestor[NMAX][LOGN];
	int N;

public:
	void init(int n, int *par){
		int i,j;

		N = n;

		memset(ancestor,-1,sizeof(int)*NMAX*LOGN);

		for(i = 0; i < N; ++i) ancestor[i][0] = par[i];

		for(j = 1; (1<<j) < N; ++j){
			for(i = 0; i < N; ++i){
				if(ancestor[i][j-1] < 0) continue;
				ancestor[i][j] = ancestor[ ancestor[i][j-1] ][j-1];
			}
		}
	}

	int query(int u, int v, int *lev){
		int i;

		if(lev[u] < lev[v]) swap(u,v);

		for(i = LOGN-1; i >= 0; --i){
			if(lev[u]-(1<<i) < lev[v]) continue;
			u = ancestor[u][i];
		}

		if(u == v) return u;

		for(i = LOGN-1; i >= 0; --i){
			if(ancestor[u][i] == ancestor[v][i]) continue;
			u = ancestor[u][i];
			v = ancestor[v][i];
		}

		return ancestor[u][0];
	}
};

int ordered_cost[NMAX];
int pos[NMAX];
int P;

int chain[NMAX];
int chain_head[NMAX];
int C;

int par[NMAX];
int ssize[NMAX];
int level[NMAX];

segment_tree T;
sparse_table lca;

vector<int> adj[NMAX];
vector<int> edge_cost[NMAX];
int N;

pair<int,int> edges[NMAX];

void hld(int v, int cost){
	int i,u,sp,c2;

	if(chain_head[C] < 0){
		chain_head[C] = v;
	}

	chain[v] = C;
	ordered_cost[P] = cost;
	pos[v] = P++;

	sp = -1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(u == par[v]) continue;
		if(sp >= 0 && ssize[u] < ssize[sp]) continue;
		sp = u;
		c2 = edge_cost[v][i];
	}

	if(sp < 0) return;

	hld(sp,c2);

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(u == par[v] || u == sp) continue;
		C++;
		hld(u,edge_cost[v][i]);
	}
}

void dfs(int v){
	int i,u;

	ssize[v] = 1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(u == par[v]) continue;
		par[u] = v;
		level[u] = level[v]+1;
		dfs(u);
		ssize[v] += ssize[u];
	}
}

void init(){
	level[0] = 0;
	par[0] = -1;

	memset(chain_head,-1,sizeof(int)*NMAX);

	dfs(0);
	hld(0,-1);

	lca.init(N,par);
//	assert(P == N);
	T.init(P,ordered_cost);
}


int query_path(int u, int v){
	if(u == v) return -1;

	int uchain,vchain,mcost;

	mcost = -1;
	uchain = chain[u];
	vchain = chain[v];

	int cn = 0;


	while(uchain != vchain){
		mcost = max(mcost, T.query(pos[chain_head[uchain]],pos[u]) );
		u = par[chain_head[uchain]];
		uchain = chain[u];
		++cn;
		assert(cn <= LOGN);
	}

	if(u != v) mcost = max(mcost, T.query(pos[v]+1,pos[u]));

	return mcost;
}

int query(int u, int v){
	int l;
	l = lca.query(u,v,level);
	return max( query_path(u,l), query_path(v,l) );
}

void update(int i, int val){
	int u,v;

	u = edges[i].first, v = edges[i].second;
	if(par[v] == u) swap(u,v);

	T.update(pos[u],val);
}

int main(){
	int i,t,c,j;
	char typ[10];

	scanf("%d",&t);

	while(t--){

		for(i = 0; i < N; ++i){
			adj[i].clear();
			edge_cost[i].clear();
		}

		P= C = 0;

		scanf("%d",&N);

		for(i = 0; i < N-1; ++i){
			scanf("%d%d%d",&edges[i].first,&edges[i].second,&c);
			--edges[i].first,--edges[i].second;
			adj[edges[i].first].push_back(edges[i].second);
			edge_cost[edges[i].first].push_back(c);
			edge_cost[edges[i].second].push_back(c);
			adj[edges[i].second].push_back(edges[i].first);
		}

		init();

		while(1){
			scanf("%s",typ);

			if(typ[0] == 'D')	break;


			if(typ[0] == 'Q'){
				scanf("%d%d",&i,&j);
				--i,--j;
				printf("%d\n",query(i,j));
				continue;
			}

			scanf("%d%d",&i,&c);
			--i;
			update(i,c);
		}

	}

	return 0;
}
