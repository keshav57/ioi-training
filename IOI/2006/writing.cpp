#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 3000010
#define MMAX 3010
#define CH 55

using namespace std;

int str[NMAX];

int occ[CH];
int exp[CH];

int N,M;

int compute(){
	int i,k,match,ct;

	k = 0;
	match = M;
	ct = 0;
	for(i = 0; i < N; ++i){
		--match;
		++occ[str[i]];

		while(occ[str[i]] > exp[str[i]]){
			++match;
			--occ[str[k]];
			++k;
		}

		assert(match >= 0 && match <= M);
		ct += !match;
	}

	return ct;
}

int main(){
	int i,v;
	char c;

	scanf("%d%d",&M,&N);
	assert(N < NMAX);

	for(i = 0; i < M; ++i){
		scanf(" %c",&c);
		v = c > 'Z' ? 26+c-'a' : c-'A';
		++exp[v];
	}

	for(i =0 ; i < N; ++i){
		scanf(" %c",&c);
		v = c > 'Z' ? 26+c-'a' : c-'A';
		str[i] = v;
	}

	printf("%d\n",compute());

	return 0;
}
