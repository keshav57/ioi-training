#include <cassert>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "assistant.h"

#define NMAX 100010

using namespace std;

int stack[NMAX];
int cur[NMAX];
int S;

void Assist(unsigned char *A, int N, int K, int R) {
	int i,k;

	assert(R == N+K);

	for(i = 0; i < K; ++i){
		cur[i] = 1;
		if(!A[i]) continue;
		stack[S++] = i;
	}

	for(i = 0; i < N; ++i){
		k = GetRequest();
		if(cur[k]){
			if(A[K+i]) stack[S++] = k;
			continue;
		}
		assert(S);
		PutBack(stack[--S]);
		cur[stack[S]] = 0;
		cur[k] = 1;
		if(!A[K+i]) continue;
		stack[S++] = k;
	}

}


/*

4 2 65000
2 0 3 0
*/
