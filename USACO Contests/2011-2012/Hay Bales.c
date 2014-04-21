/*
 Created By: Malvika Joshi
 Problem: Hay Bales (December-2011 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=94
*/

#include <stdio.h>

#define MAX_N 10010

int piles[MAX_N];
int N;

inline int max(int a, int b){ return a > b ? a : b ; }

int main(){

	int i,total,avg,mov;

	scanf("%d",&N);

	total = 0;
	for(i = 0; i < N; ++i){
		scanf("%d",&piles[i]);
		total += piles[i];
	}

	avg = total/N;

	mov = 0;
	for(i = 0; i < N; ++i)	mov += max(0,piles[i]-avg);


	printf("%d\n",mov);

	return 0;
}
