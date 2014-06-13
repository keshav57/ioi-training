#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#define NMAX 500010

typedef long long lli;
using namespace std;

vector<int> inc[NMAX];
vector<int> out[NMAX];

int cost[NMAX];
int stop[NMAX];

int scc[NMAX];
lli tot[NMAX];
int can_stop[NMAX];
lli longest[NMAX];

int visited[NMAX];
int stack[NMAX];
int S,C;

vector<int> adj[NMAX];

void dfs(int v){
	if(visited[v]) return;
	visited[v] = 1;
	int i;

	for(i =0 ; i < (int)out[v].size(); ++i){
		dfs(out[v][i]);
	}

	stack[S++] = v;
}

void dfs2(int v){
	if(visited[v]) return;
	visited[v] = 1;
	int i;

	for(i = 0; i < (int)inc[v].size(); ++i){
		dfs2(inc[v][i]);
	}

	scc[v] = C;
	tot[C] += cost[v];
	can_stop[C] |= stop[v];
}

lli dp(int v){
	if(longest[v] >= 0) return longest[v];

	longest[v] = can_stop[v] ? tot[v] : -(1e15);

	int i;

	for(i = 0; i < (int)adj[v].size(); ++i){
		longest[v] = max(longest[v],dp(adj[v][i])+tot[v]);
	}

	return longest[v];
}

int N,M;

int main(){
	int v,u,i;

	scanf("%d%d",&N,&M);

	while(M--){
		scanf("%d%d",&u,&v);
		--u,--v;
		out[u].push_back(v);
		inc[v].push_back(u);
	}

	for(i = 0; i < N ; ++i){
		scanf("%d",&cost[i]);
	}

	scanf("%d%d",&u,&M);
	--u;

	while(M--){
		scanf("%d",&i);
		stop[--i] = 1;
	}

	for(i = 0; i < N; ++i){
		dfs(i);
	}

	memset(visited,0,sizeof(visited));

	while(S--){
		if(visited[stack[S]]) continue;
		dfs2(stack[S]);
		++C;
	}


	memset(longest,-1,sizeof(longest));
	for(v = 0; v < N; ++v){
		for(i = 0; i < (int)out[v].size(); ++i){
			if(scc[v] == scc[out[v][i]]) continue;
			adj[scc[v]].push_back(scc[out[v][i]]);
		}
	}

	printf("%lld\n",dp(scc[u]));

	return 0;
}
