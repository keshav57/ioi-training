/*
 Created By: Malvika Joshi
 Problem: Wifi Setup (December-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=209
*/

#include <algorithm>
#include <stdio.h>

int N,A,B;
int C[2000];

inline double cost(int x ,int y){
	double r = (y-x)/(double)2;
	return A + (B*r);
}

int main(){

	int i,start;
	double endhere,temp,mincst;
	scanf("%d%d%d",&N,&A,&B);

	for(i = 0;i < N; i++){
		scanf("%d",&C[i]);
	}

	std::sort(C,C+N);

	start = C[0];
	mincst = 0;
	endhere = A;

	for(i = 0;i < N ;i++){
		temp = cost(start,C[i]);
		if(endhere+A < temp){
			start = C[i];
			mincst += endhere;
			endhere = A;
		}else {
			endhere = temp;
		}
	}

	mincst += endhere;

	if(mincst == (int) mincst){
		printf("%.0f",mincst);
	}else{
		printf("%.1f",mincst);
	}

	return 0;
}

