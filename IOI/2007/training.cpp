#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

#define NMAX 1010
#define SMAX ((1<<10)+10)
#define MMAX 5010
#define LOGN 12
#define DEG 12
#define ALL(v) ((1<<n[(v)])-1)

using namespace std;

struct edge{
	int u,v,cost;
};

class lca_table{
private:
	int ances[NMAX][LOGN];
	int N,dist,log;
public:

	void init(int n, int *par){
		int i,k;

		N = n;
		for(i = 0; i < N; ++i){
			ances[i][0] = par[i];
		}

		for(k = 1; (1<<k) <= N; ++k){
			for(i = 0; i < N; ++i){
				ances[i][k] = ances[i][k-1] < 0 ? -1 : ances[ances[i][k-1]][k-1];
			}
		}
		log = k;
	}

	pair<int,int> query(int u, int v, int *lev){
		assert(lev[u] >= lev[v]);
		dist = 1;

		int k;

		for(k = log-1; k >= 0; --k){
			if(ances[u][k] < 0 || lev[ances[u][k]] <= lev[v]) continue;
			u = ances[u][k];
			dist += (1<<k);
		}


		if(ances[u][0] == v) return make_pair(u,v);
		if(lev[u] != lev[v]){
			u = ances[u][0];
			++dist;
		}

		for(k = log-1; k >= 0; --k){
			if(ances[u][k] == ances[v][k]) continue;
			u = ances[u][k];
			v = ances[v][k];
			dist += (1<<k);
			dist += (1<<k);
		}

		++dist;
		return make_pair(u,v);
	}

	int get_dist(){
		return dist;
	}

};

int par[NMAX];
int lev[NMAX];
int idx[NMAX];

int child[NMAX][DEG];
int n[NMAX];
int N;

void dfs(int v){
	int i,u;


	for(i = 0; i < n[v]; ++i){
		u = child[v][i];
		if(u == par[v]){
			swap(child[v][i--],child[v][--n[v]]);
			continue;
		}

		par[u] = v;
		lev[u] = lev[v]+1;
		idx[u] = i;
		dfs(u);
	}
}

edge edges[MMAX];
pair<int,int> stree[MMAX];
int M;

lca_table T;

vector<int> aff[NMAX];

void init(){
	int i;
	pair<int,int> l;


	par[0] = -1, idx[0] = -1;
	dfs(0);
	T.init(N,par);

	for(i = 0; i < M; ++i){
		if(lev[edges[i].u] < lev[edges[i].v]) swap(edges[i].u,edges[i].v);
		l = T.query(edges[i].u,edges[i].v,lev);

		if(T.get_dist()&1){
			//even len cycle
			swap(edges[i--],edges[--M]);
			continue;
		}

		stree[i].first = idx[l.first];
		stree[i].second = par[l.first] == l.second ? -1 : idx[l.second];

		assert(par[l.first] == l.second || par[l.first] == par[l.second]);

		aff[par[l.first]].push_back(i);
	}

}


int mem[NMAX][SMAX];

int mem_cost[NMAX][NMAX];
int max_cost(int,int);

int up(int u, int v){
	if(mem_cost[u][v] >= 0) return mem_cost[u][v];
	int &val = mem_cost[u][v];

	val = max_cost(u,ALL(u));
	while(u != v){
		val += (max_cost(par[u],ALL(par[u])^(1<<idx[u])));
		u = par[u];
	}

	return val;
}

int max_cost(int i, int sel){
	int &val = mem[i][sel];
	int k,tmp,u,v,j;

	if(val >= 0) return val;
	if(!sel){
		val = 0;
		return val;
	}

	val = 0;
	for(k = 0; k < n[i]; ++k){
		if(!(sel&(1<<k))) continue;
		u = child[i][k];
		val += max_cost(u,ALL(u));
	}

	for(k = 0; k < (int)aff[i].size(); ++k){
		j = aff[i][k];
		u = edges[j].u, v = edges[j].v;

		assert(stree[j].first >= 0);
		if(!(sel&(1<<stree[j].first))) continue;

		if(stree[j].second < 0){
			tmp = max_cost(i,sel^(1<<stree[j].first)) + up(u,child[i][stree[j].first]) + edges[j].cost;
			val = max(val,tmp);
			continue;
		}

		if(!(sel&(1<<stree[j].second))) continue;

		tmp = max_cost(i,sel^(1<<stree[j].first)^(1<<stree[j].second)) + up(u,child[i][stree[j].first]) + up(v,child[i][stree[j].second]) + edges[j].cost;
		val = max(val,tmp);
	}

	return val;
}

int main(){
	int i,tot,left;

	memset(mem,-1,sizeof(mem));
	memset(mem_cost,-1,sizeof(mem_cost));
	scanf("%d%d",&N,&M);

	tot =0 ;
	for(i = 0; i < M; ++i){
		scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].cost);
		--edges[i].u,--edges[i].v;
		tot += edges[i].cost;

		if(edges[i].cost) continue;

		child[edges[i].u][n[edges[i].u]++] = edges[i].v;
		child[edges[i].v][n[edges[i].v]++] = edges[i].u;
		--i;
		--M;
	}

	init();
	left = max_cost(0,ALL(0));
	printf("%d\n",tot-left);

	return 0;
}
