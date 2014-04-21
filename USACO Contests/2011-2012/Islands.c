/*
 Created By: Malvika Joshi
 Problem: Islands (US Open-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=132
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100010

typedef struct { int height,id; } island;

int field[MAXN];
island drown[MAXN];
int N;

inline int max(int a, int b){ return a > b? a : b; }

int compare(const void *a,const void *b){
	const island *p1 = a;
	const island *p2 = b;
	return p1->height-p2->height;
}

int main(){
	int i,islands,maxisl,id;

	scanf("%d", &N);
	N+=2;

	for(i = 1; i < N-1; ++i){
		scanf("%d",&field[i]);
		if(i && field[i] == field[i-1]){
			--i;
			--N;
			continue;
		}
		drown[i-1].height = field[i];
		drown[i-1].id = i;
	}

	field[0] = field[N-1] = 0;

	qsort(drown,N-2,sizeof(island),compare);

	maxisl = islands = 1;
	for(i = 0; i < N-2; ++i){
		id = drown[i].id;
		if(field[id-1] > field[id] && field[id+1] > field[id]) ++islands;
		else if(field[id-1] < field[id] && field[id+1] < field[id]) --islands;
		if(i < N-3 && drown[i].height == drown[i+1].height) continue;
		maxisl = max(maxisl,islands);
	}

	printf("%d\n",maxisl);

	return 0;
}
