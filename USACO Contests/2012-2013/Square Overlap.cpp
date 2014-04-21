/*
 Created By: Malvika Joshi
 Problem: Square Overlap (January-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=227
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

typedef struct { int x, y; } square;

square A[50000];
int N,K;

int compare(square a, square b){ return a.x < b.x; }

int main(){
	int i,j,x,y,found = 0;
	scanf("%d %d",&N,&K);

	for(i = 0;i < N; i++){
		scanf("%d%d",&A[i].x,&A[i].y);
	}

	std::sort(A,A+N,compare);

	for(i = 0;i < N; i++){
		for(j = i+1; (A[j].x - A[i].x) < K && j < N; j++){
			if(abs(A[j].y-A[i].y) < K){
				if(found){
					printf("-1");
					return 0;
				}
				found = 1;
				x = A[j].x- A[i].x;
				y = abs(A[j].y-A[i].y);
			}
		}
	}

	if(!found){
		printf("0");
		return 0;
	}


	x -= K;
	y -= K;

	printf("%d",abs(x*y));

	return 0;
}
