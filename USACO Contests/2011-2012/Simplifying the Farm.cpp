/*
 Created By: Malvika Joshi
 Problem: Simlifying the Farm (December-2011 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=101
*/

#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <cassert>
#include <iostream>

#define N_MAX 40010
#define M_MAX 100010
#define MOD (int)(1e9+7)
#define sec second
#define fst first

using namespace std;

typedef pair<int,int> edge;
typedef long long lli;

int parent[N_MAX];
int rank[N_MAX];

void make_set(int x){
	parent[x] = x;
	rank[x] = 0;
}

int find(int x){
	if(parent[x] != x){
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

void set_union(int x, int y){
	int root_x,root_y;

	root_x = find(x);
	root_y = find(y);

	if(rank[root_x] < rank[root_y]){
		parent[root_x] = root_y;
	}else{
		parent[root_y] = root_x;
		rank[root_x] += (rank[root_x] == rank[root_y]);
	}
}

pair<int,edge> edges[M_MAX];
map<int,vector<edge> > duplicate;
map<int,int> match;
int N,M;

int sel[M_MAX];

vector<int> adj[N_MAX];
int ftime[N_MAX];
pair<int,int> exp_range[N_MAX];

lli mst(){
	lli cost,i,x,y;

	sort(edges,edges+M);

	for(i =0 ; i < N; ++i) make_set(i);

	cost = 0LL;
	for(i = 0; i < M; ++i){
		x = edges[i].sec.fst,y = edges[i].sec.sec;
		if(find(x) ==  find(y) ) continue;

		set_union(x,y);
		adj[x].push_back(y);
		adj[y].push_back(x);

		sel[i] = 1;
		cost += edges[i].fst;
	}


	return cost;
}

int cur_time;
int visited[N_MAX];

void dfs(int v){
	if(visited[v]) return;
	visited[v] = 1;

	int i;

	exp_range[v].fst = cur_time;

	for(i = 0; i < adj[v].size(); ++i){
		dfs(adj[v][i]);
	}

	exp_range[v].sec = cur_time;
	ftime[v] = cur_time++;
}

inline int  in_range(int x, pair<int,int> range){
	return (x >= range.fst && x <= range.sec);
}

int count_trees(){

	int i,weight,low,u,v,rep,k;
	int count;
	map<int,vector<edge> >::iterator it;

	dfs(0);

	count= 1;
	for(i = 0; i < M; ++i){
		if(!sel[i]) continue;

		rep = 0;
		weight = edges[i].fst;

		low = ftime[edges[i].sec.fst] > ftime[edges[i].sec.sec] ?
									edges[i].sec.sec : edges[i].sec.fst;

		it = duplicate.find(weight);
		for(k = 0; k < it->sec.size(); ++k){
			u = it->sec[k].fst;
			v = it->sec[k].sec;
			rep += (in_range(ftime[u],exp_range[low]) ^ in_range(ftime[v],exp_range[low]));
		}

		if(rep > 1) match[weight] += rep;
	}

	for(map<int,int>::iterator it2 = match.begin(); it2 != match.end(); ++it2){
		rep = it2->second;
		assert(rep > 1 && rep < 5);
		if(rep == 4) --rep;
		count = (1LL*count*rep)%MOD;
	}

	return count;
}

int main(){

	int i,a,b,n;
	vector<edge> empty;

	scanf("%d%d",&N,&M);

	for(i = 0; i < M; ++i){
		scanf("%d%d%d",&a,&b,&n);
		--a,--b;
		edges[i] = make_pair(n,make_pair(a,b));
		duplicate[n].push_back(make_pair(a,b));
	}

	printf("%lld ",mst());
	printf("%d\n",count_trees());

	return 0;
}
