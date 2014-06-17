#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include "grader.h"
#include "lang.h"

#define CHAR 65540
#define LANG 60
#define N 100

using namespace std;


int freq[CHAR+10];
int occ[CHAR+10][LANG+10];

double score[LANG+10];

int s= 0;
int L;

int tot;

void excerpt(int *E) {
	int i,k;

//	if(!s){
//		srand(7);
//		++s;
//	}

	memset(score,0,sizeof(score));

	for(i = 0; i < N; ++i){
		for(k = 0; k < L; ++k){
			if(!occ[E[i]][k]) continue;
			score[k] += (1.0/freq[E[i]]);
		}
	}

	k = max_element(score,score+L)-score;
	i = language(k);
	tot += i == k;
	k = i;
	for(i = 0; i < N; ++i){
		if(occ[E[i]][k]) continue;
		occ[E[i]][k] = 1;
		++freq[E[i]];
	}
}
