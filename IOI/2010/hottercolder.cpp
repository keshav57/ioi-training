#include <algorithm>
#include "grader.h"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;


int ct;

int HC(int n){
	int low,high,mid,g,prev,use;

	ct = 0;
	low = 1;
	high = n;
	use = 0;
	prev = -1;

	while(low < high){
		mid = low + (high-low)/2;

		if(!use){
			prev = rand()%2 ? low : high;
			use = 1;
			Guess(prev);
		}

		g = Guess(prev^low^high);
		g *= (prev == low ? 1 : -1);
		prev = prev^low^high;
		++ct;

		if(!g){
			assert(mid-low == high-mid);
			return mid;
		}

		if(g > 0){
			low = mid+1;
			use = prev == high;
		}else{
			high = (low+high+1)/2-1;
			use = prev == low;
		}
	}

	return low;
}
