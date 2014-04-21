/*
 Created By: Malvika Joshi
 Problem: Grass Planting (December-2011 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=102
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include <cstring>
#include <cassert>

#define N_MAX 100010
#define LOG_MAX 18

using namespace std;


//DATA

class sparse_table{
// LOWER NODE HIGHER LEVEL
private:
	int ans[N_MAX][LOG_MAX];
public:
	void init(int N, int* par){
		int i,j;

		memset(ans,-1,sizeof(int)*N_MAX*LOG_MAX);

		for(i = 0; i < N; ++i){
			ans[i][0] = par[i];
		}

		for(j = 1; (1<<j) < N; ++j){
			for(i = 0; i < N; ++i){
				if(ans[i][j-1] < 0) continue;
				ans[i][j] = ans[ans[i][j-1]][j-1];
			}
		}
	}

	int query(int p, int q, int *lev){
		int log,i;

		if(lev[p] < lev[q]) swap(p,q);

		for(log = 1; (1<<log) <= lev[p]; ++log);
		--log;

		for(i = log; i >= 0; --i){
			if(lev[p] - (1<<i) < lev[q]) continue;
			p = ans[p][i];
		}

		if(p == q) return q;


		for(i = log; i >= 0; --i){
			if(ans[p][i] == -1 || ans[p][i] == ans[q][i]) continue;
			p = ans[p][i], q = ans[q][i];
		}

		return ans[p][0];
	}

};

class fenwick_tree{

private:
	int tree[N_MAX];
	int N;

	int read(int x){
		int sum;
		sum = tree[0];
		while(x){
			sum += tree[x];
			x -= (x&-x);
		}
		return sum;
	}

public:
	void init(int n){
		memset(tree,0,sizeof(int)*N_MAX);
		N = n;
	}

	void update(int x, int val){
		if(!x){
			tree[x] += val;
			return;
		}
		while(x < N){
			tree[x] += val;
			x += (x&-x);
		}
	}

	int query(int s, int e){
		if(!s) return read(e);
		return read(e)-read(s-1);
	}

};

// END DATA

int par[N_MAX];
int dist[N_MAX];
int id[N_MAX];
char visited[N_MAX];

pair<int,int> range[N_MAX];

sparse_table lca_data;
fenwick_tree bit;

vector<int> adj[N_MAX];
int N,cur_time;

void dfs(int p, int v){
	if(visited[v]) return;
	int i;

	visited[v] = 1;
	par[v] = p;
	id[v] = cur_time++;


	dist[v] = p < 0 ? 0 : dist[p] + 1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		dfs(v,adj[v][i]);
	}

	range[v] = make_pair(id[v],cur_time-1);
}

void plant(int u, int v){
	int lca;

	lca = lca_data.query(u,v,dist);

	bit.update(id[u],1);
	bit.update(id[v],1);
	bit.update(id[lca],-2);
}

int edge_query(int u, int v){
	if(dist[u] > dist[v]) swap(u,v);
	return bit.query(range[v].first,range[v].second);
}

int main(){
	int i,query,u,v;
	char c;

	scanf("%d%d",&N,&query);

	for(i = 0; i < N-1; ++i){
		scanf("%d%d",&u,&v);
		--u,--v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(-1,0);
	lca_data.init(N,par);
	bit.init(N);

	while(query--){
		scanf(" %c%d%d",&c,&u,&v);
		c ^= 'P';
		--u,--v;

		if(!c){
			plant(u,v);
		}else{
			printf("%d\n",edge_query(u,v));
		}
	}

	return 0;
}








