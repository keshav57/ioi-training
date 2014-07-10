#include <algorithm>
#include <cassert>
#include <cstdio>
#include <set>
#include <iostream>
#include <cstring>

#define NMAX 210
#define MMAX 5010

using namespace std;

int path[NMAX][NMAX];

int dist[NMAX*MMAX];
int visited[NMAX*MMAX];
set<pair<int,int> > Q;

int adj[MMAX][NMAX][3];
pair<int,int> dir[3] = {make_pair(0,1), make_pair(0,-1), make_pair(1,0) };

int M,N;

void dijkstra(int src){
	//do bfs and update the paths for 0,N-1 in row M-1


	int v,u,i,d,x,y;

	memset(visited,0,sizeof(visited));
	Q.clear();
	Q.insert(make_pair(0,src));

	while(!Q.empty()){
		v = Q.begin()->second;
		d = Q.begin()->first;
		Q.erase(Q.begin());
		if(visited[v]) continue;
		visited[v] = 1;
		dist[v] = d;

		x = v/N;
		y = v%N;


		for(i = 0; i < 3; ++i){
			if(adj[x][y][i] < 0) continue;
			u = (x+dir[i].first)*N+(y+dir[i].second);
			Q.insert(make_pair(dist[v]+adj[x][y][i],u));
		}
	}

	v = 0;
	for(i = (N*M)-N; i < N*M; ++i){
		path[src][v++] = dist[i];
	}


}

int main(){
	int i;

	scanf("%d%d",&M,&N);

	memset(adj,-1,sizeof(adj));

	int j;
	for(i = 0; i < M; ++i){
		for(j = 0; j < N-1; j++){
			scanf("%d",&adj[i][j][0]);
			adj[i][j+1][1] = adj[i][j][0];
		}
	}

	for(i = 0; i < M-1; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&adj[i][j][2]);
		}
	}

	int q;
	scanf("%d",&q);

	for(i = 0; i < N; ++i){
		dijkstra(i);
	}

	int s  = 0;

	if(M > 20 && N > 20) s = 1;
	int typ;

	int ct = 0;
	while(q--){
		scanf("%d",&typ);
		scanf("%d%d",&i,&j);

		if(ct > 1000) s = 0;

		if(typ == 1){
			scanf("%d",&adj[i][j][0]);
			adj[i][j+1][1] = adj[i][j][0];
			if(s) continue;

			for(i = 0; i < N; ++i){
				dijkstra(i);
			}
			continue;
		}

		if(typ == 2){
			scanf("%d",&adj[i][j][2]);

			if(s) continue;

			for(i =0 ; i < N; ++i){
				dijkstra(i);
			}
			continue;
		}

		if(s){
			++ct;
			dijkstra(i);
		}

		printf("%d\n",path[i][j]);
	}

	return 0;
}

