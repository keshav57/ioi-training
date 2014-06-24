#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <cstdio>
#include <cstring>

#define NMAX 200010
#define KMAX 1000010
#define INF (1e9)

using namespace std;

int rem[NMAX];
int visited[NMAX];

vector<pair<int,int> > adj[NMAX];
int size[NMAX];
int out[NMAX];
int max_sub[NMAX];
int N,K;

void init(int v){
	int i,u;

	size[v] = 1;
	visited[v] = 1;
	max_sub[v] = 0;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(rem[u]){
			swap(adj[v][i],adj[v].back());
			adj[v].pop_back();
			--i;
			continue;
		}
		if(visited[u]) continue;
		init(u);
		size[v] += size[u];
		max_sub[v] = max(max_sub[v],size[u]);
	}
}

int best_root(int v, int p){
	int i,u,k,root;

	out[v] = p >= 0 ? out[p]+size[p]-size[v] : 0;
	max_sub[v] = max(max_sub[v],out[v]);
	root = v;

	for(i =0 ; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == p) continue;
		k = best_root(u,v);
		if(max_sub[k] < max_sub[root]) root = k;
	}

	return root;
}

int min_len[KMAX];
int upd[NMAX];
int U;

int cur_len[KMAX];
int stack[NMAX];
int S;

void dfs(int v, int p, int dist, int len){
	int i,u;
	if(dist > K) return;

	stack[S++] = dist;
	cur_len[dist] = min(cur_len[dist],len);

	for(i =0 ; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;
		if(u == p) continue;
		dfs(u,v,dist+adj[v][i].second,len+1);
	}
}

int path(int root){
	int i,u,k,sol,dist;

	sol = INF;
	U = 0;

	min_len[0] = 0;

	for(i = 0; i < (int)adj[root].size(); ++i){
		u = adj[root][i].first;
		S = 0;

		dfs(u,root,adj[root][i].second,1);

		for(k = 0; k < S; ++k){
			dist = stack[k];
			sol = min(sol,cur_len[dist]+min_len[K-dist]);
		}

		while(S--){
			dist = stack[S];
			min_len[dist] = min(min_len[dist],cur_len[dist]);
			cur_len[dist] = INF;
			upd[U++] = dist;
		}
	}

	while(U--){
		min_len[upd[U]] = INF;
	}

	min_len[0] = INF;

	return sol;
}

int V;

int dec(){
	int i,root,k,sol;

	sol = INF;

	for(i = 0; i <= K; ++i){
		min_len[i] = INF;
		cur_len[i] = INF;
	}

	V = N;

	while(V){

		memset(visited,0,sizeof(visited));

		for(i = 0; i < N; ++i){
			if(rem[i] || visited[i]) continue;

			init(i);
			root = best_root(i,-1);
			k = path(root);
			sol = min(sol,k);
			rem[root] = 1;
			--V;
		}
	}

	return sol >= INF ? -1 : sol;
}


int main(){
	int u,v,i,len;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N-1; ++i){
		scanf("%d%d%d",&u,&v,&len);
		adj[u].push_back(make_pair(v,len));
		adj[v].push_back(make_pair(u,len));
	}

	printf("%d\n",dec());

	return 0;
}
