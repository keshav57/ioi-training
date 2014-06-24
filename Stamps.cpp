#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>

#define NMAX 100010
#define KMAX 12
#define MMAX 10010
#define A 26

using namespace std;

int lookup[KMAX][MMAX][A];

char stamps[KMAX][MMAX];
int size[KMAX];
char S[NMAX];

int exits[A];

int N,M,K;

int init(){
	int i,k,s;

	for(s = 0; s < K; ++s){

		for(k = 0; k < A; ++k){
			lookup[s][size[s]][k] = size[s];
		}

		for(i = size[s]-1; i >= 0; --i){

			for(k = 0; k < A; ++k){
				lookup[s][i][k] = lookup[s][i+1][k];
			}

			lookup[s][i][stamps[s][i]-'a'] = i;
			exits[stamps[s][i]-'a'] = 1;
		}
	}

	for(i = 0; i < N; ++i){
		if(!exits[S[i]-'a']) return 1;
	}

	return 0;
}

int pointers[KMAX];

int main(){
	int i,found,stampings,k;

	scanf("%d",&K);
	scanf("%d%s",&N,S);

	for(i =0 ; i < K; ++i){
		scanf("%d%s",&size[i],stamps[i]);
	}

	if(init()){
		printf("-1\n");
		return 0;
	}

	memset(pointers,-1,sizeof(int)*KMAX);

	stampings =0 ;
	i = 0;

	while(i < N){

		found = 0;

		for(k =0 ; k < K ;++k){
			if(pointers[k] >= size[k]-1) continue;
			pointers[k] = lookup[k][pointers[k]+1][S[i]-'a'];
			if(pointers[k] >= size[k])	continue;
			found = 1;
		}

		if(found){
			++i;
			continue;
		}

		++stampings;
		memset(pointers,-1,sizeof(int)*KMAX);
	}

	++stampings;
	printf("%d\n",stampings);

	return 0;
}
