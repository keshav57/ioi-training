/*
 Created By: Malvika Joshi
 Problem: Happy Journey (IOITC-2013 Final 2)
*/


#include <iostream>
#include <cassert>
#include <vector>
#include <cstdio>

#define NMAX 100010

using namespace std;

vector<pair<char,int> > adj[NMAX];
int N,M;

vector<pair<char,int> > par[NMAX];
int dist[NMAX];

int Q[NMAX];
int H,T;

void bfs(int src){
	int v,u,i;

	for(i =0 ; i < N; ++i){
		dist[i] = NMAX;
	}

	dist[src] = 0;
	Q[T++] = src;

	while(H < T){
		v = Q[H++];

		for(i =0 ; i < (int)adj[v].size(); ++i){
			u = adj[v][i].second;

			if(dist[u] > dist[v]+1){
				Q[T++] = u;
				dist[u] = dist[v]+1;
				par[u].push_back(make_pair(adj[v][i].first,v));
				continue;
			}

			if(dist[u] < dist[v]+1) continue;
			par[u].push_back(make_pair(adj[v][i].first,v));
		}
	}

//	for(i = 0; i < N; ++i){
//		cout << i+1 << endl;
//		for(int k = 0; k < (int)par[i].size(); ++k){
//			cout << par[i][k].second+1 << " ";
//		}
//		cout << endl << endl;
//	}
}

pair<char,int> nxt_lev[2*NMAX];
int cur[2*NMAX];
int L,C;
int visited[NMAX];

void bfs2(int src){
	int v,i,k;
	char rank;



	cur[C++] = src;

	while(C){
		L = 0;

		rank = 'z'+1;
		for(i = 0; i < C; ++i){
			v = cur[i];
			for(k = 0; k < par[v].size(); ++k){
				nxt_lev[L++] = par[v][k];
				rank = min(rank,par[v][k].first);
			}
		}

		if(rank <= 'z') printf("%c",rank);

		C = 0;

		for(i = 0; i < L; ++i){
			if(nxt_lev[i].first > rank || visited[nxt_lev[i].second]) continue;
			assert(nxt_lev[i].first == rank);
			cur[C++] = nxt_lev[i].second;
			visited[nxt_lev[i].second] = 1;
		}
	}
}

int main(){
	int i,a,b,src,tar;
	char c;

	scanf("%d%d",&N,&M);
	scanf("%d%d",&src,&tar);
	--src,--tar;

	for(i = 0; i < M; ++i){
		scanf("%d %c %d",&a,&c,&b);
		--a,--b;
		adj[a].push_back(make_pair(c,b));
		adj[b].push_back(make_pair(c,a));
	}

	bfs(tar);
	bfs2(src);
	printf("\n");
	return 0;
}
