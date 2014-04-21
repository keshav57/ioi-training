/*
 Created By: Malvika Joshi
 Problem: Frog Jumping (INOI-2005)
 Link: http://www.iarcs.org.in/inoi/2005/inoi2005/inoi2005-qpaper.pdf
*/

#include <stdio.h>

typedef struct {int r, d;}launcher;
typedef struct {int l, u, w;}info;

int M,N;
launcher chessboard[250][250];
info weights[250][250];

inline int min(int a, int b){
	return a < b ? a : b;
}

void getweight(int i,int j){
	int top_p = weights[i-1][j].u,left_p = weights[i][j-1].l;

	if(chessboard[i][left_p].r < j-left_p){
		left_p = j-1;
	}
	if(chessboard[top_p][j].d < i-top_p){
		top_p = i-1;
	}

	weights[i][j].l = left_p;
	weights[i][j].u = top_p;
	weights[i][j].w = min(weights[i][left_p].w,weights[top_p][j].w) +1;
}

int main(){
	int i,j,temp;
	scanf("%d%d",&M,&N);

	for(i = 0;i <  M;i ++){
		for(j = 0;j < N;j ++){
			scanf("%d",&chessboard[i][j].r);
		}
	}
	for(i = 0;i <  M;i ++){
		for(j = 0;j < N;j ++){
			scanf("%d",&chessboard[i][j].d);
		}
	}

	weights[0][0].l = 0;
	weights[0][0].u = 0;
	weights[0][0].w = 0;

	for(i = 1;i < M; i++){
		temp = weights[i-1][0].u;
		if(chessboard[temp][0].d < i-temp){
			temp = i-1;
		}
		weights[i][0].l = 0;
		weights[i][0].u = temp;
		weights[i][0].w = weights[temp][0].w + 1;
	}


	for(j = 1;j < N; j++){
		temp = weights[0][j-1].l;
		if(chessboard[0][temp].r < j-temp){
			temp = j-1;
		}
		weights[0][j].u = 0;
		weights[0][j].l = temp;
		weights[0][j].w = weights[0][temp].w + 1;
	}

	for(i = 1;i < M;i ++){
		for(j = 1;j < N; j++){
			getweight(i,j);
		}
	}

	printf("%d",weights[M-1][N-1].w);
	return 0;
}
