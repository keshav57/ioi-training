#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 1010

using namespace std;

char adj[NMAX][NMAX];
int pos[NMAX][NMAX][2];
int N,M;

void dp(){
	int i,j,k,dir,n,b;

	for(n = 1; n < N; ++n){
		for(dir = -1; dir < 2; dir+=2){
			for(i = 0; i < N; ++i){
				j = (i+(dir*n)+N)%N;
				k = (i+dir+N)%N;
				b = dir>0;

				if(j == k){
					pos[i][j][b] = adj[i][j];
					continue;
				}

				pos[i][j][b] = (adj[i][k] && pos[k][j][b]) || (adj[i][j] && pos[j][k][!b]);
			}
		}
	}
}

void print(int i, int j, int dir){
	int k;
	k = (i+dir+N)%N;

	if(j == k){
		printf("%d\n",k+1);
		return;
	}

	if(adj[i][k] && pos[k][j][dir>0]){
		printf("%d\n",k+1);
		print(k,j,dir);
		return;
	}

	assert(adj[i][j] && pos[j][k][dir<0]);
	printf("%d\n",j+1);
	print(j,k,dir*-1);
}

int main(){
	int i,j;

	scanf("%d%d",&N,&M);

	while(M--){
		scanf("%d%d",&i,&j);
		--i,--j;
		adj[i][j] = adj[j][i] = 1;
	}

	dp();

	for(i = 0; i < N; ++i){
		if(pos[i][(i+1)%N][0]) break;
	}

	if(i >= N){
		printf("-1\n");
		return 0;
	}

	printf("%d\n",i+1);
	print(i,(i+1)%N,-1);

	return 0;
}