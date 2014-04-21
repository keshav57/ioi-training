/*
 Created By: Malvika Joshi
 Problem: Posh Neighbourhoods
*/

#include <stdio.h>
#include <vector>

std::vector<int> roads[100010];
int upmarket[100010] = {0};
int not_posh[100010] = {0};
int visited[100010] = {0};
int M,N,R;

void dfs(int v,int mode){
	int i,n;
	if(visited[v]) return ;

	visited[v] = 1;

	if(mode) upmarket[v] = 1;
	else not_posh[v] = 1;

	n = roads[v].size();

	for(i = 0;i < n; i++){
		dfs(roads[v][i],mode);
	}

}

int main(){
	int i,a,b;

	scanf("%d%d%d",&N,&M,&R);

	for(i = 0;i < R; i++){
		scanf("%d%d",&a,&b);
		a--;
		b--;
		roads[b].push_back(a); //reverse arcs
	}

	for(i = 0; i < M; i++){
		dfs(i,1);
	}

	for(i = 0;i < N; i++) visited[i] = 0;

	for(i = 0;i < N; i++){
		if(!upmarket[i]){
			dfs(i,0);
		}
	}

	for(i = 0;i < N; i++){
		if(!not_posh[i]) printf("%d ",i+1);
	}

	return 0;
}

