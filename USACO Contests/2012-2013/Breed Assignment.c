/*
 Created By: Malvika Joshi
 Problem: Breed Assignment (March-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=261
*/



#include <stdio.h>

#define MAXN 15
#define MAXR 50

typedef struct {
	int c1,c2,r;
} rel;

rel R[MAXR];
int count = 0;
int N,K;
int breed[MAXN];

void dfs(int cow){
	int i;

	if(cow >= N){
		for(i = 0; i < K; i++)
			if( (breed[R[i].c1] == breed[R[i].c2]) != R[i].r) return;
		++count;
		return;
	}

	for(i = 0; i < 3; i++){
		breed[cow] = i;
		dfs(cow+1);
	}
}

int main(){
	int i;
	char c;

	scanf("%d %d",&N,&K);

	for(i = 0; i < K; i++){
		scanf(" %c%d%d",&c,&R[i].c1,&R[i].c2);
		--R[i].c1,--R[i].c2;
		R[i].r = c == 'S';
	}

	dfs(0);
	printf("%d",count);

	return 0;
}
