#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 5000010

using namespace std;

long long M[NMAX];
long long minA[NMAX];
long long maxA[NMAX];

int N;

int main(){
	int i;
	long long len;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%lld",&M[i]);
		M[i] *= 2;
	}

	M[N] = (1e10);

	minA[0] = -(1e10);
	maxA[0] = M[0]/2;

	len = maxA[0]-minA[0]+1;

	for(i = 1; i <= N; ++i){
		minA[i] = M[i-1]-maxA[i-1];
		maxA[i] = min(M[i]/2,M[i-1]-minA[i-1]);
		len = min(len,maxA[i]-minA[i]+1);
	}

	len = max(len,0LL);
	printf("%lld\n",len);

	return 0;
}
