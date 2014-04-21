/*
 Created By: Malvika Joshi
 Problem: Sense of Beauty
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1501
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int red,black,top;
} state;

state DP[1010][1010];
int P1[1010];
int P2[1010];
int N;

int get_order(){

	int i,j,p,q;

	DP[0][0].red = 0;
	DP[0][0].black = 0;
	DP[0][0].top = -1;

	for(i = 0;i <= N; i++){
		for(j = 0; j <= N; j++){
			if(!i && !j) continue;

			//remove from j
			if(j && DP[i][j-1].top){
				p = DP[i][j-1].red;
				q = DP[i][j-1].black;

				P2[j] ? ++p : ++q;
				if(abs(p-q) <= 1){
					DP[i][j].red = p;
					DP[i][j].black = q;
					DP[i][j].top = 2;
					continue;
				}
			}

			if(i && DP[i-1][j].top){
				p = DP[i-1][j].red;
				q = DP[i-1][j].black;

				P1[i] ? ++p : ++q;
				if(abs(p-q) <= 1){
					DP[i][j].red = p;
					DP[i][j].black = q;
					DP[i][j].top = 1;
					continue;
				}
			}

			DP[i][j].top = 0;
		}
	}

	return DP[N][N].top;
}

void print(int i, int j){
	if(DP[i][j].top == -1) return;

	if(DP[i][j].top == 1){
		print(i-1,j);
		printf("1");
	}else{
		print(i,j-1);
		printf("2");
	}
}

int main(){
	int i;
	char c;
	scanf("%d\n",&N);

	for(i = 1; i <= N; i++){
		scanf("%c",&c);
		P1[i] = c-'0';
	}

	scanf("\n");

	for(i = 1; i <= N; i++){
		scanf("%c",&c);
		P2[i] = c-'0';
	}

	if(get_order()){
		print(N,N);
	}else{
		printf("Impossible");
	}

	return 0;
}
