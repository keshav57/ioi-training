/*
 Created By: Malvika Joshi
 Problem: Bar Code (IOITC-2013 Online Test 2)
*/

#include <stdio.h>

#define INF 2000000
inline int min(int a, int b){ return a < b? a : b; }

int cost[1010][2];
int sum[1010][2];
int T[1010][2];
int code[1010][1010];

int N,M,X,Y;

void init(){
	int i,j,c0,c1;
	sum[0][0]= 0;
	sum[0][1] = 0;
	for(i = 1; i <= M; i++){
		c0 = 0;
		c1 = 0;
		for(j = 0; j < N; j++){
			if(code[j][i]) c1++;
			else c0++;
		}
		cost[i][0] = c0;
		cost[i][1] = c1;
		sum[i][0] = sum[i-1][0] + c0;
		sum[i][1] = sum[i-1][1] + c1;
	}
}

inline int getsum(int i, int j, int c){
	return sum[j][c] - sum[i-1][c];
}

int DP(){
	int i,j;
	T[0][0] = 0;
	T[0][1] = 0;

	for(i = 1;i <=M; i++) T[i][0] = T[i][1] = INF;

	for(i = 1;i <= Y; i++){
		T[i][0] = cost[i][0] + T[i-1][0];
		T[i][1] = cost[i][1] + T[i-1][1];
	}

	for(i = 2*X; i <= X+Y; i++){
		j = (i-X)+1;
		while(j > X){
			T[i][0] = min(T[i][0],T[j-1][1] + getsum(j,i,0));
			T[i][1] = min(T[i][1],T[j-1][0] + getsum(j,i,1));
			j--;
		}
	}

	for(; i <= M; i++){
		j = i-X+1;
		T[i][0] = T[j-1][1] + getsum(j,i,0);
		T[i][1] = T[j-1][0] + getsum(j,i,1);
		j--;
		while(i-j < Y){
			T[i][0] = min(T[i][0],T[j-1][1] + getsum(j,i,0));
			T[i][1] = min(T[i][1],T[j-1][0] + getsum(j,i,1));
			j--;
		}
	}

	return min(T[M][0],T[M][1]);
}

int main(){

	int i,j;
	char c;
	scanf("%d%d%d%d",&N,&M,&X,&Y);

	if(X > M){
		printf("0");
		return 0;
	}

	for(i = 0;i < N; i++){
		getchar();
		for(j = 1;j <= M; j++){
			c = getchar();
			code[i][j] = c == '#';
		}
	}

	init();
	int sol = DP();

	printf("%d",sol >= INF ? 0 : sol);

	return 0;
}

