#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>

#define KMAX 1010

using namespace std;

int A[KMAX];
int B[KMAX];
int D[KMAX];

/*
 3
 0 0 0
 -2 0 2
 1 1 1 
*/

int get_jumps(int a, int b, int len){
	int dist;
	dist = abs(a-b);

	if(!dist && !len) return -3;

//	if(dist < len){
//		if(!dist || len%dist) return -1;
//		return len/dist;
//	}

	if(!len || dist%len) return -1;

	return (dist/len);
}

int K;

long long get_dist(int len, int a, int b, int step, int d){
	int j;
	long long inc,tmp;
	
	assert(len <= step);

	if(a > b) swap(a,b);

	inc = 0;
	for(j = 0; j <= len; ++j){
		inc += (a + (1LL*j*d));
	}

	step -= len;

	if(step%2){
	    inc += a;
	}
	
	step /= 2;

	
	tmp = 0;
	for(j = 1; j <= step; ++j){
		tmp += (b + (1LL*j*d));
	}
	tmp *= 2;
	if(step) tmp -= (b+(step*1LL*d));
	
	return inc + tmp;
}

int len[KMAX];

int min_dist(){
	int i,jumps,tot;

	tot = -1;
	for(i = 0; i < K; ++i){

		jumps = get_jumps(A[i],B[i],D[i]);

		if(jumps == -1) return -1;

		if(jumps != -3 && tot >= 0 && tot%2 != jumps%2) return -1;
		tot = max(tot,jumps);
		len[i] = (jumps == -3) ? 0 : jumps;
	}

	tot = max(0,tot);

	return tot;
}

int main(){
	int i;

// 	cout << get_dist(2,-6,-2,4,2) << endl;
	
	scanf("%d",&K);

	for(i =0 ; i < K; ++i) scanf("%d",&A[i]);

	for(i =0 ; i < K; ++i) scanf("%d",&B[i]);

	for(i =0 ; i < K; ++i) scanf("%d",&D[i]);

	int sol = min_dist();

	printf("2\n");

	if(sol < 0){
		printf("0\n");
//		assert(0);
		return 0;
	}

	printf("1\n%d\n",sol);

	long long inc = 0;

	for(i =0 ; i < K; ++i){
		inc += get_dist(len[i],A[i],B[i],sol,D[i]);
	}

	printf("%lld\n",inc);

	return 0;
}
