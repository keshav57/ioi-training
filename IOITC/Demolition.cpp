#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define NMAX 17
#define SMAX (1<<17)
#define INC 1000000


using namespace std;

struct point {int x,y,z; };

int popcount[SMAX];
int adj[NMAX][NMAX];

int comp[NMAX][SMAX];
int edges[NMAX][NMAX];
int size[NMAX];

point pos[NMAX][NMAX];

int N,K,B,D;

int floor[2000002];

int par[NMAX];
int stack[NMAX];
int S;

void dfs1(int v, int p){
	int i;
	stack[S++] = v;
	par[v] = p;

	for(i = 0; i < size[v]; ++i){
		if(edges[v][i] == p) continue;
		dfs1(edges[v][i],v);
	}
}

void dfs(){
	int i,s,k,u,bit,j,v,p;

	for(j = 0; j < S; ++j){
		v = stack[j];
		p = par[v];
		for(s = 0; s < (1<<N); ++s){
			for(i = 0; i < N; ++i){
				if(!(s&(1<<i))) continue;
				floor[pos[v][i].z+INC] = 1;
			}

			for(k = 0; k < size[v]; ++k){
				u = edges[v][k];
				if(u == p) continue;
				bit = 0;
				for(i = 0; i < N; ++i){
					bit |= (!floor[pos[u][i].z+INC])<<i;
				}
				comp[u][s] = bit;
			}

			for(i = 0; i < N; ++i){
				if(!(s&(1<<i))) continue;
				floor[pos[v][i].z+INC] = 0;
			}
		}
	}
}

void init(){
	int i,k,v;

	for(i = 0; i < (1<<N); ++i){
		popcount[i] = __builtin_popcount(i);
	}

	for(v = 0; v < B; ++v){
		for(i = 0; i < N; ++i){
			for(k = 0; k < N; ++k){
				if(k == i ||
						abs(pos[v][k].x-pos[v][i].x)+abs(pos[v][k].y-pos[v][i].y)+abs(pos[v][k].z-pos[v][i].z) > D) continue;
				adj[v][i] |= (1<<k);
			}
		}
	}

	dfs1(0,-1);
	dfs();
}

int exact[NMAX][SMAX];
int super[NMAX][SMAX];

void dp(){
	int i,u,s,j,p,v;

	for(j = S-1; j >= 0; --j){
		v = stack[j];
		p = par[v];

		for(s = 0; s < (1<<N); ++s){
			exact[v][s] = (s ? -1 : 0);

			for(i = 0; i < N; ++i){
				if(!(s&(1<<i)) || exact[v][s^(1<<i)] < 0) continue;
				if(popcount[(s^(1<<i)) & adj[v][i] ] > K) continue;
				exact[v][s] = popcount[s];
				break;
			}

			if(exact[v][s] >= 0){						//possible
				for(i = 0; i < size[v]; ++i){
					u = edges[v][i];
					if(u == p) continue;
					exact[v][s] += super[u][comp[u][s]];
				}
			}

			//superset
			for(i = 0; i < N; ++i){
				if(!(s&(1<<i))) continue;
				super[v][s] = max(super[v][s],super[v][s^(1<<i)]);
			}

			super[v][s] = max(super[v][s],exact[v][s]);
		}
	}
}

int main(){
	int i,v,u;

	scanf("%d%d%d%d",&B,&N,&K,&D);

	for(v = 0; v < B; ++v){
		for(i = 0; i < N; ++i){
			scanf("%d%d%d",&pos[v][i].x,&pos[v][i].y,&pos[v][i].z);
		}
	}

	for(i = 0; i < B-1; ++i){
		scanf("%d%d",&v,&u);
		--v,--u;
		edges[v][size[v]++] = u;
		edges[u][size[u]++] = v;
	}

	init();
	dp();

	printf("%d\n",super[0][(1<<N)-1]);

	return 0;
}
