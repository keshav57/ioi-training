/*
 Created By: Malvika Joshi
 Problem: Binary Apple Tree
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1018
*/

#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 110
#define INF 3000010
#define l first
#define r second

using namespace std;

vector<pair<int,int> > adj[MAXN];

pair<int,int> child[MAXN];
int del[MAXN][MAXN];
int apple[MAXN];
int size[MAXN];
int tapp[MAXN];
int visited[MAXN];
int N,K;

void init(int v){
	int i,u;
	visited[v] = 1;
	size[v] = 1;
	tapp[v] = apple[v];

	for(i = 0; i < (int)adj[v].size(); i++){
		u = adj[v][i].first;
		if(visited[u]) continue;
		if(child[v].l) child[v].r = u;
		else child[v].l = u;
		apple[u] = adj[v][i].second;
		init(u);
		tapp[v] += tapp[u];
		size[v] += size[u];
	}

}

void dfs(int v){
	int k,i;

	del[v][size[v]] = tapp[v];

	if(!child[v].l) return;
	dfs(child[v].l);
	dfs(child[v].r);

	for(k = 1; k <= K; k++){
		for(i = 0; i <= k; i++){
			del[v][k] = min(del[v][k],del[child[v].l][i] + del[child[v].r][k-i]);
		}
	}
}

int main(){

	int i,k,a,b,tot;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N; ++i){
		for(k = 1; k <= N; ++k){
			del[i][k] = INF;
		}
	}

	k = 0;
	for(i = 0;i < N-1; i++){
		scanf("%d%d%d",&a,&b,&k);
		--a,--b;
		adj[a].push_back(make_pair(b,k));
		adj[b].push_back(make_pair(a,k));
		tot += k;
	}
	K = N-K-1;

	init(0);
	dfs(0);

	printf("%d\n",tot-del[0][K]);

	return 0;
}
