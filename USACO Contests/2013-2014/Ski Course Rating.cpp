#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include <cstdio>
#include <utility>

#define NMAX 510
#define EMAX (NMAX*NMAX*4)

using namespace std;

typedef pair<int,pair<int,int> > edge;
typedef long long lli;

int parent[NMAX*NMAX];
int size[NMAX*NMAX];
int rank[NMAX*NMAX];
int sel[NMAX*NMAX];

int T;
lli sum;

void make_set(int x){
	parent[x] = x;
	size[x] = 1;
	rank[x] = 0;
}

int find(int x){
	if (parent[x] == x){
		return x;
	}
	parent[x] = find(parent[x]);

	return parent[x];
}

void merge(int u, int v, int cost){
	int root;

	root = rank[u] > rank[v] ? u : v;
	parent[root^u^v] = root;

	rank[root] += rank[u] == rank[v];
	size[root] = size[u]+size[v];
	sel[root] = sel[u]+sel[v];

	if(size[root] < T) return;
	sum += (1LL*cost*sel[root]);


	sel[root] = 0;
}

int adj[4][2] = { {0,1} , {0,-1} , {-1,0} , {1,0} };
int height[NMAX][NMAX];

edge edges[EMAX];

int N,M,E;

int main(){

	int i,j,k,ti,tj;

	freopen("skilevel.in","r",stdin);
	freopen("skilevel.out","w",stdout);

	scanf("%d%d%d",&M,&N,&T);

	for(i = 0; i < M; ++i){
		for(j =0; j < N; ++j){
			scanf("%d",&height[i][j]);
		}
	}

	for(i =0 ; i < M; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&sel[i*N+j]);
			make_set(i*N+j);
		}
	}


	for(i =0 ; i < M; ++i){
		for(j = 0; j < N; ++j){
			for(k = 0; k < 4; ++k){
				ti = i+adj[k][0];
				if(ti < 0 || ti >= M) continue;
				tj = j+adj[k][1];
				if(tj < 0 || tj >= N) continue;

				edges[E++] = make_pair(abs(height[ti][tj]-height[i][j]),\
						make_pair((ti*N+tj),(i*N+j)));
			}
		}
	}

	sort(edges,edges+E);

	for(k =0 ; k < E; ++k){
		i = find(edges[k].second.first);
		j = find(edges[k].second.second);
		if(i == j) continue;
		merge(i,j,edges[k].first);
	}

	printf("%lld\n",sum);

	return 0;
}
