/*
 Created By: Malvika Joshi
 Problem: CHXORR
 Link: http://www.codechef.com/problems/CHXORR
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 2010

int compare(const void *a, const void *b){ return *(int*)a-*(int*)b; }
inline int max(int a, int b){ return a > b ? a : b; }

int A[MAXN];
int N;

int bin(int tar,int st){
	int high,low,mid,i,s,e;


	s = st;
	e = N-1;
	for(i = 30; i >= 0 ; i--){

		low = s;
		high = e;
		if(!(A[high]&(1<<i))) continue;

		while(low < high){
			mid = low + (high-low)/2;
			if(A[mid]&(1<<i)){
				high = mid;
			}else{
				low = mid+1;
			}
		}

		if(!(A[low]&(1<<i))) continue;

		if(tar&(1<<i)){
			e = low-1;
		}else{
			s = low;
		}

	}

	return A[low]^tar;
}

int main(){

	int i,j,mx,xr,t;

	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);

		for(i = 0; i < N; i++) scanf("%d",&A[i]);

		qsort(A,N,sizeof(int),compare);

		mx = 0;
		for(i = 0; i < N-2; i++){
			for(j = i+1; j < N-1; j ++){
				xr = A[i]^A[j];
				mx= max(mx,bin(xr,j+1));
			}
		}


		printf("%d\n",mx);
	}


	return 0;
}

