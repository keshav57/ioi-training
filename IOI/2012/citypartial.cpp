#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define NMAX 100010
#define MOD (int)(1e9)
#define SUB 2010
#define x first
#define y second

int lookup[SUB][SUB];

int N;
int dist[NMAX];
int visited[NMAX];
int tot;

const pair<int,int> adj[4] = {make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };

int Q[SUB*SUB];
int H,T;


int X[NMAX];
int Y[NMAX];


void bfs(int src){
	int i,v,u;
	pair<int,int> p;

	memset(visited,0,sizeof(visited));
	H = T=  0;
	v = src;
	dist[v]= 0;
	Q[T++] = v;
	visited[v] = 1;

	int vis = N;
	while(H < T){
		v = Q[H++];
		--vis;

		for(i= 0; i < 4; ++i){
			p.x = X[v]+adj[i].x;
			p.y = Y[v]+adj[i].y;

			u = lookup[p.x][p.y];
			if(u < 0) continue;
			if(visited[u]) continue;
			dist[u] = dist[v]+1;
			tot += dist[u]*(u<src);
			tot %= MOD;
			Q[T++] = u;
			visited[u] = 1;
		}
	}
}

int distance(int *A){
	int i;
	long long sum,all;

	sort(A,A+N);

	all = 0;
	sum = 0;
	for(i = 0; i < N; ++i){
		A[i] %= MOD;
		all += sum;
		all %= MOD;
		all -= (1LL*i*A[i]);
		all %= MOD;
		sum += A[i];
		sum %= MOD;
	}

	all = MOD-all;
	if(all < 0) all += MOD;

	all %= MOD;

	return all;
}

int C[SUB];

void compr(int *A){
	int i,n;
	for(i = 0; i < N; ++i){
		C[i] = A[i];
	}
	sort(C,C+N);
	n = unique(C,C+N)-C;

	for(i = 0; i < N; ++i){
		A[i] = lower_bound(C,C+n,A[i])-C+1;
	}
}

int main(){
	int i;

	scanf("%d",&N);

	for(i = 0; i < N; ++i) scanf("%d%d",&X[i],&Y[i]);

	if(N < SUB){
		memset(lookup,-1,sizeof(lookup));

		compr(X);
		compr(Y);

		for(i = 0; i < N; ++i){
			lookup[X[i]][Y[i]] = i;
		}

		for(i =0 ; i < N; ++i){
			bfs(i);
		}
		printf("%d\n",tot);
		return 0;
	}

	tot = distance(X);
	tot += distance(Y);

	printf("%d\n",tot%MOD);

	return 0;
}
