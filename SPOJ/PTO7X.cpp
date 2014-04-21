/*
 Created By: Malvika Joshi
 Problem: Vertex Cover
 Link: http://www.spoj.com/problems/PT07X/
*/

#include <stdio.h>
#include <vector>

inline int min(int a, int b){return a < b ? a : b;  }

typedef struct { int sel, nsel; } cover;

std::vector<int> adjacent[100010];
int visited[100010] = {0};
int N;
cover empty = {0,0};

cover dfs(int v){

	if(visited[v]) return empty;

	visited[v] = 1;

	int i,n;
	cover ccov,rcov = {1,0};

	n = adjacent[v].size();

	for(i = 0;i < n; i++){
		ccov = dfs(adjacent[v][i]);
		rcov.sel += min(ccov.sel,ccov.nsel);
		rcov.nsel += ccov.sel;
	}

	return rcov;
}

int main(){

	int i,a,b;
	scanf("%d",&N);

	for(i =0 ;i < N-1; i++){
		scanf("%d%d",&a,&b);
		--a;
		--b;
		adjacent[a].push_back(b);
		adjacent[b].push_back(a);
	}

	cover sol = dfs(0);

	printf("%d\n",min(sol.sel,sol.nsel));
	return 0;
}
