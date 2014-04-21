/*
 Created By: Malvika Joshi
 Problem: agrinet
 Link: http://cerberus.delos.com:791/usacoprob2?a=wLlAc4srHta&S=agrinet
*/

#include <stdio.h>
#define infinity 10000000

int Graph[100][100];
int D[100];
int N;

int prim(){

	int vis = 1,i,v,weight = 0;

	for(i = 0;i < N; i++){
		D[i] = Graph[0][i];
	}

	D[0] = infinity;

	while(vis < N){
		v = 0;
		for(i = 0; i < N; i++){
			if(D[i] < D[v]){ v = i; }
		}

		weight += D[v];
		D[v] = infinity;

		for(i = 0;i < N; i++){
			if(D[i] != infinity && Graph[v][i] < D[i]){
				D[i] = Graph[v][i];
			}
		}

		vis++;
	}

	return weight;
}

int main(){

	int i,j,mst;

	freopen("agrinet.in","r",stdin);
	freopen("agrinet.out","w",stdout);

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			scanf("%d",&Graph[i][j]);
		}
	}

	mst = prim();

	printf("%d\n",mst);

	return 0;
}
