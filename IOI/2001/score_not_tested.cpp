#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>

#define NMAX 1010

using namespace std;

int edge_typ[NMAX][NMAX];
int typ[NMAX];
int wlpath[NMAX][2];
int wlpath2[NMAX][2];

int owner[NMAX];

int outdeg[NMAX];
int indeg[NMAX];

int N;

/*
 0 winning
 1 losing
 0 player
 1 opponent
*/

vector<int> inc[NMAX];
vector<int> out[NMAX];

void dfs(int v){
	int i,u;

	if(typ[v] < 0){
		typ[v] = wlpath[v][owner[v]] == owner[v];
	}

	for(i = 0; i < inc[v].size(); ++i){
		u = inc[v][i];
		if(edge_typ[u][v] >= 0) continue;
		edge_typ[u][v] = typ[v];
		wlpath[u][typ[v]] = 1;
		--outdeg[u];
		if(!outdeg[u] && typ[u] < 0){
			dfs(u);
		}
	}
}

void dfs2(int v){
	int i,u;

	if(typ[v] < 0){
		typ[v] = wlpath2[v][owner[v]] == owner[v];
	}

	for(i = 0; i < out[v].size(); ++i){
		u = out[v][i];
		if(edge_typ[v][u] >= 0) continue;
		edge_typ[v][u] = typ[v];
		wlpath2[u][typ[v]] = 1;
		--indeg[u];
		if(!indeg[u] && typ[u] < 0){
			dfs2(u);
		}
	}
}

void process(int v){
	typ[v] = owner[v];
	dfs(v);
	dfs2(v);
}

pair<int,int> order[NMAX];

int main(){
	int i,j;

	scanf("%d",&N);

	memset(edge_typ,-1,sizeof(edge_typ));
	memset(typ,-1,sizeof(typ));

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&edge_typ[i][j]);

			if(edge_typ[i][j]){

				if(!j){
					out[i].push_back(N);
					inc[N].push_back(-1);
					++outdeg[i];
					++indeg[N];
				}else{
					out[i].push_back(j);
					inc[j].push_back(i);
					++outdeg[i];
					++indeg[j];
				}
			}

			edge_typ[i][j] = -1;
		}
	}

	for(i =0 ; i < N; ++i){
		scanf("%d",&owner[i]);
		--owner[i];
	}

	for(i =0; i < N; ++i){
		scanf("%d",&j);
		order[i] = make_pair(j,i);
	}

	sort(order,order+N);

	for(i = N-1; i >= 0; --i){
		if(typ[order[i].second] >= 0) continue;
		process(order[i].second);
	}

	i = 0;

	while(i < N){

		if(owner[i]){
			scanf("%d",&i);
			--i;
			if(!i) break;
		}else{
			assert(!typ[i]);

			for(j =0 ; j <= N; ++j){
				if(edge_typ[i][j]) continue;
				break;
			}

			if(j  >N){
				j /= 0;
			}

			printf("%d\n",j%N+1);
			fflush(stdout);
			i = j;
		}
	}

	return 0;
}
