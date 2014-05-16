#include <algorithm>
#include <iostream>
#include <cassert>
#include "device.h"

#define NMAX 1510

using namespace std;

int GetN(void);
int Med3(int x, int y, int z);
void Answer(int m);

int order[NMAX];
int N,P;

int search(int i){
	int high,low,mid1,mid2,n,m;

	low =0;
	high = P;

	while(low < high){
		n = high-low+1;
		n/=3;
		mid1 = low+n;
		mid2 = mid1+n;

		if(mid1 == mid2){
			if(mid2 < P-1) ++mid2;
			assert(mid1);
			--mid1;
		}

		m = Med3(order[mid1],order[mid2],i);

		if(m == i){
			low = mid1+1;
			high = mid2-1;
		}else if(m == mid1){
			high = mid1-1;
		}else{
			low = mid2+1;
		}
	}

	return low;
}

void insert(int k, int pos){
	int i;

	for(i = P; i > pos; --i){
		order[i] = order[i-1];
	}
	order[i] = k;
}

int main(){
	int i;

	N = GetN();

	order[0] = 1;
	order[1] = 2;
	for(i = 3; i <= N; ++i){
		insert(i,search(i));
	}

	Answer(order[N/2]);

	return 0;
}
