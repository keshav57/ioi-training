#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>

#define NMAX 210
#define MMAX 6010

using namespace std;

int par[NMAX];
int rank[NMAX];

int N,M,V;

void make_set(int v){
	par[v] = v;
	rank[v] = 0;
}

int find(int v){
	if(par[v] == v){
		return par[v];
	}
	par[v] = find(par[v]);
	return par[v];
}

void merge(int v, int u){
	if(rank[v] > rank[u]){
		par[u] = v;
	}else{
		par[v] = u;
		rank[u] += (rank[v] == rank[u]);
	}
}

vector<pair<int,int> > adj[NMAX];
int v1,v2;

int dfs(int v, int p, int u){
	if(v == u) return 0;

	int i,len;

	len = -1;
	for(i = 0; i < (int)adj[v].size(); ++i){
		if(adj[v][i].first == p) continue;
		len = dfs(adj[v][i].first,v,u);
		if(len < 0) continue;
		break;
	}

	if(len < 0) return -1;

	if(adj[v][i].second >= len){
		len = adj[v][i].second;
		v1 = v;
		v2 = adj[v][i].first;
	}

	return len;
}

/*
 4 6
 1 2 10
 1 3 8
 3 2 3
 1 4 3
 1 3 6
 2 1 2
*/

int insert(int u, int v, int len){
	int uroot,vroot,inc,i;

	uroot = find(u);
	vroot = find(v);


	if(uroot != vroot){
		--V;
		merge(uroot,vroot);
		inc = len;
		adj[v].push_back(make_pair(u,len));
		adj[u].push_back(make_pair(v,len));
		return inc;
	}


	inc = dfs(v,-1,u);

	assert(v1 >= 0 && v2 >= 0);

	if(inc < len){
		return 0;
	}

	inc = len-inc;

	for(i = 0; i < (int)adj[v1].size(); ++i){
		if(adj[v1][i].first == v2){
			swap(adj[v1][i],adj[v1].back());
			adj[v1].pop_back();
			break;
		}
	}

	for(i = 0; i < (int)adj[v2].size(); ++i){
		if(adj[v2][i].first == v1){
			swap(adj[v2][i],adj[v2].back());
			adj[v2].pop_back();
			break;
		}
	}


	adj[v].push_back(make_pair(u,len));
	adj[u].push_back(make_pair(v,len));

	return inc;
}

int main(){
	int i,u,v,len,tot;
	tot=  0;

	scanf("%d%d",&N,&M);

	V = N-1;
	for(i = 0; i < N; ++i){
		make_set(i);
	}

	while(M--){
		scanf("%d%d%d",&u,&v,&len);
		--u,--v;
		tot += insert(u,v,len);
		printf("%d\n",V ? -1 : tot);
	}

	return 0;
}
