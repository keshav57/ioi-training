/*
 Created By: Malvika Joshi
 Problem: The Nilgiri Tahr (INOI-2004)
 Link: http://www.iarcs.org.in/inoi/2004/inoi2004/inoi2004-qpaper.pdf
*/

#include <stdio.h>
#include <stdlib.h>

int Grid[1000][1000];
int visited[1000][1000];
int M,N;

int is_valid(int i,int j,int i_1,int j_1){
	if(i_1 >= 0 && i_1 < M && j_1 >= 0 && j_1 < N){
		if(abs(Grid[i][j]-Grid[i_1][j_1]) <= 1 && !visited[i_1][j_1]){
			return 1;
		}
	}
	return 0;
}

int backtrack(int i, int j){

	visited[i][j] = 1;

	if(i == 0 && j == 0 ){
		printf("1\n%d %d\n",i+1,j+1);
		return 1;
	}

	if(is_valid(i,j,i-1,j)){
		if(backtrack(i-1,j)){
			printf("%d %d\n",i+1,j+1);
			return 1;
		}
	}

	if(is_valid(i,j,i,j-1)){
		if(backtrack(i,j-1)){
			printf("%d %d\n",i+1,j+1);
			return 1;
		}
	}

	if(is_valid(i,j,i,j+1)){
		if(backtrack(i,j+1)){
			printf("%d %d\n",i+1,j+1);
			return 1;
		}
	}
	if(is_valid(i,j,i+1,j)){
		if(backtrack(i+1,j)){
			printf("%d %d\n",i+1,j+1);
			return 1;
		}
	}

	return 0;
}

int main(){

	int i,j;
	scanf("%d %d",&M,&N);

	for(i = 0;i < M;i ++){
		for(j = 0;j < N;j++){
			scanf("%d",&Grid[i][j]);
			visited[i][j] = 0;
		}
	}

	if(!backtrack(M-1,N-1)){
		printf("0");
	}

	return 0;
}
