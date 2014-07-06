#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>

#define NMAX 1000010

using namespace std;

vector<int> adj[NMAX];
int N;

class chain_set{
private:
	int deg[NMAX];
	int end2[NMAX];
	int comp[NMAX];
	int del,C,N;
	int deg1[2],D,inv;

	void dfs(int v){
		if(comp[v] >= 0) return;
		int i;

		comp[v] = C;

		for(i = 0; i < (int)adj[v].size(); ++i){
			if(adj[v][i] == del) continue;
			++deg[v];
			dfs(adj[v][i]);
		}

		if(deg[v] > 2) inv = 1;
		if(deg[v] < 2) deg1[D++] = v;
	}


public:

	void init(int v, int n){
		del = v;
		N = n;
		inv = 0;
		int i;
		memset(comp,-1,sizeof(comp));

		for(i = 0; i < N; ++i){
			if(comp[i] >= 0 || i == del) continue;
			D = 0;
			dfs(i);

			if(!D){
				inv = 1;
				return;
			}
			if(D < 2) deg1[D++] = deg1[0];

			C++;
			end2[deg1[0]] = deg1[1];
			end2[deg1[1]] = deg1[0];
		}
	}

	int connect(int v, int u){
		if(u == del || v == del) return 0;
		if(deg[u] > 1 || deg[v] > 1){
			inv = 1;
			return -1;
		}
		if(comp[u] == comp[v]){
			inv = 1;
			return -2;
		}

		int ev,eu;
		ev = end2[v], eu = end2[u];
		end2[eu] = ev;
		end2[ev] = eu;
		comp[eu] = comp[ev];
		++deg[v], ++deg[u];

		return 1;
	}

	int invalid(){
		return inv;
	}
};


int end[NMAX];
int deg[NMAX];
int comp[NMAX];
int size[NMAX];

int sel[NMAX];


void init(){
	int i;
	for(i = 0; i < N; ++i) end[i] = comp[i] = i , size[i] = 1;
}

int state;
int cyc;

chain_set critical[12];
int C,failed;

int create_set(int v){
	if(sel[v]) return 2;
	if(C >= 12){
		sel[v] = -1;
		failed = 1;
		return 0;
	}
	sel[v] = 1;
	critical[C].init(v,N);
	++C;
	return 1;
}

/*
	0 = disjoint chains
	1 = 1 cycle and all disjoint chains
	2 = <= 4 degree 3 vertices
	3 = 1 vertex of degree >= 4
	4 = invalid
*/

chain_set deg_4;

int update(int u, int v){

	if(state >= 4) return 0;

	int crit,i;

	if(state < 2){
		if(deg[v] > 1 || deg[u] > 1){
			state = 2;			//degree 3 vertex is created
			++deg[u];
			++deg[v];
			adj[u].push_back(v);
			adj[v].push_back(u);

			if(deg[v] >= 3){
				create_set(v);
				for(i =0 ; i < (int)adj[v].size(); ++i) create_set(adj[v][i]);
			}

			if(deg[u] >= 3){
				if(deg[u] > 2) create_set(u);
				for(i =0 ; i < (int)adj[u].size(); ++i) create_set(adj[u][i]);
			}

			crit = 0;
			for(i = 0; i < C; ++i){
				crit += !critical[i].invalid();
			}

			if(!crit){
				state = 3;
			}

			return crit;
		}

		++deg[u];
		++deg[v];
		adj[u].push_back(v);
		adj[v].push_back(u);
		if(comp[v] == comp[u]){
			if(state){
				//disconnected cycles = invalid
				state = 3;
				return 0;
			}
			state = 1;
			cyc = comp[v];
			return size[comp[v]];			//created cycle
		}

		size[comp[v]] += size[comp[u]];
		int ev,eu;
		ev = end[v], eu = end[u];
		end[eu] = ev;
		end[ev] = eu;
		comp[eu] = comp[v];
		return state ? size[cyc] : N;
	}

	crit = 0;
	if(state == 2){
		++deg[v];
		++deg[u];
		adj[v].push_back(u);
		adj[u].push_back(v);

		if(deg[u] > 3 || deg[v] > 3){		//there's a degree 4 vertex
			state = 3;
			if(deg[u] > deg[v]) swap(u,v);

			deg_4.init(v,N);
			if(deg_4.invalid()){
				state = 4;
				return 0;
			}
			return 1;
		}

		if(deg[v] == 3){
			create_set(v);
			for(i =0 ; i < (int)adj[v].size(); ++i) create_set(adj[v][i]);
		}

		if(deg[u] == 3){
			if(deg[u] > 2) create_set(u);
			for(i =0 ; i < (int)adj[u].size(); ++i) create_set(adj[u][i]);
		}

		for(i = 0; i < C; ++i){
			if(critical[i].invalid()) continue;
			critical[i].connect(u,v);
		}

		for(i = 0; i < C; ++i){
			crit += !critical[i].invalid();
		}

		if(failed){						//if there were more than 4 degree 3 vertices all of the sets should be invalid
			assert(!crit);
			state = 4;
			return crit;
		}

		return crit;
	}

	adj[v].push_back(u);
	adj[u].push_back(v);
	++deg[u];
	++deg[v];
	if(deg_4.connect(u,v) < 0){
		state = 4;
		return 0;
	}
	return 1;

}

int crit;
int Q;

int main(){
	int i,j;

	scanf("%d%d",&N,&Q);

	crit = N;
	init();

	while(Q--){
		scanf("%d",&i);
		if(i < 0){
			printf("%d\n",crit);
			continue;
		}
		scanf("%d",&j);
		crit = update(i,j);
	}

	return 0;
}
