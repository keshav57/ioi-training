/*
 Created By: Malvika Joshi
 Problem: Luxury River Cruise (US Open-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=284
*/

#include <stdio.h>

#define MAXM 510
#define MAXN 1010

int adj[MAXN][2];

int visited[MAXN];
int last[MAXN];

int ends[MAXN];
int ins[MAXM];

int N,M,K;

int leads(int s){
	int i,k;
	k = s;
	for(i = 0; i < M; i++) k = adj[k][ins[i]];
	return k;
}

int cycle(){

	int k,i,ex,cyl;

	i = k = 0;

	while(!visited[i]){
		visited[i] = 1;
		last[i] = k;
		ends[k] = i;
		i = leads(i);
		++k;
	}

	if(K < k) return ends[K];

	ex = last[i];
	cyl = k-last[i];

	K -= ex;
	K %= cyl;

	return ends[last[i]+K];
}

int main(){
	int i;
	char c;

	scanf("%d%d%d",&N,&M,&K);

	for(i = 0; i < N; i++){
		scanf("%d%d",&adj[i][0],&adj[i][1]);
		--adj[i][0],--adj[i][1];
	}

	for(i = 0; i < M; i++){
		scanf(" %c",&c);
		ins[i] = c == 'R';
	}

	printf("%d\n",cycle()+1);

	return 0;
}
