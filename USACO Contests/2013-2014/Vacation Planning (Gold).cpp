/*
 Created By: Malvika Joshi
 Problem: Vacation Planning (December-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=364
*/

#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>
#include <cassert>
#include <queue>
#include <iostream>

#define INF (int)(5e8)
#define NMAX 20010
#define KMAX 210

using namespace std;
typedef long long lli;
typedef pair<int,int> pii;

priority_queue<pii, vector<pii>, greater<pii> > Q;

int dist[KMAX][NMAX];
char visited[NMAX];

vector<pii> adj[NMAX];
char is_pub[NMAX];
int id[NMAX];

int N,M,K;

void dijkstra(int src){
	int i,v,u,d;

	Q.push(make_pair(0,src));
	memset(visited,0,NMAX);

	for(i = 0; i < N; ++i) dist[id[src]][i] = INF;

	while(!Q.empty()){
		v = Q.top().second;
		d = Q.top().first;
		Q.pop();

		if(visited[v]) continue;
		visited[v] = 1;
		dist[id[src]][v] = d;

		for(i = 0; i < (int)adj[v].size(); ++i){
			u = adj[v][i].first;
			d = adj[v][i].second;
			Q.push(make_pair(dist[id[src]][v]+d,u));
		}
	}
}

void init(){
	int i;

	for(i =0 ; i < N; ++i){
		if(!is_pub[i]) continue;
		dijkstra(i);
	}
}

int get_dist(int src, int tar){
	int i,u,w,ds;

	if(is_pub[src]) return dist[id[src]][tar];

	ds = INF;
	for(i = 0; i < (int)adj[src].size(); ++i){
		u = adj[src][i].first;
		w = adj[src][i].second;
		assert(is_pub[u]);
		ds = min(ds,dist[id[u]][tar]+w);
	}

	return ds;
}

int main(){
	int i,full,u,v,w,t;
	lli tot;

	tot = 0ll;
	full = 0;

	scanf("%d%d%d%d",&N,&M,&K,&t);

	for(i = 0; i < M; ++i){
		scanf("%d%d%d",&u,&v,&w);
		--u,--v;
		adj[u].push_back(make_pair(v,w));
	}

	while(K--){
		scanf("%d",&i);
		--i;
		is_pub[i] = 1;
		id[i] = K;
	}

	init();

	while(t--){
		scanf("%d%d",&u,&v);
		--u,--v;
		w = get_dist(u,v);
		if(w >= INF) continue;
		tot += w;
		++full;
	}

	printf("%d\n%lld\n",full,tot);

	return 0;
}
