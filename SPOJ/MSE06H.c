/*
 Created By: Malvika Joshi
 Problem:  Japan
 Link: http://www.spoj.com/problems/MSE06H/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1010

typedef struct { int a,b; } bridge;
typedef long long lli;

bridge B[MAXN*MAXN];
int T[MAXN];
int N,M,K;

int compare(const void *a, const void *b){
	const bridge *p1 = (bridge*)a;
	const bridge *p2 = (bridge*)b;
	return p2->a-p1->a;
}

int query(int x){
	int sum = 0;

	while(x > 0){
		sum += T[x];
		x -= (x & -x);
	}

	return sum;
}

void update(int x){
	while(x < M){
		T[x]++;
		x += (x & -x);
	}
}

lli count(){

	int i,j;
	lli c = 0LL;

	memset(T,0,sizeof(int)*MAXN);
	qsort(B,K,sizeof(bridge),compare);

	j = 0;
	for(i = 0; i < K ;i++){
		c += query(B[i].b-1);
		if(i < K-1 && B[i].a == B[i+1].a) continue;
		while(j <= i) update(B[j++].b);
	}

	return c;
}

int main(){

	int i,t,n = 0;

	scanf("%d",&t);

	while(n++ < t){
		scanf("%d%d%d",&N,&M,&K);

		for(i = 0; i < K; i++) scanf("%d%d",&B[i].a,&B[i].b);

		printf("Test case %d: %lld\n",n,count());
	}

	return 0;
}
