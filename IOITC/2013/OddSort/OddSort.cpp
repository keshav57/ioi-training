/*
 Created By: Malvika Joshi
 Problem: An Odd Sort (IOITC-2013 Online Test-3)
*/

#include <algorithm>
#include <cstdio>

#define MAXN 5010

using namespace std;

int A[MAXN];
int N;
int mis[MAXN];

int dp(){
	int i,k,maxs;

	maxs = 0;

	for(i = 0; i < N; ++i){
		mis[i] = A[i];
		for(k = i-1; k >= 0; --k){
			if(A[k] > A[i]) continue;
			mis[i] = max(mis[i],mis[k]+A[i]);
		}
		maxs = max(maxs,mis[i]);
	}

	return maxs;
}

int main(){
	int i,sum;

	scanf("%d",&N);

	sum = 0;
	for(i = 0; i < N; ++i){
		scanf("%d",&A[i]);
		sum += A[i];
	}

	printf("%d\n",sum-dp());

	return 0;
}
