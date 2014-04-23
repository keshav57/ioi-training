/*
 Created By: Malvika Joshi
 Problem: Remove The String
 Link: http://www.spoj.com/problems/PSTRING/
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

int suffix(char c, int j){
	while(1){
		if(c == word[j]){
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
int suf[NMAX][30];

int dp(){
	int i,j,k;

	for(j = 0; j < M; ++j){
		rem[N][j] = 0;
		for(i = 0; i < 26; ++i){
			suf[j][i] = suffix(i+'a',j);
		}
	}

	for(i = N-1; i >= 0; --i){
		for(j = 0; j < M; ++j){
			k = suf[j][str[i]-'a'];
			rem[i][j] = rem[i+1][j]+1;
			if(k < M) rem[i][j] = min(rem[i][j],rem[i+1][k]);
		}
	}

	return rem[0][0];
}

int main(){

	while(scanf("%s%s",str,word) != EOF){
		N = strlen(str);
		M = strlen(word);

		init();
		printf("%d\n",dp());
	}

	return 0;
}
