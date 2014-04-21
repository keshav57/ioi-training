/*
 Created By: Malvika Joshi
 Problem: The Castle (IOI-1994)
 Link: http://www.ioinformatics.org/locations/ioi94/contest/day1prb2/problem.shtml 
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define NMAX 52

using namespace std;

const int adj[4][2] = {{0,-1}, {-1,0} , {0,1}, {1,0} };
int walls[NMAX][NMAX][4];

char visited[NMAX][NMAX];

int M,N;

int fill(int i, int j){
	if(i >= M || i < 0 || j >= N || j < 0) return 0;
	if(visited[i][j]) return 0;

	visited[i][j] = 1;

	int k,tot;

	tot = 1;
	for(k =0 ; k < 4; ++k){
		if(walls[i][j][k]) continue;
		tot += fill(adj[k][0]+i,adj[k][1]+j);
	}

	return tot;
}

int main(){

	int i,j,sum,k;
	int max_room,rooms,tmp;
	int rm_i,rm_j,rm_k;
	char dir;

	scanf("%d%d",&M,&N);

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&sum);
			for(k = 3; k >= 0; --k){
				if(sum < (1<<k)) continue;
				sum -= (1<<k);
				walls[i][j][k] = 1;
			}
		}
	}

	max_room = 0;
	rooms = 0;

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			if(visited[i][j]) continue;
			++rooms;
			max_room = max(max_room,fill(i,j));
		}
	}

	printf("%d\n%d\n",rooms,max_room);

	max_room = 0;
	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			for(k =0 ; k < 4; ++k){
				if(!walls[i][j][k]) continue;
				memset(visited,0,NMAX*NMAX);
				walls[i][j][k] = 0;
				tmp = fill(i,j);
				if(tmp > max_room){
					rm_i = i;
					rm_j = j;
					rm_k = k;
					max_room = tmp;
				}

				walls[i][j][k] = 1;
			}
		}
	}


	dir = rm_k ? (rm_k-1 ? (rm_k-2 ? 'S' : 'E') : 'N') : 'W';

	printf("%d %d %c\n",rm_i+1,rm_j+1,dir);


	return 0;
}
