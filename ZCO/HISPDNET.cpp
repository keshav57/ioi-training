/*
 Created By: Mavlika Joshi
 Problem: HISPDNET
 Link: http://opc.iarcs.org.in/index.php/problems/HISPDNET
*/

#include <stdio.h>
#define inf 200000;
int N;
int P[2000];
int R[2000];
int Graph[2000][2000];
int weight = 0;

void prim(){

	int us = 0;
	int i,v;
	us++;

	for(i = 0;i < N;i++){
		P[i] = Graph[0][i];
		R[i] = 0;
	}

	P[0] = -1;

	while(us < N){

		v = 0;
		for(i = 0;i < N;i ++){
			if((P[v] > P[i] || P[v] == -1) && P[i] != -1){
				v = i;
			}
		}

		weight = weight+P[v];
		P[v] = -1;

		for(i = 0;i < N;i++){
			if(Graph[v][i] < P[i]){
				P[i]  = Graph[v][i];
				R[i] = v;
			}
		}
		us++;
	}
}

int main(){

	int j,b,a,i;

	scanf("%d",&N);

	for(a = 0;a < N;a++){
		for(b = 0;b < N;b++){
			Graph[a][b] = inf;
		}
	}

	for(j = 0;j < N ;j++){
		scanf("%d",&a);
	}

	N--;

	for(i = 0;i < N;i ++){
		scanf("%d",&a);
		for(j = 0;j < N ;j++){
			scanf("%d",&Graph[i][j]);
			if(Graph[i][j] == 0) Graph[i][j] = inf;
		}
	}

	prim();

	printf("%d",weight);

	return 0;
}
