#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>

#define NMAX 310
#define INF (1e7)
#define PMAX 32

using namespace std;

typedef long long lli;

int pos[NMAX];
int N,P;

lli dist[NMAX][NMAX];
lli dp[PMAX][NMAX];
int next[32][NMAX];

void init(){
	int i,j,k;

	for(i = 0; i < N; ++i){
		for(j = i+1; j <= N; ++j){
			dist[i][j] = 0;
			for(k = i; k < j; ++k) dist[i][j] += min(pos[k]-pos[i],pos[j]-pos[k]);
		}
	}
}

void compute(){
	int i,j,p,tmp;

	for(p = 0; p <= P; ++p){
		for(i = 0; i < N; ++i){
			next[p][i] = -1;
			dp[p][i] = dist[i][N];

			if(!p) continue;

			for(j = i+1; j < N; ++j){
				tmp = dp[p-1][j]+dist[i][j];
				if(tmp < dp[p][i]){
					dp[p][i] = tmp;
					next[p][i] = j;
				}
			}
		}
	}
}

int main(){
	int i,cur;

	scanf("%d%d",&N,&P);

	pos[0] = -INF;
	++N;
	for(i = 1; i < N; ++i){
		scanf("%d",&pos[i]);
	}
	pos[N] = INF;

	init();
	compute();

	assert(dp[P][0] >= 0);
	printf("%d %d %lld\n",N-1,P,dp[P][0]);

	for(i = 1; i < N; ++i) printf("%d ",pos[i]);

//	cur = next[P][0];
//
//	while(P--){
//		printf("%d ",pos[cur]);
//		cur = next[P][cur];
//	}
//
	printf("\n");

	return 0;
}
