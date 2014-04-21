/*
 Created By: Malvika Joshi
 Problem: NUMROUTE
 Link: http://opc.iarcs.org.in/index.php/problems/NUMROUTE
*/

#include <stdio.h>

#define M 42373

int N;
long long int K;
int Matrix[150][150];
int R[150][150];

void mmul(long long int E){
	int i,j,h;
	long long int k;
	if(E == 1){
		for(i = 0;i < N ;i ++){
			for(j = 0;j < N ;j++){
				R[i][j] = Matrix[i][j];
			}
		}
		return;
	}

	int T[150][150] = {{0}};
	int A[150][150];

	for(i = 0;i < N; i++){
		for(j = 0;j < N ;j++)
		A[i][j] = Matrix[i][j];
	}

	for(k = 1; k*2 <= E;k *= 2){
		for(h = 0; h < N; h++){
			for(i = 0; i < N; i++){
				for(j= 0; j< N; j++){
					T[h][i] = T[h][i] + (A[h][j] * A[j][i]);
					T[h][i] = T[h][i]%M;
				}
			}
		}

		for(i = 0;i < N; i++){
			for(j = 0;j < N; j++){
				A[i][j] = T[i][j];
				T[i][j] = 0;
			}
		}
	}

	if(k < E){
	mmul(E-k);

	for(h = 0; h < N; h++){
		for(i = 0; i < N; i++){
			for(j= 0; j< N; j++){
				T[h][i] = T[h][i] + (A[h][j] * R[j][i]);
				T[h][i] = T[h][i] % M;
			}
		}
	}

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			A[i][j] = T[i][j];
			T[i][j] = 0;
		}
	}
	}

	for(i = 0;i < N ;i ++){
		for(j = 0;j < N; j++){
			R[i][j] = A[i][j];
		}
	}
}


int main(){

	int i,j;
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		for(j = 0;j < N;j ++){
			scanf("%d",&Matrix[i][j]);
		}
	}

	int s,d;
	scanf("%d%d%lld",&s,&d,&K);
	s--;
	d--;


	/*Test case 9 is wrong on the oj*/

	mmul(K);

	printf("%d",R[s][d]);

	return 0;
}
