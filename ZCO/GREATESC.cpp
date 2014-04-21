/*
 Created By: Malvika Joshi
 Problem: GREATESC
 Link: http://opc.iarcs.org.in/index.php/problems/GREATESC
*/

#include <stdio.h>
#include <limits.h>

#define INF -1
int n;
int D[4000];
int Q[4000];
int A[4000][4000];

void BFS(int b){
	int H = 0;
	int T = -1;
	int j,k;
	D[b] = 0;

	Q[T+1] = b;
	T = T+1;

	while(T>=H){
		j = Q[H];

		for (k = 0;k < n; k++){
			if(A[j][k] == 1 && D[k] == INF){
				D[k] = D[j]+1;
				Q[T+1] = k;
				T = T+1;
			}
		}

		H = H+1;
	}
}

int main(){
	int m;
	scanf("%d%d",&n,&m);
	int i,j;
	int a,b,s,t;

	for(i = 0;i < n; i++){
		D[i] = INF;
	}

	for(i = 0;i < n; i++){
		for(j = 0;j < n; j++){
			A[i][j] = 0;
		}
	}

	for(i = 0;i < m; i++){
		scanf("%d%d",&a,&b);
		A[a-1][b-1] = 1;
		A[b-1][a-1] = 1;
	}


	scanf("%d%d",&s,&t);


	if(s > 0 && t > 0 && s <= n && t <= n){
		s--;
		t--;
		BFS(s);

		if(D[t] == INF){
			printf("0");
		}else {
			printf("%d",D[t]);
		}
	}else {
		printf("0");
	}


	return 0;
}

