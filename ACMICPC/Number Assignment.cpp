/*
 Problem: Number Assignment (Regionals 2013 : Asia-Jakarta)
 Link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4445
*/

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

#define NMAX 110

using namespace std;

typedef long long lli;

int A[NMAX];
int diff[NMAX];
int N,K,T;

int main(){
	int i,t;
	lli rem;

	scanf("%d",&T);

	for(t = 1; t <= T; ++t){
		scanf("%d%d",&N,&K);

		for(i = 0; i < N; ++i){
			scanf("%d",&A[i]);
		}

		sort(A,A+N);

		rem = A[N-1]-A[0];

		for(i = 1; i < N; ++i){
			diff[i-1] = A[i]-A[i-1];
		}

		sort(diff,diff+N-1);

		while(--K){
			rem -= diff[N-K-1];
		}

		printf("Case #%d: %lld\n",t,rem);
	}

	return 0;
}
