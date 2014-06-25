#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include "factories.h"
#include <vector>
#include <cstring>

#define NMAX 500010

using namespace std;
typedef long long lli;

int ssize[NMAX];
lli root_dist[NMAX];
int par[NMAX];

vector<pair<int,int> > adj[NMAX];
int N;

int dtime[NMAX];
int cur_time;

int chain[NMAX];
int chain_head[NMAX];
int C;

int upd[NMAX];
int res[NMAX];
int R;

int dfs(int v){
	int u,i;

	ssize[v] = 1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == par[v]) continue;
		par[u] = v;
		root_dist[u] = root_dist[v] + adj[v][i].second;
		ssize[v] += dfs(u);
	}

	return ssize[v];
}

void hld(int v){
	int i,u,sp;

	if(chain_head[C] < 0) chain_head[C] = v;

	chain[v] = C;
	sp = -1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == par[v]) continue;
		if(sp < 0 || ssize[u] > ssize[sp]) sp = u;
	}

	if(sp < 0) return;

	hld(sp);

	for(i =0 ; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == sp || u == par[v]) continue;
		C++;
		hld(u);
	}
}

void order(int v){
	int i,sp,u;

	dtime[v] = cur_time++;
	sp = -1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;

		if(u == par[v]) continue;

		if(chain[u] == chain[v]){
			sp = u;
			continue;
		}

		order(u);
	}

	if(sp >= 0) order(sp);
}

vector<pair<int,lli> > stack[NMAX];

void update_up(int x){
	int vchain,v;
	lli dist,tmp;

	v = x;
	while(v >= 0){
		vchain = chain[v];
		dist = root_dist[x]-root_dist[v];

		tmp = stack[vchain].empty() ? (1e18) :\
				root_dist[v]-root_dist[ stack[vchain].back().first ] + stack[vchain].back().second;

		if(dist < tmp){
			if(!upd[vchain]) res[R++] = vchain;
			upd[vchain] = 1;
			stack[vchain].push_back(make_pair(v,dist));
		}

		v = par[chain_head[vchain]];
	}
}

lli query_up(int x){
	int vchain,v;
	lli dist,mdist,tmp;

	mdist = (1e18);

	v = x;
	while(v >= 0){
		vchain = chain[v];
		dist = root_dist[x]-root_dist[v];

		while(!stack[vchain].empty() && dtime[stack[vchain].back().first] > dtime[v]){
			stack[vchain].pop_back();
		}

		tmp = stack[vchain].empty() ? (1e18) :\
				root_dist[v]-root_dist[ stack[vchain].back().first ] + stack[vchain].back().second;

		mdist = min(mdist,dist+tmp);
		v = par[chain_head[vchain]];
	}

	return mdist;
}

lli min_dist(int S, int X[], int T, int Y[]){
	int i;
	lli mdist;

	mdist = (1e18);

	for(i = 0; i < T; ++i){
		update_up(Y[i]);
	}

	for(i = S-1; i >= 0; --i){
		mdist = min(mdist,query_up(X[i]));
	}

	return mdist;
}

void Init(int n, int A[], int B[], int D[]){
	int i;

	N = n;

	for(i = 0 ; i < N-1; ++i){
		adj[A[i]].push_back(make_pair(B[i],D[i]));
		adj[B[i]].push_back(make_pair(A[i],D[i]));
	}

	par[0] = -1;
	dfs(0);
	memset(chain_head,-1,sizeof(chain_head));
	hld(0);
	order(0);
}

int compare(int a, int b){
	return dtime[a] < dtime[b];
}

void clear(){
	while(R--){
		upd[res[R]] = 0;
		stack[res[R]].clear();
	}
	R = 0;
}

lli Query(int S, int X[], int T, int Y[]){
	lli mdist;

	sort(X,X+S,compare);
	sort(Y,Y+T,compare);

	mdist = min_dist(S,X,T,Y);
	clear();
	mdist = min(mdist, min_dist(T,Y,S,X));
	clear();

	return mdist;
}
