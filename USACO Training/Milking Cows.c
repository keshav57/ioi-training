/*
 Created By: Malvika Joshi
 Problem: milk2
 Link: http://cerberus.delos.com:791/usacoprob2?a=aeYx2THXhQ4&S=milk2
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int first,second; } pair;

pair A[5001];
int N;

inline int max(int a, int b){ return a > b ? a : b; }

int compare(const void* a, const void* b){
	const pair *p1 = a;
	const pair *p2 = b;
	return p1->first-p2->first;
}

pair longest_interval(void){
	int i,start,end;
	pair max_i;

	max_i.first = 0;
	max_i.second = 0;
	start = 0;
	end = 0;

	for(i = 0;i < N; i++){
		if(A[i].first <= end){
			end = max(end,A[i].second);
		}else{
			if(end != 0) max_i.second = max(max_i.second,A[i].first-end);
			start = A[i].first;
			end = A[i].second;
		}
		max_i.first = max(max_i.first,end-start);
	}

	return max_i;
}

int main(void){

	int i;
	pair sol;

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d%d",&A[i].first,&A[i].second);
	}

	qsort(A,N,sizeof(pair),compare);

	sol = longest_interval();

	printf("%d %d\n",sol.first,sol.second);

	return 0;
}

