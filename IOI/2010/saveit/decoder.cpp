#include "grader.h"
#include <iostream>
#include <cassert>
#include "decoder.h"

#define NMAX 1010
#define MMAX 40
using namespace std;



int par[NMAX];
int child[NMAX][NMAX];
int c[NMAX];

int L;

int N,M;

int tern[NMAX*MMAX];
int T2;

int dec_dist[MMAX][NMAX];

int typ[NMAX];

void dfs(int v, int *dec){
	int i;

	if(typ[v] >= 0){
		dec[v] = dec[par[v]] + (typ[v] ? (typ[v] == 1 ? -1 : 1) : 0);
	}

	for(i =0; i < c[v]; ++i){
		dfs(child[v][i],dec);
	}
}

void decode(int nv, int nh) {
	int i,k,b,val;

	 N = nv, M = nh;

	par[0] = -1;
	int p = 0;
	for(i = 1; i < N; ++i){
		for(b = 0; b < 10; ++b){
			val = decode_bit();
			++p;
			par[i] |= (val<<b);
		}
	}


	for(i = 1; i < N ;++i){
		child[par[i]][c[par[i]]++] = i;
	}


	k = N;
	for(i = 0; i < M; ++i){
		L += --k;
	}


	L = ((L+2)/3);

	for(i = 0; i < L; ++i){
		k = 0;
		for(b = 0; b < 5; ++b){
			val = decode_bit();
			k |= (val<<b);
		}

		for(b = 0; b < 3; ++b){
			tern[T2++] = k%3;
			k /= 3;
		}
	}


	b =0;
	for(i = 0; i < M; ++i){
		for(k =0; k <= i; ++k){
			dec_dist[i][k] = dec_dist[k][i];
			typ[k] = -1;
		}
		for(; k < N; ++k){
			typ[k] = tern[b++];
		}


		dfs(0,dec_dist[i]);

	}

	for(i = 0; i < M; ++i){
		for(k = 0; k < N; ++k){
			if(i == k) assert(dec_dist[i][k] == 0);
			hops(i,k,dec_dist[i][k]);
		}
	}


}
