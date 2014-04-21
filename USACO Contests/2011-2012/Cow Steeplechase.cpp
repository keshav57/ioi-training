/*
 Created By: Malvika Joshi
 Problem: Cow Steeplechase (November-2011 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=93
*/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cstring>

#define N_MAX 260
#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

int intersect(point x1, point x2, point y1, point y2){
	return ( (y1.x >= x1.x && y1.x <= x2.x) && (x1.y >= y1.y && x1.y <= y2.y) );
}

pair<point,point> xpar[N_MAX];
pair<point,point> ypar[N_MAX];

int N,X,Y;

int adj[N_MAX][N_MAX];
int visited[N_MAX];
int match[N_MAX];

int dfs(int u){
	int v;

	for(v = 0; v < Y; ++v){
		if(visited[v] || !adj[u][v]) continue;
		visited[v] = 1;
		if(match[v] < 0 || dfs(match[v])){
			match[v] = u;
			return 1;
		}
	}

	return 0;
}

int bipartite_matching(){
	int u,matched;

	memset(match,-1,sizeof(int)*N_MAX);
	matched = 0;

	for(u = 0; u < X; ++u){
		memset(visited,0,sizeof(int)*N_MAX);
		matched += dfs(u);
	}

	return matched;
}

int main(){

	int i,x1,x2,y1,y2,j;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

		if(x1 > x2) swap(x1,x2);
		if(y1 > y2) swap(y1,y2);

		if(y1 == y2) xpar[X++] = make_pair(make_pair(x1,y1), make_pair(x2,y2));
		else if(x1 == x2) ypar[Y++] = make_pair(make_pair(x1,y1), make_pair(x2,y2));
	}

	for(i = 0; i < X; ++i){
		for(j = 0; j < Y; ++j){
			adj[i][j] = intersect(xpar[i].first,xpar[i].second,
					ypar[j].first,ypar[j].second);
		}
	}

	printf("%d\n",X+Y-bipartite_matching());

	return 0;
}
