/*
 Created By: Malvika Joshi
 Problem: fence
 Link: http://cerberus.delos.com:791/usacoprob2?S=fence&a=u2Ju9QSk0I3
*/

#include <stdio.h>

#define N 500

int Graph[500][500];
int deg[500] = {0};
int E;
int circuit[250000];
int C = 0;

void find_circuit(int v){
	int i;
	for(i = 0;i < N; i++){
		if(!Graph[v][i]) continue;
		Graph[v][i]--;
		Graph[i][v]--;
		find_circuit(i);
	}
	circuit[C++] = v;
}

int main(){
	int i,j,k;

	scanf("%d",&E);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			Graph[i][j] = 0;
		}
	}

	for(k = 0;k < E; k++){
		scanf("%d%d",&i,&j);
		Graph[--i][--j]++;
		Graph[j][i]++;
		deg[i]++;
		deg[j]++;
	}

	for(k = 0;k < 500; k++){
		if(deg[k]%2){
			break;
		}
	}

	if(k >= 500) k =0;
	find_circuit(k);

	for(k = C-1;k >= 0; k--){
		printf("%d\n",circuit[k]+1);
	}

	return 0;
}
