/*
 Created By: Malvika Joshi
 Problem: Island Travels (January-2013 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=230
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <deque>
#include <cstring>
#include <utility>

#define NMAX 15
#define SMAX (1<<NMAX)
#define DMAX 52
#define INF 10000
#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

const point adj[4] = { make_pair(0,1), make_pair(0,-1), make_pair(1,0), make_pair(-1,0) };

char grid[DMAX][DMAX];
point pos[NMAX+2];
int N;

int swims[NMAX+2][NMAX+2];

int dist[DMAX][DMAX];
int id[DMAX][DMAX];
int visited[DMAX][DMAX];
deque<point> Q;

int R,C;

int dfs(int i, int j, int col){
	if(grid[i][j] || id[i][j] >= 0) return 0;

	id[i][j] = col;
	for(int k = 0; k  < 4; ++k){
		dfs(i+adj[k].x,j+adj[k].y,col);
	}

	return 1;
}

void bfs(point src){
	point v,u;
	int i,j;

	for(i = 0; i < R; ++i){
		for(j = 0; j < C; ++j){
			dist[i][j] = INF;
			visited[i][j] = 0;
		}
	}

	dist[src.x][src.y] = 0;
	Q.push_back(src);


	while(!Q.empty()){
		v = Q.front();

		if(visited[v.x][v.y]) continue;

		swims[id[src.x][src.y]][id[v.x][v.y]] =
				min(swims[id[src.x][src.y]][id[v.x][v.y]],dist[v.x][v.y]);

		visited[v.x][v.y] = 1;

		Q.pop_front();

		for(i = 0; i < 4; ++i){
			u = make_pair(v.x+adj[i].x,v.y+adj[i].y);

			if(u.x < 0 || u.x >= R || u.y < 0 || u.y >= C) continue;
			if(grid[u.x][u.y] < 0) continue;


			if(dist[v.x][v.y]+grid[u.x][u.y] >= dist[u.x][u.y]) continue;

			dist[u.x][u.y] = dist[v.x][v.y]+grid[u.x][u.y];

			if(grid[u.x][u.y]) Q.push_back(u);
			else Q.push_front(u);
		}

	}
}

void init(){
	int i,j;

	for(i = 0; i < R; ++i){
		for(j = 0; j < C; ++j){
			if(!dfs(i,j,N)) continue;
			pos[N++] = make_pair(i,j);
		}
	}

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j) swims[i][j] = INF;
		bfs(pos[i]);
	}
}


int min_swims[SMAX+2][NMAX+2];

int dp(){
	int sel,i,k;



	for(sel = 1; sel < (1<<N); ++sel){
		for(i = 0; i < N; ++i){
			if(!(sel&(1<<i))){
				min_swims[sel][i] = INF;
				continue;
			}
			if(!(sel^(1<<i))) continue;

			min_swims[sel][i] = INF;

			for(k = 0; k < N; ++k){
				if(k == i) continue;
				min_swims[sel][i] = min(min_swims[sel][i],min_swims[sel^(1<<i)][k]+swims[k][i]);
			}

		}
	}

	return *min_element(min_swims[sel-1],min_swims[sel-1]+N);
}

int main(){

	int i,j;

	scanf("%d%d",&R,&C);

	for(i = 0; i < R; ++i){
		for(j = 0; j < C; ++j){
			scanf(" %c",&grid[i][j]);
			id[i][j] = -1;
			grid[i][j] = grid[i][j] == '.' ? -1 : grid[i][j] == 'S';
		}
	}

	init();
	printf("%d\n",dp());

	return 0;
}

