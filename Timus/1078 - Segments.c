/*
 Created By: Malvika Joshi
 Problem: Segments
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1078
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int x,y,id; } seg;

int compare(const void *a, const void *b){
	const seg *p1 = (seg*)a;
	const seg *p2 = (seg*)b;
	if(p2->x == p1->x) return p2->y-p1->y;
	return p2->x-p1->x;
}

seg A[510];
int prev[510];
int seq[510];
int S,N;

int search(int target){
	if(!S) return 0;

	int mid,low,high;
	low = 0;
	high = S-1;

	while(low <=high){
		mid = low + (high-low)/2;

		if(A[seq[mid]].y < target){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}

	return low;
}

int LIS(){
	int i,p;

	for(i= 0;i < N; i++){
		p = search(A[i].y);
		seq[p] = i;
		prev[i] =  p ? seq[p-1] : -1;
		if(p == S) ++S;
	}

	return S;
}


void print(int i){
	if(i < 0) return;
	print(prev[i]);
	printf("%d ",A[i].id);
}

int main(){
	int i;
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d%d",&A[i].x,&A[i].y);
		A[i].id = i+1;
	}

	qsort(A,N,sizeof(seg),compare);

	printf("%d\n",LIS());
	print(seq[S-1]);

	return 0;
}
