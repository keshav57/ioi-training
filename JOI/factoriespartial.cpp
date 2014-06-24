#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include "factories.h"
#include <cstring>
#include <vector>

#define NMAX 500010

typedef long long lli;
using namespace std;


class sparse_matrix{
private:
	int ances[NMAX][21];
	int N,log;
public:
	void init(int n, int *P){
		int i,k;

		N = n;

		for(i = 0; i < N; ++i) ances[i][0] = P[i];
		for(k = 1; (1<<k) <= N; ++k){
			for(i =0 ; i < N; ++i){
				ances[i][k] = ances[i][k-1] < 0 ? -1 : ances[ances[i][k-1]][k-1];
			}
		}
		log = k;

	}

	int query(int v, int u, int *lev){
		int k;
		if(lev[v] > lev[u]) swap(u,v);


		for(k = log-1; k >= 0; --k){
			if(ances[u][k] < 0 || lev[ances[u][k]] < lev[v]) continue;
			u = ances[u][k];
		}

		assert(lev[u] == lev[v]);
		if(u == v) return u;

		for(k = log-1; k >= 0; --k){
			if(ances[u][k] == ances[v][k]) continue;
			u = ances[u][k];
			v = ances[v][k];
		}


		return ances[v][0];
	}

};

lli cl[NMAX];
int sel[NMAX];
int pdist[NMAX];

long long root_dist[NMAX];
int par[NMAX];
int lev[NMAX];
vector<pair<int,int> > adj[NMAX];

void dfs(int v, int p){
	int i,u;

	par[v] = p;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == p) continue;

		lev[u] = lev[v]+1;
		root_dist[u] = root_dist[v] + adj[v][i].second;
		dfs(u,v);
	}
}

void dfs1(int v, int p){
	int i,u;

	cl[v] = sel[v] ? 0 : (1e15);


	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == p) continue;
		pdist[u] = adj[v][i].second;
		dfs1(u,v);
		cl[v] = min(cl[v],cl[u]+adj[v][i].second);
	}
}

void dfs2(int v, int p){
	int i;
	if(p >= 0) cl[v] = min(cl[v],cl[p]+pdist[v]);

	for(i =0 ; i < (int)adj[v].size(); ++i){
		if(adj[v][i].first == p) continue;
		dfs2(adj[v][i].first,v);
	}
}
int N;

sparse_matrix M;

void Init(int n, int A[], int B[], int D[]){
	N = n;
	int i;

	for(i = 0; i < N; ++i){
		adj[A[i]].push_back(make_pair(B[i],D[i]));
		adj[B[i]].push_back(make_pair(A[i],D[i]));
	}
	dfs(0,-1);
	M.init(N,par);
}

long long Query(int S, int X[], int T, int Y[]){
	int i,j,l;
	long long mdist,dist;

	if(S*T <= 5000){

		mdist = (1e15);

		for(i = 0; i < S; ++i){
			for(j = 0; j < T; ++j){
				l = M.query(X[i],Y[j],lev);
				assert(l >= 0);
				dist = root_dist[X[i]] + root_dist[Y[j]] - 2*root_dist[l];
				mdist = min(mdist,dist);
			}
		}


		return mdist;
	}

//	assert(N <= 5010);

	for(i = 0; i < S; ++i){
		sel[X[i]] = 1;
	}

	dfs1(0,-1);
	dfs2(0,-1);

	mdist = (1e15);

	for(i =0 ; i <T; ++i){
		mdist = min(mdist,cl[Y[i]]);
//		cout << Y[i] << " " << cl[Y[i]] << endl;
	}



	for(i = 0; i < S; ++i) sel[X[i]] = 0;


	return mdist;
}
