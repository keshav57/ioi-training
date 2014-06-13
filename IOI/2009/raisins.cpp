#include <algorithm>
#include <cassert>
#include <cstdio>

#define NMAX 52

using namespace std;

typedef long long lli;

lli pref[NMAX][NMAX];
lli min_cost[NMAX][NMAX][NMAX][NMAX];
int raisins[NMAX][NMAX];
int N,M;

inline lli sum(int i, int j, int k, int l){
	return pref[k][l] -(i ? pref[i-1][l] : 0) -(j ? pref[k][j-1] : 0) + (i && j ? pref[i-1][j-1] : 0);
}

lli dp(){
	int i,j,k,l,m,n,cut;

	for(m = 0; m < M; ++m){
		for(n = 0; n < N; ++n){
			if(!m && !n) continue;
			for(i = 0,k = m; k < M; ++i, ++k){
				for(j = 0, l = n; l < N; ++j, ++l){
					min_cost[i][j][k][l] = (1e17);

					for(cut = i; cut < k; ++cut){
						min_cost[i][j][k][l] = min(min_cost[i][j][k][l],\
								min_cost[i][j][cut][l]+min_cost[cut+1][j][k][l]);
					}

					for(cut = j; cut < l; ++cut){
						min_cost[i][j][k][l] = min(min_cost[i][j][k][l],\
								min_cost[i][j][k][cut]+min_cost[i][cut+1][k][l]);
					}

					min_cost[i][j][k][l] += sum(i,j,k,l);
				}
			}
		}
	}

	return min_cost[0][0][M-1][N-1];
}

void init(){
	int i,j;

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			pref[i][j] = raisins[i][j] + (i ? pref[i-1][j] : 0) + (j ? pref[i][j-1] : 0) - (i && j ? pref[i-1][j-1] : 0);
		}
	}
}

int main(){
	int i,j;

	scanf("%d%d",&M,&N);

	for(i =0 ; i < M; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&raisins[i][j]);
		}
	}

	init();
	printf("%lld\n",dp());

	return 0;
}