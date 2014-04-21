/*
 Created By: Malvika Joshi
 Problem: Umbrellas for Cows (December-2011 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=99
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 5010
#define MAXM 100010
#define INF 5000000010

typedef long long lli;

inline lli min(lli a,lli b){ return a < b ? a : b; }

int compare(const void *a, const void *b){ return *(int*)a - *(int*)b; }

int U[MAXM];
lli C[MAXN];
int pos[MAXN];
int N,M;

lli init(){

	int i,k;

	C[0] = 0;

	for(i = 1; i <= N; ++i){
		C[i] = INF;
		for(k = i; k > 0; --k){
			C[i] = min(C[i],C[k-1]+U[pos[i]-pos[k]+1]);
		}
	}

	return C[N];
}

int main(){

	int i;

	scanf("%d%d",&N,&M);

	for(i = 1; i <= N; i++)	scanf("%d",&pos[i]);

	qsort(pos,N+1,sizeof(int),compare);

	for(i = 1; i <= M; i++)	scanf("%d",&U[i]);

	for(i = M-1; i > 0; --i) U[i] = min(U[i],U[i+1]);

	printf("%lld\n",init());

	return 0;
}
