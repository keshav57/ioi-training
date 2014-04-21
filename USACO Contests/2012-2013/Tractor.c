/*
 Created By: Malvika Joshi
 Problem: Tractor (February-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=245
*/

#include <stdio.h>
#include <stdlib.h>


int F[500][500];
int visited[500][500];
int N;

int flood_fill(int limit,int i,int j){
	if(visited[i][j]){
		return 0;
	}

	int total = 1;

	visited[i][j] = 1;

	if(i > 0 && abs(F[i][j]-F[i-1][j]) <= limit){
		total += flood_fill(limit,i-1,j);
	}

	if(j > 0 && abs(F[i][j]-F[i][j-1]) <= limit){
		total += flood_fill(limit,i,j-1);
	}

	if(i+1 < N && abs(F[i][j]-F[i+1][j]) <= limit){
		total += flood_fill(limit,i+1,j);
	}

	if(j+1 < N && abs(F[i][j]-F[i][j+1]) <= limit){
		total += flood_fill(limit,i,j+1);
	}

	return total;
}

void init(void){
	int i,j;
	for(i = 0;i < N; i++){
		for(j = 0; j < N; j++){
			visited[i][j] = 0;
		}
	}
	return;
}

int isvalid(int target,int limit){

	int i,j,temp;
	init();

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			temp = flood_fill(limit,i,j);
			if(temp >= target){
				return 1;
			}
		}
	}

	return 0;
}

int bin_search(int target){
	int low,high,mid,val;
	low = 0;
	high = 1000000;

	while(low <= high){
		mid = (high+low)/2;
		init();
		val = isvalid(target,mid);
		if(!val){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}

	return low;
}

int main(){

	int i,j,K;
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			scanf("%d",&F[i][j]);
		}
	}

	K = bin_search((N*N+1)/2);

	printf("%d",K);

	return 0;
}
