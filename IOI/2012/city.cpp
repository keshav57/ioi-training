#include <iostream>
#include <cassert>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cstdio>

#define MOD (int)(1e9)
#define NMAX 100010
#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

map<point, int> idx;
const point adj[4] = {make_pair(-1,0), make_pair(1,0) , make_pair(0,1), make_pair(0,-1) };

/*
 * 0 1 : down up
 * 2 3 : left right
 */

vector<int> child[NMAX];
vector<int> cells[NMAX];
int N,V;

int visited[NMAX];
int comp[NMAX];

point pos[NMAX];

void dfs(int v){
	int i,u,dir,node;
	point pt;

	map<point,int>::iterator it;

	node = V++;
	visited[v] = 1;
	comp[v] = node;
	cells[node].push_back(v);

	for(dir = 0; dir < 2; ++dir){
		pt = pos[v];
		while(1){
			pt.x += adj[dir].x;
			pt.y += adj[dir].y;
			it = idx.find(pt);
			if(it == idx.end()) break;
			u = it->second;
			visited[u] = 1;
			comp[u] = node;
			cells[node].push_back(u);
		}
	}

	for(i = 0; i < (int)cells[node].size(); ++i){
		v = cells[node][i];
		for(dir = 2; dir < 4; ++dir){
			pt = make_pair(pos[v].x+adj[dir].x, pos[v].y+adj[dir].y);
			it = idx.find(pt);
			if(it == idx.end()) continue;
			u = it->second;
			if(visited[u]) continue;
			dfs(u);
			child[node].push_back(comp[u]);
		}
	}
}

int sum[NMAX];
int sub[NMAX];
int cross[NMAX];

void init(){
	int i;
	memset(sum,0,sizeof(sum));
	memset(sub,0,sizeof(sub));
	memset(cross,0,sizeof(cross));
	memset(visited,0,sizeof(visited));

	for(i = 0; i < V; ++i){
		cells[i].clear();
		child[i].clear();
	}

	idx.clear();
	V = 0;
	for(i = 0 ; i < N; ++i){
		idx.insert(make_pair(pos[i],i));
	}
	dfs(0);
}

void dp(int v){
	int i,u,sz,g;

	sz = cells[v].size();
	for(i = 0; i < (int)child[v].size(); ++i){
		u = child[v][i];
		dp(u);

		g = (sum[u]+sub[u])%MOD;
		cross[u] = (1LL*sum[v]*g)%MOD;
		cross[u] += (1LL*sum[u]*sub[v])%MOD;
		cross[u] %= MOD;
		sub[v] += g;
		sub[v] %= MOD;
		sum[v] += sum[u];
	}

	sum[v] += sz;
	assert(sum[v] < MOD);
}

int compute(){
	int tot,i;
	dp(0);

	tot = 0;
	for(i =0 ; i < V; ++i){
		tot += cross[i];
		tot %= MOD;
		tot += (sub[i]*1LL*cells[i].size())%MOD;
		tot %= MOD;
	}

	return tot;
}

int DistanceSum(int n, int *X, int *Y){
	int i,sol;
	N = n;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		pos[i] = make_pair(X[i],Y[i]);
	}

	sol = 0;
	init();

	sol = compute();

	for(i =0 ; i  < N; ++i){
		swap(pos[i].x,pos[i].y);
	}

	init();
	sol += compute();
	sol %= MOD;

	return sol;
}

