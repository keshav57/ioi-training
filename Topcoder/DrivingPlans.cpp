/* SRM 624 Div 1 450 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <cstring>

#define NMAX 2010
#define INF (1e9)
#define MOD ((1e9)+9)

using namespace std;

pair<int,int> par[NMAX][NMAX];
int n[NMAX];

int adj[NMAX][NMAX];

int dist[NMAX];
int visited[NMAX];
int N;

int get_min(){
	int i,v;

	v = -1;
	for(i =0 ; i < N; ++i){
		if(visited[i] || dist[i] >= INF) continue;
		if(v < 0 || dist[i] < dist[v]){
			v = i;
		}
	}
	return v;
}

void dijkstra(int src){
	int i,v,tmp;

	for(i = 0; i < N; ++i) dist[i] = INF;
	dist[src] = 0;

	while(1){
		v = get_min();
		if(v < 0) break;
		visited[v] = 1;


		for(i = 0; i < N; ++i){
			if(adj[i][v] < 0) continue;
			tmp = 	dist[v]+adj[i][v];
			if(tmp > dist[i]) continue;
			if(tmp == dist[i]){
				par[i][n[i]++] = make_pair(v,adj[i][v]);
				continue;
			}
			if(tmp < dist[i]){
				dist[i] = tmp;
				n[i] = 0;
				par[i][n[i]++] = make_pair(v,adj[i][v]);
				dist[i] = tmp;
			}
		}
	}
}

int mem[NMAX];

int ways(int v){
	if(mem[v] >= 0) return mem[v];
	int i,p,tmp;

	mem[v] = !v;


	for(i = 0; i < n[v]; ++i){
		p = par[v][i].first;
		if(par[v][i].second == 0){
			mem[v] = MOD+1;
			return mem[v];
		}
		tmp = ways(p);
		if(tmp == MOD+1){
			mem[v] = MOD+1;
			return mem[v];
		}
		mem[v] += tmp;
		if(mem[v] >= MOD) mem[v] -= MOD;
	}

	return mem[v];
}

class DrivingPlans{
public:

	int count(int k, vector<int> A, vector<int> B, vector<int> C){
		memset(adj,-1,sizeof(adj));
		int i;

		N = k;
		for(i =0 ; i < A.size(); ++i){
			--A[i], --B[i];
			adj[A[i]][B[i]] = C[i];
			adj[B[i]][A[i]] = C[i];
		}

		dijkstra(0);

		memset(mem,-1,sizeof(mem));

		int sol = ways(N-1);

		return sol == MOD+1 ? -1 : sol;
	}
};
