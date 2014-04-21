/*
 Created By: Malvika Joshi
 Problem: fence6
 Link: http://cerberus.delos.com:791/usacoprob2?a=fShWFi0bUBr&S=fence6
*/

#include <stdio.h>
#include <string.h>
#define inf 30000

typedef struct {
	int weight;
	int ivaild,jvalid,ival,jval,in,jn;
	int I[8],J[8];
} edge;

int N,K;
edge E[101];
int Graph[200][200] = {{0}};

int D[200];
int Q[200];
int H,T;

int min(){
	int min = inf,in = H, i;

	for(i = H; i < T; i++){
		if(D[Q[i]] <= min){
			min = D[Q[i]];
			in = Q[i];
		}
	}
	return in;
}

int Dijkstra(int src, int tar){
	int i,v,temp;
	int vis[200] = {0};

	H = 0;
	T = 0;
	memset(D,inf,sizeof(int)*200);
	D[src] = 0;
	Q[T++] = src;

	while(H < T){
		v = min();
		vis[v] = 1;
		Q[v] = Q[H++];
		for(i = 0;i < K; i++){
			temp = D[v] + Graph[i][v];
			if(temp < D[i] && !vis[i]){
				D[i] = temp;
				Q[T++] = i;
			}
		}
	}

	return D[tar];
}




int find(int *A,int target, int n){
	int i;
	for(i = 0;i < n; i++){
		if(A[i] == target) return 1;
	}

	return 0;
}

int main(){
	int N,i,k,j;

	scanf("%d",&N);

	for(i = 1;i <= N; i++){
		E[i].in = 0;
		E[i].jn = 0;
		E[i].ivaild = 1;
		E[i].jvalid = 1;
		E[i].ival = -1;
		E[i].jval = -1;
	}

	for(i = 0;i < N; i++){
		scanf("%d",&k);
		scanf("%d%d%d",&E[k].weight,&E[k].in,&E[k].jn);
		for(j = 0;j < E[k].in; j++){
			scanf("%d",&E[k].I[j]);
			if(E[k].I[j] < k){
				E[k].ivaild = 0;
			}
		}
		for(j = 0;j < E[k].jn; j++){
			scanf("%d",&E[k].J[j]);
			if(E[k].J[j] < k){
				E[k].jvalid = 0;
			}
		}
	}

	k = 0;
	for(i = 1;i <= N; i++){
		if(E[i].ivaild){
			E[i].ival = k++;
		}
		if(E[i].jvalid){
			E[i].jval = k++;
		}
	}

	K = k;

	for(i = 1; i <= N; i++){
		if(E[i].ival == -1){
		for(j = 0; j < E[i].in; j++){
			if(E[i].I[j] < i){
				k = E[i].I[j];
				if(find(E[k].I,i,E[k].in)){
					E[i].ival = E[k].ival;
				}else{
					E[i].ival = E[k].jval;
				}
				break;
			}
		}
		}

		if(E[i].jval == -1){
		for(j = 0; j < E[i].jn; j++){
			if(E[i].J[j] < i){
				k = E[i].J[j];
				if(find(E[k].I,i,E[k].in)){
					E[i].jval = E[k].ival;
				}else{
					E[i].jval = E[k].jval;
				}
				break;
			}
		}
		}
	}

	for(i = 0;i < K; i++){
		for(j = 0;j < K; j++){
			Graph[i][j] = inf;
		}
	}

	for(i = 1;i <= N; i++){
		Graph[E[i].ival][E[i].jval] = E[i].weight;
		Graph[E[i].jval][E[i].ival] = E[i].weight;
	}


	int min = inf,temp;

	for(i = 1; i <= N; i++){
		Graph[E[i].ival][E[i].jval] = inf;
		Graph[E[i].jval][E[i].ival] = inf;
		temp = Dijkstra(E[i].ival,E[i].jval) + E[i].weight;
		if(temp < min) min = temp;
		Graph[E[i].ival][E[i].jval] = E[i].weight;
		Graph[E[i].jval][E[i].ival] = E[i].weight;
	}


	printf("%d\n",min);
	return 0;
}
