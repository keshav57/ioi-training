/*
 Created By: Malvika Joshi
 Problem: Necklace (March-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=267
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define NMAX 10010
#define MMAX 1010

using namespace std;

int T[MMAX];
char word[MMAX],str[NMAX];
int M,N;

void init(){
	int i,j;

	T[0] = 0;
	i = 1;
	j = 0;

	while(i < M){
		if(word[i] == word[j]){
			T[i++] = ++j;
		}else if(j){
			j = T[j-1];
		}else{
			T[i++] = 0;
		}
	}
}

int suffix(int i, int j){
	while(1){
		if(str[i] == word[j]){
			return j+1;
		}
		if(j){
			j = T[j-1];
		}else{
			break;
		}
	}

	return 0;
}

int rem[NMAX][MMAX];

int dp(){
	int i,j,k;

	for(i = N-1; i >= 0; --i){
		for(j = 0; j < M; ++j){
			k = suffix(i,j);
			rem[i][j] = rem[i+1][j]+1;
			if(k < M) rem[i][j] = min(rem[i][j],rem[i+1][k]);
		}
	}

	return rem[0][0];
}

int main(){

	freopen("necklace.in","r",stdin);
	freopen("necklace.out","w",stdout);

	scanf("%s%s",str,word);

	N = strlen(str);
	M = strlen(word);

	init();
	printf("%d\n",dp());

	return 0;
}
