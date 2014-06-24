#include "decoderlib.h"
#include <cassert>
#include <iostream>

using namespace std;


int occ[260];
int at_pos[32][4];

void decode(int N, int L, int X[]){
	int i,k,dec,b,same;

	assert(N <= 32);
	for(i = 0; i < L; ++i) ++occ[X[i]];

	for(i = 0; i < L; ++i){
		if(!occ[X[i]]) continue;
		same = 0;
		if(occ[X[i]] > 2){
			occ[X[i]] = 1;
			same = 1;
		}

		k = X[i]>>2;
		assert(k < 2*N);
		at_pos[k>>1][((k&1)<<1)+occ[X[i]]-1] = X[i]&3;
		occ[X[i]] = same ? 2 : 0;
	}

	for(i = 0; i < N; ++i){
		dec = 0;
		for(b = 3; b >= 0; --b){
			dec <<= 2;
			dec |= at_pos[i][b];
		}
		output(dec);
	}
}
