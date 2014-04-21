/*
 Created By: Malvika Joshi
 Problem: Train Ride (INOI-2006)
 Link: http://www.iarcs.org.in/inoi/2006/inoi2006/inoi2006-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

typedef struct{
	int start;
	int end;
}t_route;

int compare(t_route a, t_route b){
	return a.start < b.start;
}

t_route A[4000];
int N,M;

int main(){

	int i,x,y,num_t;
	scanf("%d%d",&N,&M);

	for(i = 0;i < M;i ++){
		scanf("%d%d",&A[i].start,&A[i].end);
	}

	std::sort(A,A+M,compare);

	x = A[0].start;
	y = A[0].end;
	num_t = 1;
	for(i = 1;i < M; i++){
		if(x != A[i].start && y >= A[i].start){
			x = A[i].start;
			y = A[i].end;
			num_t++;
		}
	}

	printf("%d",num_t);

	return 0;
}
