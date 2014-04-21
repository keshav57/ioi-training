/*
 Created By: Malvika Joshi
 Problem: Concurrently Balanced Strings (November-2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=194
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <cassert>
#include <iostream>
#include <numeric>
#include <cstring>

#define NMAX 50010
#define KMAX 11

using namespace std;


char str[KMAX][NMAX];

int match[KMAX][NMAX];
int con_match[NMAX];
long long cbs[NMAX];

int stack[NMAX];
int S;

int pointers[KMAX];

int N,K;

void init(){
	int i,k,sm,fst,gr,b;

	memset(match,-1,sizeof(int)*KMAX*NMAX);

	for(k = 0 ; k < K; ++k){
		S = 0;
		for(i = 0; i < N; ++i){

			if(str[k][i] == '('){
				stack[S++] = i;
				continue;
			}

			if(!S) continue;
			match[k][stack[--S]] = i;
		}
	}

	memset(con_match,-1,sizeof(int)*NMAX);

	sm = 0;
	fst = 0;
	gr = -1;

	while(sm < N){

		b = -1;

		for(k = 0; k < K; ++k){
			if(pointers[k] > sm) continue;
			if(match[k][pointers[k]] < 0) b = ++pointers[k];
			else pointers[k] = match[k][pointers[k]]+1;
		}

		if(b >= 0){
			sm = fst+1;
			++fst;
			for(k = 0; k < K; ++k){
				pointers[k] = fst;
			}
			continue;
		}

		sm = N;
		gr= -1;
		for(k = 0; k < K; ++k){
			sm = min(sm,pointers[k]);
			gr = max(gr,pointers[k]);
		}

		if(sm == gr){
			con_match[fst] = sm-1;
			++fst;
			for(k = 0; k < K; ++k) pointers[k] = fst;
			sm = fst;
		}
	}

}

int main(){

	int i,k;

	scanf("%d%d",&K,&N);

	for(k =0 ; k <K; ++k){
		scanf("%s",str[k]);
		assert(strlen(str[k]) == N);
	}

	init();


	for(i = N-1; i >= 0; --i){
		cbs[i] = con_match[i] < 0 ? 0 : 1+cbs[con_match[i]+1];
	}

	printf("%lld\n",accumulate(cbs,cbs+N,0LL));

	return 0;
}

