/*
 Created By: Malvika Joshi
 Problem: Hide and Seek (IOITC-2012 Final-1)
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <set>
#include <map>

#define COOR_MAX 1700
#define RECT_MAX 410
#define x first
#define y second
#define INF (long long)(1e10)

using namespace std;

typedef pair<int,int> point;
typedef pair<point,point> rect;
typedef long long lli;

//compression
map<int,int> compr;
int lookup[2][COOR_MAX];

//input
rect rects[RECT_MAX];
int N,M,B;
point src,tar;

//shortest_path
const point adj[4] = { make_pair(0,1), make_pair(0,-1), make_pair(-1,0), make_pair(1,0) };

char grid[COOR_MAX][COOR_MAX];
char visited[COOR_MAX][COOR_MAX];
set<pair<lli,point> > Q;


int compress(int *list, int n, int axis, int lim){
	int val,i;

	compr.clear();
	sort(list,list+n);

	val = 0;
	for(i = 0; i < n; ++i){
		if(list[i] < 0 || list[i] >= lim) continue;
		if(list[i] && list[i] != list[i-1])	++val;
		compr[list[i]] = val;
		lookup[axis][val] = list[i];
	}

	return val+1;
}

void init(){

	int i,j,n,k;
	int list[COOR_MAX];

	n = 0;
	list[n++] = src.x-1;
	list[n++] = src.x+1;
	list[n++] = src.x;

	list[n++] = tar.x-1;
	list[n++] = tar.x+1;
	list[n++] = tar.x;

	for(i = 0; i < B; ++i){
		list[n++] = rects[i].first.x;
		list[n++] = rects[i].second.x;
		list[n++] = rects[i].second.x+1;
		list[n++] = rects[i].first.x-1;
	}

	M = compress(list,n,0,M);

	src.x = compr[src.x];
	tar.x = compr[tar.x];

	n = 0;

	list[n++] = src.y-1;
	list[n++] = src.y+1;
	list[n++] = src.y;

	list[n++] = tar.y-1;
	list[n++] = tar.y+1;
	list[n++] = tar.y;


	for(i = 0; i < B; ++i){
		rects[i].first.x = compr[rects[i].first.x];
		rects[i].second.x = compr[rects[i].second.x];
		list[n++] = rects[i].first.y;
		list[n++] = rects[i].second.y;
		list[n++] = rects[i].second.y+1;
		list[n++] = rects[i].first.y-1;
	}

	N = compress(list,n,1,N);

	src.y = compr[src.y];
	tar.y = compr[tar.y];

	for(i = 0; i < B; ++i){
		rects[i].first.y = compr[rects[i].first.y];
		rects[i].second.y = compr[rects[i].second.y];
	}

	for(k = 0; k < B; ++k){
		for(i = rects[k].first.x; i <= rects[k].second.x; ++i){
			for(j = rects[k].first.y; j <= rects[k].second.y; ++j){
				grid[i][j] = 1;
			}
		}
	}
}

lli dijkstra(){
	int k;
	lli dist,cost;
	point v,u;

	Q.insert(make_pair(0,src));

	while(!Q.empty()){
		v = Q.begin()->second;
		dist = Q.begin()->first;
		Q.erase(Q.begin());

		if(visited[v.x][v.y]) continue;
		if(v == tar) return dist;

		visited[v.x][v.y] = 1;

		for(k = 0; k < 4; ++k){
			u = make_pair(v.x+adj[k].x,v.y+adj[k].y);
			if(u.x < 0 || u.x >= M) continue;
			if(u.y < 0 || u.y >= N) continue;
			if(grid[u.x][u.y]) continue;

			cost = abs(lookup[0][v.x]-lookup[0][u.x]) + abs(lookup[1][v.y]-lookup[1][u.y]);
			Q.insert(make_pair(dist+cost,u));
		}
	}

	return -1;
}

int main(){

	int i;

	scanf("%d%d%d",&M,&N,&B);

	scanf("%d%d%d%d",&src.x,&src.y,&tar.x,&tar.y);

	for(i = 0; i < B; ++i){
		scanf("%d%d",&rects[i].first.x,&rects[i].first.y);
		scanf("%d%d",&rects[i].second.x,&rects[i].second.y);
	}

	init();
	printf("%lld\n",dijkstra());

	return 0;
}
