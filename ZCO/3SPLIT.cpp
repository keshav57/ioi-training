/*
 Created By: Malvika Joshi
 Problem: 3SPLIT
 Link: http://opc.iarcs.org.in/index.php/problems/3SPLIT
*/

#include <stdio.h>

short int A[3000][3000];
short int Desc[3000][3000];
int V[3000];
short int Visited[3000];
int N,W;

void dfs(int s){

	int i,j;
	Visited[s] = 1;

	for(i = N-1; i >= 0; i--){
		if(A[i][s] && !Visited[i]){
			Desc[i][s] = 1;
			for(j = 0;j < N; j++){
				if(Desc[s][j]){
					Desc[i][j] = 1;
					V[j] = V[j] + V[i];
				}
			}
		V[s] = V[s] + V[i];
		dfs(i);
		}
	}

}

int best(){
	int bestv = 90000000,i,j,spliti,splitj,split,splitk;

	for(i = 0;i < N; i++){
		for(j = i+1;j < N; j++){
			split = 0;
			splitj = V[j];
			spliti = V[i];
			if(Desc[i][j]){
				splitj -= V[i];
			}
			if(Desc[j][i]){
				spliti -= V[j];
			}

			splitk = W-spliti-splitj;
			split = spliti > split ? spliti : split;
			split = splitj > split ? splitj : split;
			split = splitk > split ? splitk : split;
			bestv = bestv > split ? split : bestv;
		}
	}

	return bestv;
}

int main(){

	int i,j,a,b;
	scanf("%d",&N);
	for(i = 0;i < N;i ++){
		for(j = 0;j < N;j++){
			A[i][j] = 0;
			Desc[i][j] = 0;
		}
	}

	for(i = 0;i < N;i ++){
		Visited[i] = 0;
	}

	W = 0;

	for(i = 0;i < N; i++){
		scanf("%d",&V[i]);
		W += V[i];
	}

	for(i = 0;i < N-1;i ++){
		scanf("%d%d",&a,&b);
		a--;
		b--;
		A[a][b] = 1;
		A[b][a] = 1;
	}

	dfs(0);

	printf("%d",best());

	return 0;
}
