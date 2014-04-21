/*
 Created By: Malvika Joshi
 Problem: holstein
 Link: http://cerberus.delos.com:791/usacoprob2?S=holstein&a=YnrI700o9Fg
*/

#include <stdio.h>
#include <stdlib.h>

int F[15][25];
int sol_stack[15];
int V,G,S = 0;

inline int is_empty(int A[25]){
	int i;
	for(i = 0; i < V; i++){
		if(A[i]){ return 0; }
	}
	return 1;
}

int dfs(int feed,int req[25],int limit){
	if(!limit) return is_empty(req);
	if(feed >= G) return 0;

	int i,j;
	int rem[15][25];

	for(i = feed; i < G; i++){
		for(j = 0;j < V; j++){
			rem[i][j] = req[j] <= F[i][j] ? 0 : req[j] - F[i][j];
		}
		if(dfs(i+1,rem[i],limit-1)){
			sol_stack[S++] = i;
			return 1;
		}
	}

	return 0;
}

int main(){

	int i,j;
	int req[25];

	scanf("%d",&V);

	for(i = 0;i < V; i++) scanf("%d",&req[i]);

	scanf("%d",&G);

	for(i = 0;i < G; i++){
		for(j = 0;j < V; j++){
			scanf("%d",&F[i][j]);
		}
	}


	for(j = 1;j <= G; j++){
		if(dfs(0,req,j)){
			printf("%d",S);
			for(i = S-1;i >= 0; i--){
				printf(" %d",sol_stack[i]+1);
			}
			printf("\n");
			break;
		}
	}

	exit(0);
}
