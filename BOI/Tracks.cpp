#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <cstdio>

#define NMAX 4010

using namespace std;

pair<int,int> Q[NMAX*NMAX];
pair<int,int> next[NMAX*NMAX];

int H,T,N;
int visited[NMAX][NMAX];
int cleared[NMAX][NMAX];
char grid[NMAX][NMAX];

const int adj[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
int R,C;

int bfs(){
	int i,v,x,comp,y,x1,y1;
	char col;

	next[N++] = make_pair(0,0);

	comp = 0;
	col = grid[0][0];
	visited[0][0] = 1;

	while(N){

		H = T = 0;
		while(N--) Q[T++] = next[N];
		++N;

		while(H < T){
			x = Q[H].first;
			y = Q[H++].second;

			for(i = 0; i < 4; ++i){
				x1 = adj[i][0]+x;
				y1 = adj[i][1]+y;

				if(x1 < 0 || x1 >= R) continue;
				if(y1 < 0 || y1 >= C) continue;

				if(visited[x1][y1] || cleared[x1][y1]) continue;
				if(grid[x1][y1] == '.') continue;
				if(grid[x1][y1]^col){
					next[N++] = make_pair(x1,y1);
					cleared[x1][y1] = 1;
					continue;
				}
				visited[x1][y1] = 1;
				Q[T++] = make_pair(x1,y1);
			}

		}

		++comp;
		col ^= 'F'^'R';
	}

	return comp;
}


int main(){
	int i;

	scanf("%d%d",&R,&C);

	for(i = 0; i < R; ++i){
		scanf("%s",grid[i]);
		assert(strlen(grid[i])  == C);
	}

	printf("%d\n",bfs());

	return 0;
}
