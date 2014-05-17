#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cassert>

#define MMAX 210
#define NMAX 260
#define LMAX 32

using namespace std;

int st[LMAX];
int adj[MMAX][MMAX];

int conn[NMAX][NMAX];

int N,M,L;

int dist[NMAX];
int Q[MMAX];
int H,T;

int reg[NMAX][MMAX];

void bfs(int src){
	int i,v;

	H = T = 0;

	for(i = 0; i < M; ++i) dist[i] = -1;
	dist[src] = 0;

	Q[T++] = src;

	while(H < T){
		v = Q[H++];
		for(i = 0; i < M; ++i){
			if(dist[i] >= 0 || !adj[v][i]) continue;
			dist[i] = dist[v]+1;
			Q[T++] = i;
		}
	}
}

int cross_sum(int src){
	int sum,i,k,cross;

	bfs(src);

	sum = 0;

	for(i = 0; i < L; ++i){
		cross = N*N;

		for(k = 0; k < M; ++k){
			if(!reg[st[i]][k]) continue;
			assert(dist[k] >= 0);
			cross = min(dist[k],cross);
		}

		sum += cross;
	}

	return sum;
}

int main(){
	int i,k,n,p,s,mincross;

	scanf("%d%d%d",&M,&N,&L);

	memset(conn,-1,sizeof(int)*NMAX*NMAX);

	for(i = 0; i < L; ++i){
		scanf("%d",&st[i]);
		--st[i];
	}

	for(i =0; i < M; ++i){
		scanf("%d",&n);
		p = -1;
		s = -1;
		k = -1;
		while(n--){
			scanf("%d",&k);
			--k;

			reg[k][i] = 1;

			if(p < 0){
				p = k;
				s = p;
				continue;
			}

			conn[p][k] < 0 ? conn[p][k] = i : conn[k][p] = i;
			p = k;
		}
		p = s;
		if(s < 0) continue;
		conn[p][k] < 0 ? conn[p][k] = i : conn[k][p] = i;
	}

	for(i = 0; i < N; ++i){
		for(k = i+1; k < N; ++k){
			if(conn[i][k] < 0 && conn[k][i] < 0) continue;
			assert(conn[i][k] >= 0 && conn[k][i] >= 0);

			adj[conn[i][k]][conn[k][i]] = 1;
			adj[conn[k][i]][conn[i][k]] = 1;
		}
	}


	mincross = N*N;
	k = -1;

	for(i = 0; i < M; ++i){
		s = cross_sum(i);
		if(s < mincross){
			mincross = s;
			k  = i;
		}
	}

	printf("%d\n%d\n",mincross,k+1);
	return 0;
}
