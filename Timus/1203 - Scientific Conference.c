/*
 Created By: Malvika Joshi
 Problem: Scientific Conference
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1203
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int s,e; } report;

int compare(const void *a, const void* b){
	const report* p1 = a;
	const report* p2 = b;
	return p1->e-p2->e;
}

report R[100000];
int N;

int main(){
	int i,n = 0, maxe = 0;

	scanf("%d",&N);
	for(i = 0;i < N; i++)	scanf("%d%d",&R[i].s, & R[i].e);

	qsort(R,N,sizeof(report),compare);

	for(i = 0;i < N; i++){
		if(R[i].s <= maxe) continue;
		maxe = R[i].e;
		++n;
	}

	printf("%d",n);

	return 0;
}
