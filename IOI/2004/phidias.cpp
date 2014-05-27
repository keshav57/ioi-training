#include <algorithm>
#include <cassert>
#include <cstdio>

#define NMAX 610

using namespace std;

int valid[NMAX][NMAX];
int wasted[NMAX][NMAX];

int M,N;

int dp(){
	int i,j,k;

	for(i = 1; i <= M; ++i){
		for(j = 1; j <= N; ++j){
			if(valid[i][j]) continue;
			wasted[i][j] = i*j;

			for(k = 1; k+k <= i; ++k){
				wasted[i][j] = min(wasted[i][j],wasted[k][j]+wasted[i-k][j]);
			}

			for(k = 1; k+k <= j; ++k){
				wasted[i][j] = min(wasted[i][j],wasted[i][k]+wasted[i][j-k]);
			}
		}
	}

	return wasted[M][N];
}


int main(){
	int i,j,n;

	scanf("%d%d%d",&M,&N,&n);

	while(n--){
		scanf("%d%d",&i,&j);
		valid[i][j] = 1;
	}

	printf("%d\n",dp());

	return 0;
}
