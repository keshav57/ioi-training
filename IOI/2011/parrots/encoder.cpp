#include "encoderlib.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

int part[4];

using namespace std;


void encode(int N, int M[]){
	int i,enc,b,k;

	for(i = 0; i < N; ++i){
		part[0] = M[i]&3;
		part[1] = (M[i]&15)>>2;
		part[2] = (M[i]&63)>>4;
		part[3] = M[i]>>6;

		enc = i<<3;

		for(k = 0; k < 4; ++k){
			b = (k&1)+1;
			int tmp = enc|((k>1)<<2)|part[k];
			while(b--) send(tmp);
			assert(enc >= 0 && enc <= 255);
		}
	}
}

