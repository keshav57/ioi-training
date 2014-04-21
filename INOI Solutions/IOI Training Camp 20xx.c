/*
 Created By: Malvika Joshi
 Problem: IOI Training Camp 20xx (INOI-2011)
 Link: http://www.iarcs.org.in/inoi/2011/inoi2011/inoi2011-qpaper.pdf
*/

#include <stdio.h>

int A[10000];
int N,K;
int d,max_d,max_e_here;

const int nil = -20000;

int gmin(int x,int y){
	int i,min = nil;
	for(i = x;i <= y;i ++){
		if(A[i] <= max_d && A[i] > min){
			min = A[i];
		}
	}
	return min;
}

void sum(int x,int y){
	if(A[y] < max_d && K > 0){
		if(d < K){
			d++;
		}
		if(d == K){
			max_e_here = max_e_here + max_d;
			max_d = gmin(x,y);
		}
	}
	else{
		max_e_here = max_e_here+A[y];
	}
}

int main(){

	int i,max_so_far,s;
	scanf("%d%d",&N,&K);

	for(i = 0;i < N ; i++){
		scanf("%d",&A[i]);
	}

	max_e_here = 0;
	d = 0;
	max_d = 0;
	max_so_far = 0;
	s = 0;

	for(i = 0;i < N ;i++){
		sum(s,i);
		if(max_e_here < A[i]){
			d = 0;
			max_d = 0;
			max_e_here = 0;
			s = i;
			sum(s,i);
		}
		if(max_e_here > max_so_far){
			max_so_far = max_e_here;
		}
	}

	printf("%d",max_so_far);
	return 0;
}
