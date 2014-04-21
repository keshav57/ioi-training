/*
 Created By: Malvika Joshi
 Problem: Haybale Restacking (March-2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=128
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>


#define NMAX 100010

using namespace std;

long long A[NMAX];
int N;

int main(){
	int i,b,a;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&a,&b);
		A[i] = b-a;
	}

	for(i = 1; i < N; ++i){
		A[i] += A[i-1];
	}

	sort(A,A+N);

	int dec = A[(N-1)/2];
	long long tot;

	tot = 0;

	for(i = 0; i < N; ++i) tot += llabs(A[i]-dec);

	printf("%lld\n",tot);

	return 0;
}
