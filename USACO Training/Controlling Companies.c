/*
 Created By: Malvika Joshi
 Problem: concom
 Link: http://cerberus.delos.com:791/usacoprob2?a=BKsrStSpHTO&S=concom
 */

#include <stdio.h>
#define N 100

int Control[100][100];
int Graph[100][100];
int Q[100];
int H,T;

void bfs(int s){
	int i,k;

	H = 0;
	T = 0;
	for(i = 0; i < N; i++){
		Control[s][i] =  (Graph[s][i] > 50);
		if(Control[s][i]){
			Q[T++] = i;
		}
	}

	while(H < T){
		k = Q[H++];
		for(i = 0;i < N; i++){
			if(!Control[s][i]){
				Graph[s][i] += Graph[k][i];
				if(Graph[s][i] > 50){
					Control[s][i] = 1;
					Q[T++] = i;
				}
			}
		}
	}
}

int main(){

	int i,j,n,a,b;

	scanf("%d",&n);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			Graph[i][j] = 0;
		}
	}

	for(i = 0;i < n; i++){
		scanf("%d%d",&a,&b);
		scanf("%d",&Graph[a-1][b-1]);
	}

	for(i = 0;i < N; i++){
		bfs(i);
	}

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			if(Control[i][j] && i != j){
				printf("%d %d\n",i+1,j+1);
			}
		}
	}

	return 0;
}
