/*
 Created By: Malvika Joshi
 Problem: Distant Pastures (November-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=191
*/

#include <stdio.h>
#define infinity 2000000000

typedef struct { int i,j; }node;

char Graph[40][40];
int N,A,B;
int D[40][40];
int visited[40][40];
node Q[1600];
int lookup[40][40];
int heap_size;

inline int left(int p){ return ((p+1)*2)-1; }
inline int right(int p){ return (p+1)*2; }
inline int parent(int c){ return ((c+1)/2)-1; }

void heaplify(int i){
	int l = left(i);
	int r = right(i);
	int smallest;
	node temp;

	if(l < heap_size && D[Q[l].i][Q[l].j] < D[Q[i].i][Q[i].j]){
		smallest = l;
	}else{
		smallest = i;
	}

	if(r < heap_size && D[Q[r].i][Q[r].j] < D[Q[smallest].i][Q[smallest].j]){
		smallest = r;
	}

	if(smallest != i){
		temp = Q[i];
		Q[i] = Q[smallest];
		Q[smallest] = temp;
		lookup[Q[i].i][Q[i].j] = i;
		lookup[Q[smallest].i][Q[smallest].j] = smallest;
		heaplify(smallest);
	}
}

void build_heap(){
	int n = heap_size;
	int i;
	for(i = (n/2)-1; i >= 0; i--){
		heaplify(i);
	}
}

node extract_min(){
	int j = heap_size-1;
	node temp;
	temp = Q[0];
	Q[0] = Q[j];
	lookup[Q[0].i][Q[0].j] = 0;
	heap_size--;
	heaplify(0);
	return temp;
}

void decrease_key(int x){
	int p = parent(x);
	node temp;

	if(p >= 0 && D[Q[x].i][Q[x].j] < D[Q[p].i][Q[p].j]){
		temp = Q[x];
		Q[x] = Q[p];
		Q[p] = temp;
		lookup[Q[p].i][Q[p].j] = p;
		lookup[Q[x].i][Q[x].j] = x;
		decrease_key(p);
	}
}

void relax(int i, int j){
	visited[i][j] = 1;
	int dist;

	if(i+1 < N && !visited[i+1][j]){
		dist = Graph[i][j] == Graph[i+1][j] ? A : B;
		dist+= D[i][j];
		if(D[i+1][j] > dist){
			D[i+1][j] = dist;
			decrease_key(lookup[i+1][j]);
		}
	}

	if(j+1 < N && !visited[i][j+1]){
		dist = Graph[i][j] == Graph[i][j+1] ? A : B;
		dist += D[i][j];
		if(D[i][j+1] > dist){
			D[i][j+1] = dist;
			decrease_key(lookup[i][j+1]);
		}
	}

	if(i-1 >= 0 && !visited[i-1][j]){
		dist = Graph[i][j] == Graph[i-1][j] ? A : B;
		dist += D[i][j];
		if(D[i-1][j] > dist){
			D[i-1][j] = dist;
			decrease_key(lookup[i-1][j]);
		}
	}

	if(j-1 >= 0 && !visited[i][j-1]){
		dist = Graph[i][j] == Graph[i][j-1] ? A : B;
		dist += D[i][j];
		if(D[i][j-1] > dist){
			D[i][j-1] = dist;
			decrease_key(lookup[i][j-1]);
		}
	}
}

int dijkstra(int si,int sj){
	int i, j, mdist = 0;

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			D[i][j] = infinity;
			visited[i][j] = 0;
		}
	}

	D[si][sj] = 0;
	heap_size = 0;

	for(i = 0;i < N; i++){
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
		relax(min.i,min.j);
	}

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			if(D[i][j] > mdist){
				mdist = D[i][j];
			}
		}
	}

	return mdist;

}

int main(void){
	int i,j,max = 0,temp;
	scanf("%d%d%d",&N,&A,&B);

	for(i = 0;i < N; i++){
		scanf("\n");
		for(j = 0;j < N; j++){
			Graph[i][j] = getchar();
		}
	}

	dijkstra(N-1,0);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			temp  = dijkstra(i,j);
			max = temp > max ? temp : max;
		}
	}

	printf("%d\n",max);
	return 0;
}
