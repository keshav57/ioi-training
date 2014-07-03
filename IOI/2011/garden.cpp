#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include <cstdio>

#define QMAX 2010
#define NMAX 150010
#define INF (1e9)

using namespace std;

int best[NMAX][2];
int deg[NMAX];

int out[NMAX*2];
vector<int> in[NMAX*2];

int dist[2][NMAX*2];

int N,M,P,len[2],src;

int visited[NMAX*2];

void dfs(int v){
	visited[v] = 1;

	int i,u;

	for(i = 0; i < (int)in[v].size(); ++i){
		u = in[v][i];
		if(visited[u]){
			assert(len[src] >= INF);
			len[src] = dist[src][v]-dist[src][u]+1;
			continue;
		}
		dist[src][u] = dist[src][v] + 1;
		dfs(u);
	}
}

int order[NMAX];
pair<int,int> queries[QMAX];
int ct[NMAX*2];
int ans[QMAX];

int Q;

int compare(int a, int b){
	return dist[src][a] < dist[src][b];
}

void init(){
	int i,v,k;

	memset(out,-1,sizeof(out));

	for(i = 0; i < N; ++i){
		v = i;
		for(k = 0; k < deg[i]; ++k,v+=N){
			out[v] = best[i][k];
		}
	}

	for(i = 0; i < N*2; ++i){
		if(out[i] < 0)	continue;

		v = out[i];
		if(deg[v] >= 2 && (i%N) == best[v][0]) v += N;
		in[v].push_back(i);
		out[i] = v;

	}

	for(i = 0; i < N*2; ++i) dist[0][i] = dist[1][i] = INF;
	len[0] = len[1] = INF+1;

	for(i = 0; i < N; ++i){
		order[i] = i;
	}

	for(;src<2;++src){
		memset(visited,0,sizeof(visited));
		dist[src][P+src*N] = 0;
		dfs(P+src*N);
	}

	sort(queries,queries+Q);
}

void compute(){
	int i,k,v;


	for(src=0; src < 2; ++src){
		sort(order,order+N,compare);
		k = 0;
		memset(ct,0,sizeof(ct));

		for(i = 0; i < Q; ++i){
			while(k < N && dist[src][order[k]] <= queries[i].first){
				v = dist[src][order[k++]];
				if(v >= INF) continue;
				ct[v%len[src]]++;
			}

			ans[queries[i].second] += (queries[i].first%len[src]) > 2*N ? 0 : ct[queries[i].first%len[src]];
		}
	}

}

int main(){
	int i,v,u;

	scanf("%d%d%d",&N,&M,&P);

	for(i =0; i < M; ++i){
		scanf("%d%d",&u,&v);
		if(deg[v] < 2) best[v][deg[v]++] = u;
		if(deg[u] < 2) best[u][deg[u]++] = v;
	}

	scanf("%d",&Q);

	for(i = 0; i < Q; ++i){
		scanf("%d",&queries[i].first);
		queries[i].second = i;
	}

	init();
	compute();

	for(i =0 ; i < Q; ++i){
		printf("%d ",ans[i]);
	}
	printf("\n");

	return 0;
}
