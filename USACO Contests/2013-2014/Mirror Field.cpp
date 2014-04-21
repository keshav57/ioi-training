/*
 Created By: Malvika Joshi
 Problem: Mirror Field (February-2014 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=394
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

#define N_MAX 1010
#define DIR 4

using namespace std;

int next[2][4] = { { 3,2,1,0 }, { 2,3,0,1 } };
int adj[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

int visited[N_MAX][N_MAX][4];
int board[N_MAX][N_MAX];
int N,M;

int trace(int i, int j, int dir){
	int ref;

	ref = 0;

	while(i >= 0 && j >= 0 && i < M && j < N){
		if(visited[i][j][dir]){
			ref = -1;
			break;
		}
		visited[i][j][dir] = 1;
		++ref;
		dir = next[board[i][j]][dir];
		i += adj[dir][0];
		j += adj[dir][1];
	}

	return ref;
}

int main(){
	int i,j;
	char c;


	scanf("%d%d",&M,&N);

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			scanf(" %c",&c);
			board[i][j] = c == '\\';
		}
	}

	int max_ref;

	max_ref = -1;

	for(i = 0; i < M; ++i){
		max_ref = max(max_ref,trace(i,0,3));
		max_ref = max(max_ref,trace(i,N-1,2));
	}

	for(j = 0; j < N; ++j){
		max_ref = max(max_ref,trace(0,j,1));
		max_ref = max(max_ref,trace(M-1,j,0));
	}

	printf("%d\n",max_ref);

	return 0;
}
