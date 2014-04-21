/*
 Created By: Malvika Joshi
 Problem: Meeting Point, Again! (IOITC-2013 Final 3)

 As the metric used is Manhattan distance, we can compute the number of meeting points in each dimension separately.
 If there are even number of points, there will be m1-m2+1 meeting points in each dimension where m1,m2 are the two
 median points (All the integer coordinates on the line formed by m1,m2 can be the meeting point). Otherwise if the
 number of points is odd there will be only one median (in each dimension) which will be the only meeting point.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXK 3
#define MOD ((long long)(1e9+7))

typedef long long lli;

int compare(const void *a, const void *b){
    const long long *p1 = a, *p2 = b;
    if(*p1 < *p2) return -1;      //We are sorting long long, so we can't simply return the difference of the two elements.
    return *p1 > *p2;
}

lli C[MAXK][MAXN+10];	//Coordinates of the points stored dimension by dimension
int N,K;

int main(){

	int i,k,mid;
	lli mpts,tmp;

	scanf("%d%d",&N,&K);

	if(N%2){
		printf("1");	//There is only one meeting point if there are odd number of points.
		exit(0);
	}

	for(i = 0; i < N; i++){
		for(k = 0; k < K; k++) scanf("%lld",&C[k][i]);
	}

	mid = N/2;	//The index of the second median
	mpts = 1;	//The number of meeting points.

	for(k = 0; k < K; k++){
		qsort(C[k],N,sizeof(lli),compare);	//We sort each dimension to find the medians.

		tmp = C[k][mid] - C[k][mid-1] +1;	//The number of points on the median line.
		tmp %= MOD;		//To avoid overflow as they can be as large as 2 * 10^18.
		mpts *= tmp;
		mpts %= MOD;	//We are ensuring that mpts and tmp are less than MOD, and so it fits in a long long.
	}

	printf("%lli",mpts);

	return 0;
}
