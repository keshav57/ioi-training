/*
 Created By: Malvika Joshi
 Problem: NUMTRIPLE
 Link: http://opc.iarcs.org.in/index.php/problems/NUMTRIPLE
*/

#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
int N = 2000;
int Dist[2000];
int Q[2000];
int Graph[2000][2000];
int Visited[2000];

int H = 0;
int T = -1;


int min(){
	int i,min = Q[H];
	for(i = H+1;i <= T;i++){
		if(Dist[Q[i]] <= Dist[min]){
			min = Q[i];
		}
	}
	return min;
}


void Dijkstra(int b){
	int j,k,i;

	Dist[b] = 0;

	for(i = 0;i < N;i ++){
		Q[T+1] = i;
		T++;
	}

	while(T>=H){
		j = min();
		Visited[j] = 1;
		Q[j] = Q[H];
		H = H+1;
		for (k = 0;k < N; k++){
			if(Graph[j][k] != -1 && !Visited[k] && Dist[k] > Graph[j][k] + Dist[j]){
				Dist[k] = Dist[j]+Graph[j][k];
				Q[T+1] = k;
				T = T+1;
			}
		}
	}
}

int main(){

	int src,target,m;
	int a,w,b,i,j;

	for(i = 0;i < N;i ++){
		for(j = 0;j < N;j++){
			Graph[i][j] = -1;
		}
	}

	for(i = 0; i< N; i++){
		Dist[i] = INF;
	}

	scanf("%d%d%d",&m,&src,&target);

	for(i = 0;i < m; i++){
		scanf("%d%d%d",&a,&w,&b);
		a--;
		b--;
		if(Graph[a][b] == -1 || Graph[a][b] > w){
			Graph[a][b] = w;
			Graph[b][a] = w;
		}
	}

	Dijkstra(src-1);


	if(Dist[target-1] == INF){
		printf("NO");
	}else {
		printf("YES\n%d",Dist[target-1]);
	}

	return 0;
}
