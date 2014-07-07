#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>

#define NMAX 100010

using namespace std;

typedef long long lli;

int N,M,L;

lli sub[NMAX][2];
lli out[NMAX];

vector<pair<int,int> > adj[NMAX];
pair<int,int> par[NMAX];

lli best_st[NMAX];
int comp[NMAX];
int C;

int visited[NMAX];

void dfs(int v){
	visited[v] = 1;


	int i,u;
	lli ins;
	comp[v] = C;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i].first;

		if(visited[u]) continue;

		par[u] = make_pair(v,adj[v][i].second);
		dfs(u);

		ins = sub[u][0]+adj[v][i].second;
		for(int b = 0; b < 2; ++b){
			if(ins > sub[v][b]) swap(ins,sub[v][b]);
		}
	}
}

void dfs2(int v){
	int i;
	lli ins;

	if(par[v].first < 0){
		for(i = 0; i < (int)adj[v].size(); ++i) dfs2(adj[v][i].first);
		return;
	}

	out[v] = out[par[v].first];
	ins = sub[v][0]+par[v].second;
	out[v] = max(out[v],sub[par[v].first][ (sub[par[v].first][0] == ins) ]) + par[v].second;

	for(i = 0; i < (int)adj[v].size(); ++i){
		if(adj[v][i] == par[v]) continue;
		dfs2(adj[v][i].first);
	}
}

lli max_st[3],dist;

void init(){
	int i;
	lli ins;

	for(i = 0; i < N; ++i){
		if(visited[i]) continue;

		par[i] = make_pair(-1,0);
		dfs(i);
		best_st[C] = (1e15);
		dfs2(i);
		++C;
	}

	for(i =0 ; i < N; ++i){
		dist = max(dist,max(sub[i][0],out[i]));
		best_st[comp[i]] = min ( best_st[comp[i]], max(sub[i][0],out[i]));
	}


	for(i = 0; i < C; ++i){
		ins = best_st[i];
		for(int b = 0; b < 3; ++b){
			if(ins > max_st[b]) swap(ins,max_st[b]);
		}
	}
}

int main(){

	int a,b,c,i;

	scanf("%d%d%d",&N,&M,&L);
	for(i = 0; i < M; ++i){
		scanf("%d%d%d",&a,&b,&c);
		adj[a].push_back(make_pair(b,c));
		adj[b].push_back(make_pair(a,c));
	}

	init();

	if(C > 1) dist = max(dist,max_st[0]+max_st[1]+L);
	if(C > 2) dist = max(dist,max_st[1]+max_st[2]+2LL*L);
	printf("%lld\n",dist);

	return 0;
}
