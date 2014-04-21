/*
 Created By: Malvika Joshi
 Problem: Route Design (February-2013 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=249
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int r,l; } route;
typedef struct { int dist,weight; } dist;

int compare(const void *a, const void *b){
	const route *r1 = a;
	const route *r2 = b;

	return r1->l == r2->l ? r1->r-r2->r : r1->l-r2->l;
}

inline int max(int a, int b){ return a > b ? a : b; }

route Routes[1000000];
dist Left[40000];
dist Right[40000];
int N,L,R;

int main(){

	int i,r,l,sol = 0,temp;

	scanf("%d%d%d",&L,&R,&N);

	for(i = 0;i < L; i++){
		scanf("%d",&Left[i].weight);
		Left[i].dist = Left[i].weight;
	}

	for(i = 0;i < R; i++){
		scanf("%d",&Right[i].weight);
		Right[i].dist = Right[i].weight;
	}

	for(i = 0;i <N; i++){
		scanf("%d%d",&Routes[i].l,&Routes[i].r);
		Routes[i].l--;
		Routes[i].r--;
	}

	qsort(Routes,N,sizeof(route),compare);

	for(i = N-1; i>= 0; i--){
		l = Routes[i].l;
		r = Routes[i].r;
		temp = Left[l].dist;
		Left[l].dist = max(Left[l].dist,Right[r].dist+Left[l].weight);
		Right[r].dist = max(Right[r].dist,temp+Right[r].weight);
	}

	for(i = 0;i < L; i++){
		sol = max(sol,Left[i].dist);
	}

	for(i = 0;i < R; i++){
		sol = max(sol,Right[i].dist);
	}

	printf("%d",sol);
	return 0;
}
