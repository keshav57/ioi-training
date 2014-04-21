/*
 Created By: Malvika Joshi
 Problem: Perimeter (February-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=243
*/

#include <stdio.h>

#define red -1
#define white 0
#define black 1
#define N 102

int Farm[102][102];
int M,perimeter = 0;

void flood_fill(int i, int j){
	if(Farm[i][j] == black){
		return;
	}

	if(Farm[i][j] == red){
		perimeter++;
		return;
	}

	Farm[i][j] = black;

	if(i > 0){
		flood_fill(i-1,j);
	}
	if(j > 0){
		flood_fill(i,j-1);
	}
	if(i+1 < N){
		flood_fill(i+1,j);
	}
	if(j+1 < N){
		flood_fill(i,j+1);
	}

}

int main(){

	int i,j,a,b;

	scanf("%d",&M);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			Farm[i][j] = white;
		}
	}

	for(i = 0;i < M; i++){
		scanf("%d%d",&a,&b);
		Farm[a][b] = red;
	}

	flood_fill(0,0);

	printf("%d\n",perimeter);

	return 0;
}
