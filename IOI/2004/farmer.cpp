#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cassert>

#define QMAX 150010
#define NMAX 2010

using namespace std;


int dp[QMAX][2];

int cyc[NMAX];
int path[NMAX];
int N,K,Q;

int compute(){
	int i,b,q;

	dp[0][0] = 1;
	dp[cyc[0]][0] = 1;

	for(i = 1; i < N; ++i){
		b = i&1;
		for(q = 0; q <= Q; ++q){
			dp[q][b] = dp[q][!b];
			if(cyc[i] <= q) dp[q][b] |= dp[q-cyc[i]][!b];
		}
	}

	b = (N-1)&1;
	return dp[Q][b];
}

int main(){
	int sum,i,tot;

	scanf("%d%d%d",&Q,&N,&K);

	sum = 0;
	for(i = 0; i < N; ++i){
		scanf("%d",&cyc[i]);
		sum += cyc[i];
	}

	for(i = 0; i < K; ++i){
		scanf("%d",&path[i]);
	}

	sort(path,path+K);

	if(sum >= Q){
		if(compute()){
			printf("%d\n",Q);
		}else{
			printf("%d\n",Q-1);
		}
		return 0;
	}

	tot = 0;
	Q -= sum;

	for(i = K-1; i >= 0; --i){
		if(path[i] >= Q){
			tot += Q-1;
			break;
		}
		Q -= path[i];
		tot += path[i]-1;
	}

	printf("%d\n",sum+tot);

	return 0;
}
