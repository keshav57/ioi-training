/*
 Created By: Malvika Joshi
 Problem: Extend To Palindrome
 Link: http://www.spoj.com/problems/EPALIN/
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 100010

using namespace std;

int T[NMAX];
char str[NMAX];
char rev[NMAX];
int N;

void init(){
	int i,j;

	T[0] = 0;
	i = 1;
	j = 0;

	while(i < N){
		if(rev[j] == rev[i]){
			T[i++]= ++j;
		}else if(j){
			j = T[j-1];
		}else{
			T[i++] = 0;
		}
	}
}

int main(){
	int i,pos;

	while(scanf("%s",str) != EOF){
		N = strlen(str);
		memcpy(rev,str,N+1);
		reverse(rev,rev+N);

		init();

		pos = 0;
		i = 0;

		while(i < N){

			if(str[i] == rev[pos]){
				if(i+pos+1 >= N){
					break;
				}
				++i,++pos;
			}else if(pos){
				pos = T[pos-1];
			}else{
				++i;
			}
		}

		assert(i < N);
		for(i -= pos+1; i >= 0; --i){
			str[N++] = str[i];
		}
		str[N++] = '\0';

		printf("%s\n",str);
	}

	return 0;
}
