/*
 Created By: Malvika Joshi
 Problem: Facebook (IOITC-2014 Test-5)
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

#define MAXN 7000
#define MAXM 50000
#define INF 200000000

typedef pair<int,int> edge;

vector<pair<int,int> > adj[MAXN];
int dist[MAXN];
int par[MAXN];

int N,M;

edge edges[MAXM];
int weight[MAXM];
int visited[MAXN];

set<pair<int,edge> > Q;

void dijkstra(int src){
	int i,v;
	int tmp;

	for(i = 0; i < N; ++i) {
		dist[i] = INF;
		par[i] = -1;
		visited[i] = 0;
	}

	Q.insert(make_pair(0,make_pair(-1,src)));

	while(!Q.empty()){
		v = Q.begin()->second.second;
		if(visited[v]){
			Q.erase(Q.begin());
			continue;
		}
		visited[v] = 1;
		par[v] = Q.begin()->second.first;
		dist[v] = Q.begin()->first;
		Q.erase(Q.begin());

		for(i = 0; i < adj[v].size(); ++i){
			tmp = dist[v] + adj[v][i].second;
			Q.insert(make_pair(tmp,make_pair(v,adj[v][i].first)));
		}
	}
}

int tar_dist[MAXN];
char col[MAXN];
vector<int> child[MAXN];

int new_dist[MAXM];

void init(){

	dijkstra(N-1);
	memcpy(tar_dist,dist,sizeof(int)*MAXN);

	dijkstra(0);

	for(int i = 0; i < N; ++i){
		if(par[i] < 0) continue;
		child[par[i]].push_back(i);
	}


	for(int i = 0; i < M; ++i){
		new_dist[i] = dist[N-1];
	}
}

set<pair<int,int> > join;

void dfs(int v){
	int k,tmp;

	if(col[v]) return;
	col[v] = 1;

	for(k = 0; k < adj[v].size(); ++k){
		if(adj[v][k].first == par[v])	continue;

		tmp = adj[v][k].second + dist[adj[v][k].first] + tar_dist[v];
		join.insert(make_pair(tmp,adj[v][k].first));
	}


	for(int i = 0; i < child[v].size(); ++i) dfs(child[v][i]);
}


int edit[MAXN];

void compute(){

	int i,u,v;
	int mindist;


	for(i = 0; i < M; ++i){
		u = edges[i].first;
		v = edges[i].second;
		if(u == par[v]) edit[v] = i;
		if(v == par[u]) edit[u] = i;
	}

	i = N-1;
	while(par[i] >= 0){
		dfs(i);
		u = join.begin()->second;

		while(col[u]){
			join.erase(join.begin());
			u = join.begin()->second;
		}

		if(join.empty()) mindist = INF;
		else mindist = join.begin()->first;

		new_dist[edit[i]] = mindist;
		i = par[i];
	}
}

int main(){

	int i,q;

	scanf("%d%d%d",&N,&M,&q);

	int a,b,c;
	for(i =0 ; i < M; ++i){
		scanf("%d%d%d",&a,&b,&c);
		weight[i] = c;
		edges[i] = make_pair(a,b);
		adj[a].push_back(make_pair(b,c));
		adj[b].push_back(make_pair(a,c));
	}

	init();
	compute();

	while(q--){
		scanf("%d",&i);
		printf("%d\n",new_dist[i] >= INF ? -1 : new_dist[i]);
	}

	return 0;
}
