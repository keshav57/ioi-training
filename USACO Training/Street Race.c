/*
 Created By: Malvika Joshi
 Problem: race3
 Link: http://cerberus.delos.com:791/usacoprob2?a=bXBVfu8FyVs&S=race3
*/

#include <stdio.h>
#include <string.h>

int Graph[60][60] = {{0}};

int visited[60] = {0};
int unavoid[60] = {0};
int split[60] = {0};
int N;

int dfs(int v, int u){
	int visn = 0,i;
	if(visited[v]){
		return 0;
	}

	visited[v] = 1;

	for(i = 0; i < N; i++){
		if(i == u) continue;
		if(Graph[v][i]){
			visn += dfs(i,u);
		}
	}

	return visn+1;
}

int outcheck(int v){
	int i;
	for(i = 0; i < N; i++){
		if(visited[i] && Graph[v][i]) return 0;
	}
	return 1;
}

int udfs(int v, int split){
	int visn = 0,i;
	if(visited[v]){
		return 0;
	}

	visited[v] = 1;

	for(i = 0; i < N; i++){
		if(i == split){	continue; }
		if(Graph[v][i] || Graph[i][v]){
			visn += udfs(i,split);
		}
	}

	return visn+1;
}

typedef struct { int first, second ; }pair;

pair unavoidable(){
	int s = 0,u = 0,i;

	for(i = 1;i < N-1; i++){
		memset(visited,0,sizeof(int)*60);
		if(dfs(0,i) < N-1){
			unavoid[i] = 1;
			u++;
		}
		memset(visited,0,sizeof(int)*60);
		if(udfs(0,i) < N-1 && outcheck(i)){
			split[i] = 1;
			s++;
		}
	}

	pair r = {s,u};

	return r;
}

int main(){

	int x = 0,i = 0;
	pair sol;

	scanf("%d",&x);

	while(x != -1){
		while(x != -2){
			Graph[i][x] = 1;
			scanf("%d",&x);
		}
		scanf("%d",&x);
		i++;
	}

	N = i;

	sol = unavoidable();

	printf("%d",sol.second);
	for(i = 0; i < N; i++){
		if(unavoid[i]){
			printf(" %d",i);
		}
	}
	printf("\n");

	printf("%d",sol.first);
	for(i = 0; i < N; i++){
		if(split[i]){
			printf(" %d",i);
		}
	}
	printf("\n");
	return 0;
}
