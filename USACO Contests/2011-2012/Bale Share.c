/*
 Created By: Malvika Joshi
 Problem: Bale Share (January-2012 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=107
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 21
#define MAX_S 2010

int F[MAX_S][MAX_S];
int P[MAX_S][MAX_S];
int s[MAX_N];
int w[MAX_N];
int N,S;

inline int max(int a, int b){ return a > b ? a : b; }
inline int min(int a, int b){ return a < b ? a : b; }

int init(){
	int i,j,k,b3,b1,b2;

	P[0][0] = 1;
	for(k = 1; k <= N; ++k){
		for(i = 0; i <= S; ++i){
			for(j = 0; j <= i; ++j){
				b3 = s[k]-i-j;

				if(j < b3){
					F[i][j] = 0;
					continue;
				}

				b1 = max(j,i-w[k]);
				b2 = max(min(i-w[k],j),b3);

				F[i][j] |= P[b1][b2];

				if(w[k] <= j)F[i][j] |= P[i][max(j-w[k],b3)];
			}
		}

		for(i = 0; i <= S; ++i)
			for(j = 0; j <= i; ++j)	P[i][j]= F[i][j];

	}

	for(i = 0; i <= S; ++i){
		for(j = 0; j <= i; ++j){
			 if(F[i][j]) return i;
		}
	}

	return -1;
}

int main(){
	int i;
	scanf("%d",&N);

	for(i = 1; i <= N; i++){
		scanf("%d",&w[i]);
		s[i] = w[i] + s[i-1];
	}
	S = s[N];

	i = init();
	printf("%d\n",i);

	return 0;
}
