/*
 Created By: Malvika Joshi
 Problem: Cow Beauty Pageant (Novermber-2011 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=88
*/


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

#define MAXN 52
#define INF 3000
#define x first
#define y second

using namespace std;

const pair<int,int> adj[4] = { make_pair(0,1), make_pair(0,-1), make_pair(-1,0), make_pair(1,0) };

int grid[MAXN][MAXN];
int M,N;

//bfs data
int dist[3][MAXN][MAXN];
int paint_dist[MAXN][MAXN];
int visited[MAXN][MAXN];
pair<int,int> Q[MAXN*MAXN];
int H,T;


int fill(int i, int j, int tar, int col){
	if(i < 0 || j < 0 || i >= M || j >= N || grid[i][j] != tar) return 0;
	int k;
	grid[i][j] = col;
	for(k = 0; k < 4; ++k){
		fill(i+adj[k].x, j+adj[k].y, tar, col);
	}

	return 1;
}

void enqueue(int i, int j, int col, int src, int d){
	if(i < 0 || j < 0 || i >= M || j >= N || grid[i][j] != col) return;
	if(visited[i][j]) return;

	int k;
	Q[T++] = make_pair(i,j);
	dist[src][i][j] = d;
	visited[i][j] = 1;

	for(k = 0; k < 4; ++k){
		enqueue(i+adj[k].x, j+adj[k].y, col, src, d);
	}
}

void bfs(int src){
	int k;
	pair<int,int> v,u;

	while(H < T){
		v  = Q[H++];
		paint_dist[v.x][v.y] += dist[src][v.x][v.y];

		for(k = 0; k < 4; ++k){
			u = make_pair(v.x+adj[k].x,v.y+adj[k].y);
			if(u.x >= M || u.y >= N || u.x < 0 || u.y < 0 || visited[u.x][u.y]) continue;

			if(grid[u.x][u.y] != 3){
				enqueue(u.x,u.y,grid[u.x][u.y],src,dist[src][v.x][v.y]+1);
				continue;
			}

			visited[u.x][u.y] = 1;
			dist[src][u.x][u.y] = dist[src][v.x][v.y]+1;
			Q[T++] = u;
		}

	}
}

void print(int src){
	int i,j;
	for(i  =0; i < M; i++){
		for(j = 0; j  < N; j++){
			printf("%d ",dist[src][i][j]);
		}
		printf("\n");
	}
}

void init(int src){
	int i,j;

	memset(visited,0,sizeof(int)*MAXN*MAXN);
	H = 0;
	T = 0;

	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			if(!(fill(i,j,4,src))) continue;
			enqueue(i,j,src,src,0);
			bfs(src);
			return;
		}
	}
}


int main(){

	int i,j,src,min_paint;
	char c;

	scanf("%d%d",&M,&N);

	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			scanf(" %c",&c);
			grid[i][j] = (c == 'X')+3;
		}
	}

	for(src = 0; src < 3; src++){
		init(src);
	}

	min_paint = INF;

	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			min_paint = min(min_paint, paint_dist[i][j] - 2);
		}
	}

	printf("%d\n",min_paint);

	return 0;
}
