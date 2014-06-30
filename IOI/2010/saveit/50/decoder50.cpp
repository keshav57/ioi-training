#include "grader.h"
#include "decoder.h"

#include <iostream>

using namespace std;

void decode(int nv, int nh) {

  
	int i,k,b,dist;
	
	for(i = 0; i < nh; ++i){
		for(k = 0; k < nv; ++k){
			dist = 0;
 			for(b = 0; b < 10; ++b){
				dist |= (decode_bit()<<b);
			}
			hops(i,k,dist);
		}
	}
}
