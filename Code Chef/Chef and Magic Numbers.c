/*
 Created By: Malvika Joshi
 Problem: CHMAGIC
 Link: http://www.codechef.com/problems/CHMAGIC
 */

#include <stdio.h>

#define MAXN 300000
#define MOD 1000000007
#define MAXQ 410

typedef long long lli;

int sq_sum[MAXN+5];
int magic[MAXN+5];
int B[MAXN+5];
int A[MAXN+5];
int N,Q,M;

void init(){
	int i,j,dg;
	lli tnum;
	int tsum;

	if(Q >= MAXQ){
		for(i = 1; i <= N; i++){
			B[i] = A[i] + B[i-1];
			B[i] %= MOD;
		}
		return;
	}

	for(i = 0, j = 1; i <= MAXN; i++){
		for(dg = 0; dg < 10 && j <= MAXN; ++dg){
			if(!dg && !magic[i]) continue;

			tnum = (magic[i]*10LL) + dg;
			tnum %= MOD;
			tsum = sq_sum[i] + dg * dg;

			if(tsum > Q) break;
			magic[j] = (int)tnum;
			sq_sum[j++] = tsum;
		}
	}

	for(i = 1; i <= N; i++){
		B[i] = B[i-1] + magic[A[i]];
		B[i] %= MOD;
	}
}

int main(){
	int i,l,r;

	scanf("%d%d",&Q,&N);
	for(i = 1; i <= N; i++) scanf("%d",&A[i]);
	init();

	scanf("%d",&M);

	int diff;

	while(M--){
		scanf("%d%d",&l,&r);
		diff = B[r]-B[l-1];
		if(diff < 0) diff += MOD;
		printf("%d\n",diff);
	}

	return 0;
}
