/*
 Created By: Malvika Joshi
 Problem: Width (IOITC-2010 Final-3)
*/
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 1010

using namespace std;

struct label{ int l[3]; };

char seq[NMAX];

int adj[NMAX][NMAX];
int graph[NMAX][NMAX];

int stack[NMAX];
int S,N;

int check_2(){
	int i;

	for(i = 0; i < N; ++i){
		if(seq[i]^'(') continue;
		if(seq[i+1]^')'){
			return 0;
		}
	}

	printf("%d\n",N);

	for(i =0 ; i < N-1; ++i){
		printf("%d %d\n",i+1,i+2);
	}

	for(i = 0; i < N; ++i){
		printf("2 %d %d\n",i+1,i+2);
	}

	return 1;
}

void init(){
	int i,j,k;

	for(i = 0 ; i < N; ++i){
		if(seq[i]^')'){
			stack[S++] = i;
			continue;
		}

		while(seq[stack[S-1]] != '('){
			k = stack[--S];
			adj[k][i] = 1;
			adj[i][k] = 1;
		}

		k = stack[S-1];
		adj[k][i] = 1;
		adj[i][k] = 1;
		graph[i][k] = graph[k][i] = 1;
		seq[k] = '#';
		stack[S++] = i;
	}

	i = N-1;
	for(j = 0; j < S-1; ++j){
		k = stack[j];
		adj[k][i] = 1;
		adj[i][k] = 1;
	}

}

label nodes[NMAX];
int M;
int adj2[2*NMAX][2*NMAX];

void create_node(){
	int i,j,k;

	for(i = 0; i < N-1; ++i){
		adj[i][i+1] = adj[i+1][i] = 1;
		graph[i][i+1] = graph[i+1][i] = 1;
	}

	for(i = 0; i < N; ++i){
		for(j = i+1; j < N; ++j){
			if(!adj[i][j]) continue;
			for(k = j+1; k < N; ++k){
				if(!adj[j][k] || !adj[i][k]) continue;
				nodes[M].l[0] = i;
				nodes[M].l[1] = j;
				nodes[M++].l[2] = k;
			}
		}
	}
	assert(M<2*N);
}


int common(label a, label b){
	int i,m,j;
	m = 0;
	for(i  =0; i < 3; ++i){
		for(j = 0; j < 3; ++j){
			m += a.l[i] == b.l[j];
		}
	}

	return m;
}

void add_edges(){
	int i,j,n;

	n = 0;
	for(i = 0; i < M; ++i){
		for(j = i+1; j < M; ++j){
			if(common(nodes[i],nodes[j]) < 2) continue;
			adj2[i][j] = adj2[j][i] = 1;
			++n;
		}
	}

	assert(n == M-1);
}

int visited[2*NMAX];

void dfs(int v, int p){
	int i;
	assert(!visited[v]);
	visited[v] = 1;
	for(i = 0; i < M; ++i){
		if(i == p) continue;
		if(adj2[i][v]) dfs(i,v);
	}
}

inline int occurs(label l, int i){
	int k;
	for(k = 0; k < 3; ++k){
		if(l.l[k] == i) return 1;
	}
	return 0;
}

void check_edges(){
	int i,j,k;

	for(i = 0; i < N; ++i){
		for(j = i+1; j < N; ++j){
			if(!graph[i][j]) continue;
			for(k = 0; k < M; ++k){
				if(occurs(nodes[k],i) && occurs(nodes[k],j)) break;
			}
			assert(k < M);
		}
	}
}

int del[NMAX];

void check_conn(int v){
	visited[v] = 1;
	int i;

	for(int t = 0;t < 3; ++t){
		assert(!(del[nodes[v].l[t]]));
	}

	for(i = 0; i < M; ++i){
		if(!adj2[v][i] || visited[i]) continue;
		for(int t = 0; t < 3; ++t){
			if(!occurs(nodes[i],nodes[v].l[t])){
				del[nodes[v].l[t]] = 1;
			}
		}
		check_conn(i);
		for(int t = 0;t < 3; ++t){
			del[nodes[v].l[t]] = 0;
		}
	}

}

int main(){

	scanf("%d",&N);
	scanf("%s",seq);

	if(check_2()) return 0;

	init();
	create_node();
	add_edges();

	//check ans
	dfs(0,-1);
	check_edges();
	memset(visited,0,sizeof(int)*NMAX*2);
	check_conn(0);

	int i,j;

	printf("%d\n",M);
	for(i = 0; i <  M ;++i){
		for(j = i+1; j < M; ++j){
			if(adj2[i][j]) printf("%d %d\n",i+1,j+1);
		}
	}

	for(i = 0; i < M; ++i){
		printf("3");
		for(j = 0; j < 3; ++j){
			printf(" %d",nodes[i].l[j]+1);
		}
		printf("\n");
	}

	return 0;
}
