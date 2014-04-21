/*
 Created By: Malvika Joshi
 Problem: fence8
 Link: http://cerberus.delos.com:791/usacoprob2?a=fShWFi0bUBr&S=fence8
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int boards[50];
int rails[2000];
int sum[50];
int N,R,maxwaste = 0,min;

int dfs(int rail,int waste,int index){
	int i,temp,twaste;

	if(rail < 0){
		return 1;
	}

	if(waste > maxwaste){
		return 0;
		printf("returned");
	}

	int tmin,k = 0;

	if(rail && index  && rails[rail] == rails[rail-1]){
		k = index+1;
		if(k >= N) k = 0;
	}

	for(i = k; i < N; i++){
		if(i && sum[i] == sum[i-1]) continue;
		if(sum[i] >= rails[rail]){
			temp = sum[i];
			tmin = min;
			sum[i] -= rails[rail];
			twaste = 0;
			if(sum[i] < rails[min]){
				twaste = sum[i];
				sum[i] = 0;
			}else if(sum[i] == rails[min]){
				min++;
			}
			if(dfs(rail-1,waste+twaste,i)){
				return 1;
			}
			sum[i] = temp;
			min = tmin;
		}
	}

	return 0;
}

int greedy(int rail){
	int i,j,flag;
	for(i = rail; i>= 0; --i){
		flag = 0;
		for(j = 0;j < N; j++){
			if(sum[j] >= rails[i]){
				sum[j] -= rails[i];
				flag = 1;
				break;
			}
		}
		if(!flag) return 0;
	}
	return 1;
}

int compare(const void* a, const void *b){
	return *(int*)a - *(int*)b;
}

int main(){
	int i,j;

	scanf("%d",&N);
	for(i = 0;i < N; i++){
		scanf("%d",&boards[i]);
		maxwaste += boards[i];
	}

	scanf("%d",&R);
	for(i = 0; i < R ;i++) scanf("%d",&rails[i]);

	qsort(rails,R,sizeof(int),compare);
	qsort(boards,N,sizeof(int),compare);


	int flag = 1;

	for(i = 0; i < R; i++){
		maxwaste -= rails[i];
		for(j = 0;j < N; j++){
			sum[j] = boards[j];
		}
		if(flag && !greedy(i)){
			flag = 0;
			for(j = 0;j < N; j++){
				sum[j] = boards[j];
			}
		}
		min = 0;

		if(!flag && !dfs(i,0,0)){
			break;
		}
	}

	printf("%d\n",i);

	return 0;
}
