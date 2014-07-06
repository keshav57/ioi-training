#include <algorithm>
#include <iostream>
#include "station.h"

using namespace std;


#define NMAX 500010

int stops[NMAX];
int N;

int findMinDays(int n, int k, int lodge[]){
	int i,days,nxt,prev;

	for(i = 0; i < n; ++i){
		if(!lodge[i]) continue;
		stops[N++] = i;
	}

	nxt = k;
	days = 1,prev = -1;
	for(i = 0; i < N; ++i){
		if(stops[i] <= nxt){
			prev = stops[i];
			continue;
		}
		if(prev < 0 || stops[i]-prev > k) return -1;
		++days;
		nxt = prev+k;
		prev = stops[i];
	}

	return days;
}
