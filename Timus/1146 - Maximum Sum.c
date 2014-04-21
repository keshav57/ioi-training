/*
 Created By: Malvika Joshi
 Problem: Maximum Sum
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1146
*/

#include <stdio.h>

int sum[100][100];

int N;

void init(){
	int i,j;
	for(i = 1; i < N; i++){
		sum[0][i] += sum[0][i-1];
		sum[i][0] += sum[i-1][0];
	}

	for(i = 1;i < N; i++){
		for(j = 1; j < N; j++){
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	return;
}

int max_rect(){
	int i,j,k,l,temp,max = sum[0][0];

	for(k = 0;k < N; k++){
		for(l = 0;l < N; l++){
			for(i = k; i < N; i++){
				for(j = 0; j <= l; j++){
					temp = sum[i][l];
					if(k > 0 && j > 0){
						temp += sum[k-1][j-1];
					}
					if(k > 0){
						temp -= sum[k-1][l];
					}
					if(j > 0){
						temp -= sum[i][j-1];
					}

					if(temp > max) max = temp;
				}
			}
		}
	}

	return max;
}

int main(){
	int i,j;
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			scanf("%d",&sum[i][j]);
		}
	}

	init();

	printf("%d",max_rect());

	return 0;
}
