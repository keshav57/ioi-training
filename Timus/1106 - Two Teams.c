/*
 Created By: Malvika Joshi
 Problem: Two Teams
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1106
*/

#include <stdio.h>

int Graph[110][110] ={{0}};
int group[110] = {0};
int visited[110] = {0};
int N;

void dfs(int v){
	visited[v] = 1;

	int i;
	for(i = 0; i < N; i++){
		if(Graph[v][i] && !visited[i]){
			group[i] = !group[v];
			dfs(i);
		}
	}
}

int main(){
	scanf("%d",&N);
	int i,k;

	for(i = 0;i < N; i++){
		scanf("%d",&k);
		k--;
		while(k != -1){
			Graph[i][k] = 1;
			scanf("%d",&k);
			k--;
		}
	}

	for(i = 0;i < N; i++){
		if(!visited[i]){
			dfs(i);
		}
	}

	int c = 0;

	for(i = 0;i < N; i++){
		if(group[i]) c++;
		if(!visited[i]) {
			printf("0");
			return 0;
		}
	}

	printf("%d\n",c);
	for(i = 0;i < N; i++){
		if(group[i]) printf("%d ",i+1);
	}
	return 0;
}

