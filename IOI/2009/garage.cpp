#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define MMAX 2010
#define NMAX 110

using namespace std;

int rate[NMAX];
int weight[MMAX];

int Q[MMAX];
int H,T;

int occ[NMAX];
int pl[MMAX];

int N,M;

int main(){
	int i,tot,k;

	tot = 0;
	scanf("%d%d",&N,&M);

	for(i = 0; i < N; ++i){
		scanf("%d",&rate[i]);
	}

	for(i = 0; i < M; ++i){
		scanf("%d",&weight[i]);
	}

	M*=2;
	tot = 0;

	while(M--){

		while(H < T){
			for(i = 0; i < N; ++i){
				if(!occ[i]) break;
			}
			if(i >= N) break;
			k = Q[H++];
			occ[i] = 1;
			pl[k] = i;
			tot += weight[k]*rate[i];
		}

		scanf("%d",&k);
		if(k >= 0) Q[T++] = --k;
		else{
			k*=-1;
			occ[pl[--k]] = 0;
		}
	}

	printf("%d\n",tot);

	return 0;
}
