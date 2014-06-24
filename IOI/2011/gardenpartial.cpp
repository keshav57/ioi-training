#include <algorithm>
#include <iostream>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

int pos[110][2][1010];

int best[1010][2];
int n[1010];
int N,M,P,K;

int main(){
	int i,v,u,q,k,b;

	memset(best,-1,sizeof(best));

	scanf("%d%d%d",&N,&M,&P);

	while(M--){
		scanf("%d%d",&u,&v);
		if(n[u] < 2) best[u][n[u]++] = v;
		if(n[v] < 2) best[v][n[v]++] = u;
	}

	scanf("%d",&q);
	scanf("%d",&K);

	pos[0][0][P] = pos[0][1][P] = 1;

	for(k = 1; k <= K; ++k){
		for(b = 0; b < 2; ++b){
			for(i= 0; i < N; ++i){
				u = best[i][b] < 0 ? best[i][0] : best[i][b];
				pos[k][b][i] = pos[k-1][(i==best[u][0])][u];
			}
		}
	}

	printf("%d\n",accumulate(pos[K][0],pos[K][0]+N,0));

	return 0;
}
