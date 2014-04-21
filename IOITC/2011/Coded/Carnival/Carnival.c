/*
 Created: Malvika Joshi
 Problem: Complan Carnival (IOITC-2011 Final-1)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int cost,increase,min;} item;

item rides[110];
int H,N,M;
int F[110][2000] = {{0}};

int compare(const void* a, const void* b){
	const item *p1 = a;
	const item *p2 = b;
	return p1->min-p2->min;
}

inline int max(int a , int b){ return a > b ? a : b; }

int knapsack(){
	int i,j,k;

	F[0][0] = H;

	for(k = 0;k < N; k++){
		for(i = k;i >= 0; i--){
			for(j = M;j >= 0; j--){
				if(rides[k].min <= F[i][j]){
					F[i+1][j+rides[k].cost] = max(F[i+1][j+rides[k].cost],F[i][j]+rides[k].increase);
				}
			}
		}
	}

	for(i = N; i >= 0; i--){
		for(j = M;j >= 0; j--){
			if(F[i][j]) return i;
		}
	}

	return 0;
}

int main(int argc, char **argv){
	int i;

	scanf("%d%d%d",&N,&M,&H);

	for(i = 0;i < N; i++){
		scanf("%d%d%d",&rides[i].min,&rides[i].cost,&rides[i].increase);
	}

	qsort(rides,N,sizeof(item),compare);

	printf("%d\n",knapsack());

	return 0;
}
