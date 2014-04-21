/*
 Created By: Malvika Joshi
 Problem: Twin Robots (INOI-2010)
 Link: http://www.iarcs.org.in/inoi/2010/inoi2010/inoi2010-qpaper.pdf
*/

#include <stdio.h>

int W[2500][2500];
int R_1[2500][2500];
int R_2[2500][2500];
int N;

int const nil = -10000;

typedef struct{
	int x1,y1;
	int x2,y2;
} q_i;

q_i Q[6250000];
int H = 0, T = 0;

void push(int x1,int y1, int x2,int y2){
	Q[T].x1 = x1;
	Q[T].y1 = y1;
	Q[T].x2 = x2;
	Q[T].y2 = y2;
	T++;
}

void visit(int x1,int y1,int x2,int y2){

	int temp = R_1[x1][y1]+R_2[x2][y2];

	if(x1+1 < N && y2-1 >= 0){
		if(temp + W[x1+1][y1] + W[x2][y2-1] > R_1[x1+1][y1] + R_2[x2][y2-1]){
			if(R_1[x1+1][y1] == nil && R_2[x2][y2-1] == nil){
				push(x1+1,y1,x2,y2-1);
			}
			R_1[x1+1][y1] = R_1[x1][y1] + W[x1+1][y1];
			R_2[x2][y2-1] = R_2[x2][y2] + W[x2][y2-1];
		}
	}

	if(y1+1 < N && x2+1 < N){
		if(temp + W[x1][y1+1] + W[x2+1][y2] > R_1[x1][y1+1] + R_2[x2+1][y2]){
			if(R_1[x1][y1+1] == nil && R_2[x2+1][y2] == nil){
				push(x1,y1+1,x2+1,y2);
			}
			R_1[x1][y1+1] = R_1[x1][y1] + W[x1][y1+1];
			R_2[x2+1][y2] = R_2[x2][y2] + W[x2+1][y2];
		}
	}
}

int main(){

	int i,j;
	scanf("%d",&N);

	for(i = 0;i < N;i ++){
		for(j = 0;j < N; j++){
			scanf("%d",&W[i][j]);
			R_1[i][j] = nil;
			R_2[i][j] = nil;
		}
	}

	R_1[0][0] = W[0][0];
	R_2[0][N-1] = W[0][N-1];
	push(0,0,0,N-1);

	while(H < T){
		visit(Q[H].x1,Q[H].y1,Q[H].x2,Q[H].y2);
		H++;
	}

	printf("%d\n",R_1[N-1][N-1]+R_2[N-1][0]);

	return 0;
}
