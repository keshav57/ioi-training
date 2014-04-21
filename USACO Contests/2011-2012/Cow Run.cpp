/*
 Created By: Malvika Joshi
 Problem: Cow Run (January-2012 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=110
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

int N,M,K;
int cards[8][20];

char evaluate(int fj, int bessie){


	int i,sel;
	int R;

	R = 0;
	for(i = 0; i < N; ++i){
		sel = fj&(1<<i) ? 4 : 0;
		sel += bessie&(1<<i) ? 2 : 0;
		R += ((1LL*R*cards[sel][i])%M);
		if(R >= M) R -= M;
		R += cards[sel+1][i];
		if(R >= M) R -= M;
	}

	return R <= K || M-R <= K;
}


char dfs(int fj, int bessie, int i){

	int m,n;

	if(i >= N){
		return evaluate(fj,bessie);
	}

	//srand(1<<i);
	m = rand()&1;
	n = rand()&1;

	if(dfs(fj|(n<<i),bessie|(m<<i),i+1) && (dfs(fj|(n<<i),bessie|((m^1)<<i),i+1))){
		return 1;
	}

	if(dfs(fj|((n^1)<<i),bessie|(m<<i),i+1) && (dfs(fj|((n^1)<<i),bessie|((m^1)<<i),i+1))){
		return 1;
	}

	return 0;
}

int main(){
	int i,bessie,fj,k,known;
	char c;

	scanf("%d%d%d",&N,&M,&K);

	bessie = 0;
	for(i = 0; i < N; ++i){
		scanf(" %c",&c);
		bessie |= ((c == 'B')<<i);
	}

	for(i = 0; i < N; ++i){
		for(k = 0; k < 8; ++k){
			scanf("%d",&cards[k][i]);
		}
	}

	fj = 0;

	for(i = 0; i < N; ++i){
		known = bessie&((1<<i)-1);

	//	srand(known);
		k = rand()&1;

		if(dfs(fj|(1<<i),known|(k<<i),i+1) && dfs(fj|(1<<i),known|((k^1)<<i),i+1)){
			fj |= (1<<i);
			printf("B");
		}else{
			printf("T");
		}
	}

	printf("\n");

	return 0;
}
