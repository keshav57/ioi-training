/*
 Created By: Malvika Joshi
 Problem: Delivery Route (January-2012 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=106
*/

#include <stdio.h>
#include <stdlib.h>


#define RANGE 1000010
#define MAXN 210
#define INF 200000010

typedef struct { int x,y,id; }point;

int comparex(const void *a,const void *b){
	const point *p1 = a;
	const point *p2 = b;
	return p1->x-p2->x;
}

int comparey(const void *a,const void *b){
	const point *p1 = a;
	const point *p2 = b;
	return p1->y-p2->y;
}

point compr[MAXN];
point orig[MAXN];
point Q[MAXN*MAXN];
int x[MAXN];
int y[MAXN];
int visited[MAXN][MAXN];
int dist[MAXN][MAXN];
int H,T,N,X,Y;

void init(){
	int cval[RANGE];
	int i,k;

	k = 1;
	qsort(orig,N,sizeof(point),comparex);

	for(i = 0; i < N; i++){
		if(i < N-1 && orig[i].x == orig[i+1].x) continue;
		x[k] = orig[i].x;
		cval[orig[i].x] = k++;
		if(i < N-1 && orig[i+1].x == orig[i].x+1) continue;
		x[k] = orig[i].x+1;
		cval[orig[i].x+1] = k++;
	}

	x[0] = x[1]-1;

	X = k;

	for(i = 0; i < N; i++) compr[orig[i].id].x = cval[orig[i].x];

	k = 1;
	qsort(orig,N,sizeof(point),comparey);
	for(i = 0; i < N; i++){
		if(i < N-1 && orig[i].y == orig[i+1].y) continue;
		y[k] = orig[i].y;
		cval[orig[i].y] = k++;
		if(i < N-1 && orig[i+1].y == orig[i].y+1) continue;
		y[k] = orig[i].y+1;
		cval[orig[i].y+1] = k++;
	}

	y[0] = y[1]-1;

	Y = k;

	for(i = 0; i < N; i++) compr[orig[i].id].y = cval[orig[i].y];
}




void set(int a, int v){
	int i,j;
	for(i = 0; i < X; i++)
		for(j = 0; j < Y; j++)
			if(a) visited[i][j] = v; else  dist[i][j] = v;
}

inline int min(int a, int b){ return a < b ? a : b; }

point make_point(int x,int y){
	point p = {x,y,0};
	return p;
}

int bfs(point s,point t){
	point v;

	H = 0,T = 0;
	Q[T++] = s;
	visited[s.x][s.y] = 1;
	dist[s.x][s.y] = 0;

	while(H < T){
		v = Q[H++];

		if(v.x < X-1){
			dist[v.x+1][v.y] = min(dist[v.x+1][v.y],dist[v.x][v.y]+x[v.x+1]-x[v.x]);
			if(!visited[v.x+1][v.y]) Q[T++] = make_point(v.x+1,v.y);
			visited[v.x+1][v.y] = 1;
		}

		if(v.x > 0){
			dist[v.x-1][v.y] = min(dist[v.x-1][v.y],dist[v.x][v.y]+x[v.x]-x[v.x-1]);
			if(!visited[v.x-1][v.y]) Q[T++] = make_point(v.x-1,v.y);
			visited[v.x-1][v.y] = 1;
		}

		if(v.y < Y-1){
			dist[v.x][v.y+1] = min(dist[v.x][v.y+1],dist[v.x][v.y]+y[v.y+1]-y[v.y]);
			if(!visited[v.x][v.y+1]) Q[T++] = make_point(v.x,v.y+1);
			visited[v.x][v.y+1] = 1;
		}


		if(v.y > 0){
			dist[v.x][v.y-1] = min(dist[v.x][v.y-1],dist[v.x][v.y]+y[v.y]-y[v.y-1]);
			if(!visited[v.x][v.y-1]) Q[T++] = make_point(v.x,v.y-1);
			visited[v.x][v.y-1] = 1;
		}
	}

	return dist[t.x][t.y] >= INF ? -1 : dist[t.x][t.y];
}

inline int next(int i){ return i < N-1 ? i+1 : 0; }

int main(){

	int i,j,tmp,total;

	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%d%d",&orig[i].x,&orig[i].y);
		orig[i].id = i;
	}

	init();


	total = 0;
	for(i = 0; i < N; i++){
		set(1,0);
		set(0,INF);

		for(j = 0; j < N; j++){
			if(j == i || j == next(i)) continue;
			visited[compr[j].x][compr[j].y] = 1;
		}

		tmp = bfs(compr[i],compr[next(i)]);
		if(tmp < 0){
			printf("%d\n",tmp);
			exit(0);
		}
		total += tmp;
	}

	printf("%d\n",total);
	return 0;
}

