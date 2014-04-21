/*
 Created By: Malvika Joshi
 Problem: Relocation (February-2012 Siver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=117
*/


#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>

#define MAXN 10010
#define MAXM 50010
#define MAXK 6
#define INF  20000010

using namespace std;

vector<pair<int,int> > adjacent[MAXN];
set<pair<int,int> > Q;

int D[MAXK][MAXN];
int visited[MAXN];
int ismarket[MAXN];
int market[MAXK];
int N,K,M;

void dijkstra(int src){
	int i,wt,u,v,t;

	for(i = 0; i < N; i++) D[src][i] = INF, visited[i] = 0;

	Q.clear();
	Q.insert(make_pair(0,market[src]));
	D[src][market[src]] = 0;

	while(!(Q.empty())){

		v = Q.begin()->second;
		wt = Q.begin()->first;

		if(wt >= INF) return;

		Q.erase(Q.begin());

		if(visited[v]) continue;
		visited[v] = 1;

		for(i = 0; i < (int)adjacent[v].size(); ++i){
			u = adjacent[v][i].first;
			t = adjacent[v][i].second + wt;
			if(t < D[src][u]){
				D[src][u] = t;
				Q.insert(make_pair(t,u));
			}
		}

	}

}


int init(){
	int order[5] = {0,1,2,3,4};
	int k,i,mdist,dist;

	for(k = 0; k < K; k++)	dijkstra(k);

	mdist = 7*INF;


	do {
		dist = 0;
		for(k = 0; k < K-1; k++) dist += D[order[k]][market[order[k+1]]];
		for(i = 0; i < N; i++){
			if(ismarket[i]) continue;
			mdist = min(mdist,dist+D[order[0]][i] + D[order[K-1]][i]);
		}
	}while(next_permutation(order,order+K));

	return mdist;
}

int main(){

	int i,j,k,m;

	scanf("%d%d%d",&N,&M,&K);

	for(i = 0; i < K; i++){
		scanf("%d",&market[i]);
		ismarket[--market[i]] = 1;
	}

	for(m = 0; m < M; m++){
		scanf("%d%d%d",&i,&j,&k);
		--i,--j;
		adjacent[i].push_back(make_pair(j,k));
		adjacent[j].push_back(make_pair(i,k));
	}

	k = init();
	printf("%d\n",k);

	return 0;
}
