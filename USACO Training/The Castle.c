/*
 Created By: Malvika Joshi
 Problem: castle
 Link: http://cerberus.delos.com:791/usacoprob2?S=castle&a=YnrI700o9Fg
*/

#include <stdio.h>
#include <string.h>

typedef struct { int N,W,S,E; } wall;

wall create_config(int module){
	wall config = {0,0,0,0};

	if(module >= 8){
		config.S = 1;
		module -= 8;
	}
	if(module >= 4){
		config.E = 1;
		module -= 4;
	}
	if(module >= 2){
		config.N = 1;
		module -= 2;
	}
	if(module >= 1){
		config.W = 1;
		module -= 1;
	}
	return config;
}

wall castle[50][50];
int visited[50][50];
int M,N;

int get_rooms(int i, int j){
	if(i < 0 || j < 0 || i >= M || j >= N|| visited[i][j]) return 0;
	visited[i][j] = 1;
	int size = 1;

	if(!castle[i][j].E)	size += get_rooms(i,j+1);

	if(!castle[i][j].W)	size += get_rooms(i,j-1);

	if(!castle[i][j].S) size += get_rooms(i+1,j);

	if(!castle[i][j].N)	size += get_rooms(i-1,j);

	return size;
}

int main(){
	int i,j,module,rooms = 0,size,max_size = 0;

	memset(visited,0,sizeof(int)*50*50);

	scanf("%d%d",&N,&M);

	for(i = 0; i < M; i++){
		for(j = 0;j < N; j++){
			scanf("%d",&module);
			castle[i][j] = create_config(module);
		}
	}


	for(i = 0;i < M; i++){
		for(j = 0;j < N; j++){
			size = get_rooms(i,j);
			rooms += size ? 1 : 0;
			if(size > max_size){
				max_size = size;
			}
		}
	}

	printf("%d\n%d\n",rooms,max_size);

	int m1,m2;
	char dir;

	max_size = 0;
	for(j = 0;j < N; j++){
		for(i = M-1; i >= 0; i--){
			if(i > 0 && castle[i][j].N){
				castle[i][j].N = 0;
				castle[i-1][j].S = 0;
				memset(visited,0,sizeof(int)*50*50);
				size = get_rooms(i,j);
				if(size > max_size){ m1 = i, m2 = j, max_size = size, dir = 'N'; }
				castle[i][j].N = 1;
				castle[i-1][j].S = 1;
			}
			if(j < N-1 && castle[i][j].E){
				castle[i][j].E = 0;
				castle[i][j+1].W = 0;
				memset(visited,0,sizeof(int)*50*50);
				size = get_rooms(i,j);
				if(size > max_size){ m1 = i, m2 = j, max_size = size, dir = 'E'; }
				castle[i][j].E = 1;
				castle[i][j+1].W = 1;
			}
		}
	}


	printf("%d\n%d %d %c\n",max_size,m1+1,m2+1,dir);

	return 0;
}
