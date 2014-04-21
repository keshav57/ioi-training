/*
 Created By: Malvika Joshi
 Problem: Bicolored Horses
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1167
*/

#include <stdio.h>

#define MAXN 510
#define INF 1000000000LL

typedef long long lli;

int col[MAXN][2];
lli U[MAXN][MAXN];
int N,K;

inline lli min(lli a, lli b){ return a < b ? a : b; }

inline lli unhappy(int i, int j){
	int b,w;
	b = col[i][1]-col[j-1][1];
	w = col[i][0]-col[j-1][0];
	return (lli)b*w;
}

void init(){
	int i;

	for(i = 1; i <= N; i++){
		col[i][0] += col[i-1][0];
		col[i][1] += col[i-1][1];
	}
}

lli DP(){
	int i,k,j;

	for(i = 1; i <= N; i++) U[i][0] = INF, U[0][i] = INF;

	for(i = 1; i <= N; ++i){
		for(k = 1; k <= K; ++k){
			U[i][k] = INF;
			if(i < k) continue;
			for(j = i; j; --j){
				U[i][k] = min(U[i][k],U[j-1][k-1]+unhappy(i,j));
			}
		}
	}

	return U[N][K];
}

int main(){
	int i,c;

	scanf("%d%d",&N,&K);

	for(i = 1; i <= N; i++){
		scanf("%d",&c);
		col[i][c] = 1;
	}

	init();
	printf("%lld\n",DP());

	return 0;
}
