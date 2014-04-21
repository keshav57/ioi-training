/*
 Created By: Malvika Joshi
 Problem: False Mirrors
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1152
*/

#include <stdio.h>

#define MAXN 20
#define MAXS ((1<<20)+10)
#define INF 40000

int mons[MAXN];
int damg[MAXS];
int N,S;

inline int min(int a, int b){ return a < b ? a : b; }
inline int next(int i){ return i == N-1 ? 0 : i+1; }

int DP(){
	int i,s,j,t;

	S = 1<<N;

	for(s = 1; s < S; ++s){
		damg[s] = INF;
		for(i = 0 ; i < N; i++){
			if(s & (1<<i)){
				j = next(i);
				t = s;
				t &= ~(1 << i);
				damg[s] = min(damg[s],damg[t]);
				t &= ~(1 << j);
				damg[s] = min(damg[s],damg[t]);
				t &= ~(1 << (next(j)));
				damg[s] = min(damg[s],damg[t]);
			}
		}
		for(i = 0;i < N; i++){
			if(s & (1<<i)) continue;
			damg[s] += mons[i];
		}

	}

	return damg[S-1];
}

int main(){
	int i;
	scanf("%d",&N);

	for(i= 0 ; i < N; i++){
		scanf("%d",&mons[i]);
	}

	printf("%d\n",DP());

	return 0;
}
