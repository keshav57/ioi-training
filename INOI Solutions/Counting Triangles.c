/*
 Created By: Malvika Joshi
 Problem: Counting Triangles (INOI-2011)
 Link: http://www.iarcs.org.in/inoi/2011/inoi2011/inoi2011-qpaper.pdf
*/

#include <stdio.h>

int X[100000] = {0};
int Y[100000] = {0};
int N;

typedef struct{
	int x;
	int y;
}point;

point P[3000];

int main(){

	int i,a,b,tri = 0;

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d%d",&P[i].x,&P[i].y);
		X[P[i].x] ++;
		Y[P[i].y] ++;
	}

	for(i = 0;i < N; i++){
		a = X[P[i].x]-1;
		b = Y[P[i].y]-1;
		tri = (tri + (a*b))%1000;
	}

	printf("%d",tri);

	return 0;
}
