/*
 Created By: Malvika Joshi
 Problem: maze1
 Link: http://cerberus.delos.com:791/usacoprob2?S=maze1&a=AVzY99Ha8aa
*/

#include <stdio.h>
#include <string.h>

#define infinity 1000000

typedef struct { int i, j; } vertex;

int Maze[210][100];
int visited[210][100];
int dist[210][100];
int M,N;
vertex Q[20000];
int H,T;
vertex exits[2];

inline int min(int a, int b){ return a < b ? a : b; }

void init(int b){
	int i,j;
	for(i = 0;i < M; i++){
		for(j = 0;j < N; j++){
			visited[i][j] = 0;
			if(b){ dist[i][j] = infinity; }
		}
	}
}

void bfs(vertex s){
	vertex k;

	H = 0;
	T = 0;

	Q[T++] = s;
	visited[s.i][s.j] = 1;
	dist[s.i][s.j] = 1;

	while(H < T){
		k = Q[H++];

		if(Maze[k.i+1][k.j] && !visited[k.i+2][k.j]){
			Q[T].i = k.i+2;
			Q[T++].j = k.j;
			dist[k.i+2][k.j] = min(dist[k.i][k.j] + 1,dist[k.i+2][k.j]);
			visited[k.i+2][k.j] = 1;
		}
		if(Maze[k.i-1][k.j] && !visited[k.i-2][k.j]){
			Q[T].i = k.i-2;
			Q[T++].j = k.j;
			dist[k.i-2][k.j] = min(dist[k.i][k.j] + 1,dist[k.i-2][k.j]);
			visited[k.i-2][k.j] = 1;
		}
		if(Maze[k.i][k.j-1] && !visited[k.i][k.j-2]){
			Q[T].i = k.i;
			Q[T++].j = k.j-2;
			dist[k.i][k.j-2] = min(dist[k.i][k.j] + 1,dist[k.i][k.j-2]);
			visited[k.i][k.j-2] = 1;
		}
		if(Maze[k.i][k.j+1] && !visited[k.i][k.j+2]){
			Q[T].i = k.i;
			Q[T++].j = k.j+2;
			dist[k.i][k.j+2] = min(dist[k.i][k.j] + 1,dist[k.i][k.j+2]);
			visited[k.i][k.j+2] = 1;
		}
	}

}


int main(){
	int i,j,m,n,e = 0;
	char c;

	scanf("%d%d",&n,&m);
	M = m*2+1;
	N = n*2+1;

	for(i = 0;i < M; i++){
		getchar();
		for(j = 0;j < N; j++){
			c = getchar();
			Maze[i][j] = c == ' ' ? 1 : 0;
			if((i == 0 || i == M-1 || j == 0 || j == N-1) && Maze[i][j]){
				if(i == 0){
					exits[e].j = j;
					exits[e].i = i+1;
				}else if(i == M-1){
					exits[e].j = j;
					exits[e].i = i-1;
				}else if(j == 0){
					exits[e].i = i;
					exits[e].j = j+1;
				}else{
					exits[e].i = i;
					exits[e].j = j-1;
				}
				e++;
				Maze[i][j] = 0;
			}
		}
	}

	init(1);
	bfs(exits[0]);
	init(0);
	bfs(exits[1]);

	int max= 0;

	for(i = 1;i < M; i+=2){
		for(j= 1; j < N; j+=2){
			if(dist[i][j] > max) max = dist[i][j];
		}
	}

	printf("%d\n",max);

	return 0;
}
