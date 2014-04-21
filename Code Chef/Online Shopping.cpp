/*
 Created By: Malvika Joshi
 Problem: COUPON
 Link: http://www.codechef.com/problems/COUPON
*/

#include <cstdio>
#include <algorithm>

#define INF 1000000000000

using namespace std;
typedef long long lli;

int N,M,T;

lli DP(){

	int i,s,j;
	lli mprev,mcur;

	scanf("%d%d",&N,&M);

	int *cost = new int[N*M];
	int *dis = new int[N*M];
	lli *bcst = new lli[M];

	for(i = 0; i < N; i++){
		s = i*M+M;
		for(j = i*M; j < s; ++j){
			scanf("%d",&cost[j]);
		}
	}

	for(i = 0; i < N; i++){
		s = i*M+M;
		for(j = i*M; j < s; ++j){
			scanf("%d",&dis[j]);
		}
	}

	mprev = INF;

	for(j = 0; j < M; j++){
		bcst[j] = (lli)cost[j];
		mprev = min(mprev,bcst[j]);
	}

	lli c1,c2;

	for(i = 1; i < N; i++){
		s = i*M;
		mcur = INF;
		for(j = 0; j < M; ++j){
			c1 = mprev + (lli)cost[s+j];
			c2 = bcst[j] + (lli)max(0,cost[s+j]-dis[s-M+j]);
			bcst[j] = min(c1,c2);
			mcur = min(mcur,bcst[j]);
		}
		mprev = mcur;
	}

	delete [] cost;
	delete [] dis;
	delete [] bcst;

	return mprev;
}

int main(){

	int t;
	scanf("%d",&t);

	while(t--){
		printf("%lld\n",DP());
	}

	return 0;
}
