/*
 Created By: Malvika Joshi
 Problem: The Middleman (INOI-2007)
 Link: http://www.iarcs.org.in/inoi/2007/inoi2007/inoi2007-qpaper.pdf
*/

#include <stdio.h>
#include <limits.h>

#define NFS -40000001
int Matrix[201][201];
int M,N;

inline int min(int a, int b){return a < b ? a : b;}

int get_sum(int x1,int y1, int x2, int y2){
	return Matrix[x2][y2] - Matrix[x2][y1-1] - Matrix[x1-1][y2] + Matrix[x1-1][y1-1];
}

void init_matrix(){
	int i, j;

	for(i = 0;i <= M; i++){
		Matrix[i][0] = 0;
	}
	for(j = 1;j < N; j++){
		Matrix[0][j] = 0;
	}

	for(i = 1;i <= M;i ++){
		for(j = 1;j <= N;j++){
			Matrix[i][j] = Matrix[i][j] + Matrix[i-1][j] + Matrix[i][j-1] - Matrix[i-1][j-1];
		}
	}
}

int main(){

	int i,j,max_s,sum,limit,k;
	max_s = NFS;
	scanf("%d%d",&M,&N);

	for(i = 1;i <= M; i++){
		for(j = 1;j <= N;j ++){
			scanf("%d",&Matrix[i][j]);
			if(Matrix[i][j] == 0){
				Matrix[i][j] = NFS;
			}
		}
	}

	init_matrix();

	for(i = 1;i <= M; i++){
		for(j = 1;j <= N;j ++){
			limit = min(M-i,N-j);
			for(k = 0;k <= limit;k ++){
				sum = get_sum(i,j,i+k,j+k);
				if(sum > max_s){
					max_s = sum;
				}
			}
		}
	}

	printf("%d",max_s);

	return 0;
}
