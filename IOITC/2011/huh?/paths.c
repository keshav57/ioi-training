/*
 Problem: Grid Paths [Standard]
*/

#include <stdio.h>
#include <stdlib.h>
#define infinity 100000
#define North 0
#define East 90
#define South 180
#define West 270

typedef struct { int i,j; } node;
typedef struct { int dist,dir; }time_i;

inline int left(int p){ return (p+1)*2-1;}
inline int right(int p){ return (p+1)*2; }
inline int parent(int c){ return (c+1)/2-1;}

int Graph[400][400];
int lookup[400][400];
int visited[400][400];
time_i D[400][400];
int M,N,heap_size,si,sj;
node Q[160000];

void heaplify(int x){
	int smallest,l,r;
	node temp;

	l = left(x);
	r = right(x);
	smallest = x;

	if(l < heap_size && D[Q[l].i][Q[l].j].dist < D[Q[x].i][Q[x].j].dist){
		smallest = l;
	}

	if(r < heap_size && D[Q[r].i][Q[r].j].dist < D[Q[smallest].i][Q[smallest].j].dist){
		smallest = r;
	}

	if(smallest != x){
		temp = Q[x];
		Q[x] = Q[smallest];
		Q[smallest] = temp;
		lookup[Q[x].i][Q[x].j] = x;
		lookup[Q[smallest].i][Q[smallest].j] = smallest;
		heaplify(smallest);
	}

	return;
}

void build_heap(void){
	int i,n = heap_size;
	for(i = (n/2)-1; i>= 0; i--){
		heaplify(i);
	}
	return;
}

node extract_min(void){
	int j = heap_size-1;
	node temp;

	temp = Q[0];
	Q[0] = Q[j];

	lookup[Q[j].i][Q[j].j] = j;
	heap_size--;
	heaplify(0);

	return temp;
}

void decrease_key(int x){
	int p = parent(x);
	node temp;

	if(p >= 0 && D[Q[p].i][Q[p].j].dist > D[Q[x].i][Q[x].j].dist){
		temp = Q[x];
		Q[x] = Q[p];
		Q[p] = temp;

		lookup[Q[x].i][Q[x].j] = x;
		lookup[Q[p].i][Q[p].j] = p;

		decrease_key(p);
	}
	return;
}

int getdtime(int i, int j, int tdir){
	int diff = abs(D[i][j].dir - tdir);

	if(i == si && j == sj){
		return 0;
	}
	if(diff == 90 || diff == 270){
		return 1;
	}
	if(diff == 180){
		return 2;
	}

	return 0;
}

void relax(int i, int j){

	visited[i][j] = 1;
	int dist;

	if(i+1 < M && Graph[i+1][j] != -1 && !visited[i+1][j]){
		dist = getdtime(i,j,South) + D[i][j].dist + Graph[i+1][j];
		if(D[i+1][j].dist > dist){
			D[i+1][j].dist = dist;
			D[i+1][j].dir = South;
			decrease_key(lookup[i+1][j]);
		}
	}

	if(j+1 < N && Graph[i][j+1] != -1 && !visited[i][j+1]){
		dist = getdtime(i,j,East) + D[i][j].dist + Graph[i][j+1];
		if(D[i][j+1].dist > dist){
			D[i][j+1].dist = dist;
			D[i][j+1].dir = East;
			decrease_key(lookup[i][j+1]);
		}
	}

	if(i-1 >= 0 && Graph[i-1][j] != -1 &&!visited[i-1][j]){
		dist = getdtime(i,j,North) + D[i][j].dist + Graph[i-1][j];
		if(D[i-1][j].dist > dist){
			D[i-1][j].dist = dist;
			D[i-1][j].dir = North;
			decrease_key(lookup[i-1][j]);
		}
	}

	if(j-1 >= 0 && Graph[i][j-1] != -1 && !visited[i][j-1]){
		dist = getdtime(i,j,West) + D[i][j].dist + Graph[i][j-1];
		if(D[i][j-1].dist > dist){
			D[i][j-1].dist = dist;
			D[i][j-1].dir = West;
			decrease_key(lookup[i][j-1]);
		}
	}

	return;
}

void dijkstra(void){
	int i,j;

	for(i = 0;i< M ; i++){
		for(j = 0;j < N; j++){
			visited[i][j] = 0;
			D[i][j].dist = infinity;
		}
	}

	D[si][sj].dist = 0;
	D[si][sj].dir = 0;
	heap_size= 0;

	for(i = 0;i < M ;i ++){
		for(j = 0;j < N; j++){
			Q[heap_size].i = i;
			Q[heap_size].j = j;
			lookup[i][j] = heap_size;
			heap_size++;
		}
	}

	build_heap();
	node min;

	while(heap_size > 0){
		min = extract_min();
		if(D[min.i][min.j].dist == infinity){
			return;
		}
		relax(min.i,min.j);
	}

	return;
}

int main(void){

	int i,j,ei,ej;
	char temp;

	scanf("%d%d",&M,&N);

	for(i = 0;i < N; i++){
		scanf("\n");
		for(j = 0; j < N; j++){
			temp = getchar();
			if(temp == 'S'){
				si = i;
				sj = j;
				Graph[i][j] = 0;
			}else if(temp == 'T'){
				ei = i;
				ej = j;
				Graph[i][j] = 0;
			}else if(temp == '#'){
				Graph[i][j] = -1;
			}else {
				Graph[i][j] = temp -'0';
			}
		}
	}

	dijkstra();

	printf("%d",D[ei][ej].dist == infinity ? -1 : D[ei][ej].dist);

	return 0;
}
