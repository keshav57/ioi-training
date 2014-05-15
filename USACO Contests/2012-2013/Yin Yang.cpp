/*
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=286
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <cstring>

#define NMAX 100010
#define INC 100000

using namespace std;
typedef long long lli;

vector<pair<int,int> > adj[NMAX];

int rem[NMAX];

int size[NMAX];
int max_child[NMAX];
int roots[NMAX];

int visited[NMAX];

int R,N;

void dp(int v, int p){
	int i,u;
	visited[v] = 1;

	size[v] = 1;
	max_child[v] = 0;
	for(i = 0; i < adj[v].size(); ++i){
		u = adj[v][i].first;
		if(rem[u] || u == p) continue;
		dp(u,v);
		max_child[v] = max(max_child[v],size[u]);
		size[v] += size[u];
	}
}

int find_root(int v, int p, int out){
	int i,u,root,tmp;

	root = v;
	max_child[v] = max(max_child[v],out);
	out += size[v];

	for(i = 0; i < adj[v].size(); ++i){
		u = adj[v][i].first;
		if(rem[u] || u == p) continue;

		tmp = find_root(u,v,out-size[u]);
		if(max_child[root] > max_child[tmp]) root = tmp;
	}

	return root;
}

void init(){
	int i;

	memset(visited,0,sizeof(int)*NMAX);

	for(i = 0; i < N; ++i){
		if(rem[i] || visited[i]) continue;
		dp(i,-1);
		roots[R++] = find_root(i,-1,0);
	}
}

int cur[2][NMAX*2];
int prev[2][NMAX*2];

int occ[NMAX*2];
int mod[NMAX];
int M;

void dfs(int v, int p, int sum){
	int i,u,b;

	mod[M++] = sum;
	b = !!(occ[sum+INC]);
	++occ[sum+INC];
	++cur[b][sum+INC];

	for(i = 0; i < adj[v].size(); ++i){
		u = adj[v][i].first;
		if(rem[u] || u == p) continue;
		dfs(u,v,sum+adj[v][i].second);
	}

	--occ[sum+INC];
}

int added[NMAX*2];

lli count_paths(int root){
	int i,m,u,k,sum;
	lli paths;

	paths = 0LL;

	prev[0][0+INC] = 1;
	m = 0;

	M = 0;
	for(i = 0; i < adj[root].size(); ++i){
		u = adj[root][i].first;
		if(rem[u]) continue;
		m = M;
		dfs(u,root,adj[root][i].second);

		for(k = m; k < M; ++k){
			sum = mod[k];
			if(added[sum+INC]) continue;
			added[sum+INC] = 1;
			paths += (1LL*(prev[0][INC-sum]+prev[1][INC-sum])*cur[1][sum+INC]);
			paths += (1LL*prev[1][INC-sum]*cur[0][sum+INC]);

			if(!sum){	//path can stop at the root
				paths += (1LL*(prev[0][INC-sum]-1)*cur[0][sum+INC]);
			}
		}

		for(k = m; k < M; ++k){
			sum = mod[k];
			added[sum+INC] = 0;
			prev[0][sum+INC] += cur[0][sum+INC];
			prev[1][sum+INC] += cur[1][sum+INC];
			cur[0][sum+INC] = cur[1][sum+INC] = 0;
		}
	}

	while(M--){
		sum = mod[M];
		prev[0][sum+INC] = prev[1][sum+INC] = 0;
	}
	prev[0][0+INC] = 0;

	return paths;
}

lli tot(){
	lli paths,i;
	paths = 0LL;

	for(i = 0; i < R; ++i){
		paths += count_paths(roots[i]);
		rem[roots[i]] = 1;
	}

	return paths;
}

int main(){
	int i,u,v,t,left;
	lli paths;

	scanf("%d",&N);

	for(i = 0; i < N-1; ++i){
		scanf("%d%d%d",&u,&v,&t);
		--u,--v;
		t = t ? -1 : 1;
		adj[u].push_back(make_pair(v,t));
		adj[v].push_back(make_pair(u,t));
	}

	left = N;
	paths= 0LL;

	while(left){
		init();
		paths += tot();
		left -= R;
		R = 0;
	}

	printf("%lld\n",paths);

	return 0;
}
