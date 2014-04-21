/*
 Created By: Malvika Joshi
 Problem: Empty Stalls (November-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=346
*/

#include <algorithm>
#include <iostream>
#include <deque>
#include <cstdio>
#include <cassert>

#define NMAX 3000010

using namespace std;

deque<int> empty;
int pref[NMAX];
int N;

int main(){
	int i,x,y,a,b,k;

	scanf("%d%d",&N,&k);

	for(i =0 ; i < N; ++i) empty.push_back(i);

	while(k--){
		scanf("%d%d%d%d",&x,&y,&a,&b);

		for(i = 1; i <= y; ++i){
			pref[((1LL*a*i)+b)%N] += x;
		}
	}

	for(i = 0; i < N; ++i){
		if(!pref[i]) continue;
		assert((int)empty.size() >= pref[i]);

		while(empty.front() < i){
			x = empty.front();
			empty.pop_front();
			empty.push_back(x+N);
		}

		while(pref[i]--){
			empty.pop_front();
		}
	}

	k = N;

	for(i = 0; i < (int)empty.size(); ++i){
		k = min(k,empty[i]%N);
	}

	printf("%d\n",k);

	return 0;
}
