/*
 Created By: Malvika Joshi
 Problem: NUMFACT
 Link: http://www.codechef.com/problems/NUMFACT
*/

#include <stdio.h>
#include <string.h>

#define MAXL 1000000
#define MAXP 80000
#define MAXN 10

bool fac[MAXL];
int primes[MAXP];
short count[MAXP];
int P,N;

int init(){

	int i,j;

	for(i = 2; i*i < MAXL; i++){
		if(fac[i]) continue;
		for(j = i*i; j < MAXL; j += i) fac[j] = 1;
		primes[P++] = i;
	}

	for(; i < MAXL; i++){
		if(fac[i]) continue;
		primes[P++] = i;
	}

	return P;
}

int main(){

	int i,t,n,p;
	long long sol;

	init();

	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);
		memset(count, 0, sizeof(short)*MAXP);

		for(i = 0; i < N; i++){
			scanf("%d",&n);
			for(p = 0; p < P; ++p){
				while(!(n%primes[p])){
					++count[p];
					n /= primes[p];
				}
			}
		}

		sol = 1;
		for(p = 0; p < P; ++p) sol *= (count[p]+1);
		printf("%lld\n",sol);
	}


	return 0;
}
