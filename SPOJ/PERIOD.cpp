/*
 Created By: Malvika Josh
 Problem: Period
 Link: http://www.spoj.com/problems/PERIOD/
*/

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>

#define NMAX 100010

using namespace std;

int T[NMAX];
char str[NMAX];
int N;

void init(){
	int i,j;

	T[0] = 0;
	i = 1;
	j = 0;

	while(i < N){
		if(str[i] == str[j]){
			T[i++] = ++j;
		}else if(j){
			j = T[j-1];
		}else{
			T[i++] = 0;
		}
	}
}

int find_root(){
	int x;

	x = T[N-1];
	if(x*2 < N) return 1;

	if(!(N%(N-x))){
		return N/(N-x);
	}
	return 1;
}

int main(){

	scanf("%s",str);

	while(str[0] != '*'){
		N = strlen(str);
		init();
		printf("%d\n",find_root());
		scanf("%s",str);
	}

	return 0;
}
