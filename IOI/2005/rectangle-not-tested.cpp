#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>

#include "creclib.h"


using namespace std;

int dimension_x();
int dimension_y();
void cut(direction dir, int position);

int get_cut(int x, int y){
	int i,k;

	assert(x^y);

	if(y <= 2*x){
		return x;
	}

	for(i = 0; i < 30; ++i){
		k= (1<<i);
		if(y < k*x+k-1){
			break;
		}
	}

	assert(i);
	--i;
	k = (1<<i);

	return k*i+k-1;
}

int main(){
	int x,y,c;
	direction d;

	while(1){
		d = vertical;
		x = dimension_x();
		y = dimension_y();

		assert(x != y);

		if(x > y){
			d = horizontal;
			c = get_cut(y,x);
			cut(d,c);
			continue;
		}
		c = get_cut(x,y);
		cut(d,c);
	}

	return 0;
}
