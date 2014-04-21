/*
 Created By: Malvika Joshi
 Problem: Sum Thing
*/

#include <stdio.h>
#include <math.h>

#define INF 100

int plus[60][100010];
int dig[60];
int K, N;

inline int min(int a, int b){ return  a < b ? a : b; }

int DP(){

	int i, num, j,k;

	for(k = 1;k <= K; k++){
		plus[0][k] = INF;
	}
	plus[0][0] = 0;

	for(i = 1;i <= N; i++){
		for(k = 0; k <= K; k++){
			if(k < dig[i]){
				plus[i][k] = INF;
				continue;
			}

			num = dig[i];
			plus[i][k] = plus[i-1][k-dig[i]]+1;

			for(j = i-1; j > 0; j--){
				num += dig[j] * pow(10,i-j);
				if(num > k) break;
				plus[i][k] = min(plus[i][k],plus[j-1][k-num]+1);
			}
		}
	}

	return plus[N][K]-1;
}

int main(){
	int i;
	char c;
	scanf("%d\n",&N);
	for(i = 1; i <= N; i++){
		c = getchar();
		dig[i] = c- '0';
	}

	scanf("%d",&K);
	int sol;

	sol = DP();

	if(sol >= INF) printf("-1");
	else printf("%d",sol);

	return 0;
}
