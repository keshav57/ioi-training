/*
 Created By: Malvika Joshi
 Problem: Vongon Zoo (INOI-2010)
 Link: http://www.iarcs.org.in/inoi/2010/inoi2010/inoi2010-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

int N;
int K;
int A[1000000];

int compare(int a,int b){
	return a < b;
}

int main(){

	int i,cur,max_s;

	scanf("%d%d",&N,&K);

	for(i = 0;i < N;i ++){
		scanf("%d",&A[i]);
	}

	std::sort(A,A+N,compare);

	cur = A[0];
	max_s = 1;

	for(i = 1;i < N; i++){
		if(A[i] - cur >= K){
			max_s++;
			cur = A[i];
		}
	}

	printf("%d",max_s);

	return 0;
}
