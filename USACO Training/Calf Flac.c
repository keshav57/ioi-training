/*
 Created By: Malvika Joshi
 Problem: calfflac
 Link: http://cerberus.delos.com:791/usacoanal2?a=n6BRw2oFkXX&S=calfflac
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char A[30000];
char T[50000];
int lookup[50000];
int P[50000];
int N = 0,L;

int min(int a, int b){
	return a < b ? a : b;
}

void process(){
	int i;
	T[N] = '1';
	lookup[N] = -1;
	N++;
	T[N] = '#';
	lookup[N] = -1;
	N++;
	for(i = 0;i < L; i++){
		if(isalpha(A[i])){
			T[N] = tolower(A[i]);
			lookup[N] = i;
			N++;
			T[N] = '#';
			lookup[N] = -1;
			N++;
		}
	}
	T[N] = '#';
	lookup[N] = -1;
	N++;
	T[N] = '0';
	lookup[N] = -1;
	N++;
}

int longest_pal(){
	int center = 0,right = 0,i,_i,max;

	for(i = 1;i < N-1;i ++){
		_i = 2*center-i;
		P[i] = (right > i) ? min(right-i,P[_i]) : 0;

		while(T[i+1+P[i]] == T[i-1-P[i]])	P[i]++;

		if(i + P[i] > right){
			center = i;
			right = i + P[i];
		}
	}

	max = 0;
	for(i = 1;i < N-1; i++){
		if(P[i] > P[max]){
			max = i;
		}
	}
	return max;
}

int main(){

	int c,s,e,i = 0;

	while(scanf("%c",&A[i]) != EOF){
		i++;
	}

	L = i;
	process();

	c = longest_pal();
	e = lookup[c+P[c]] == -1 ? lookup[c+P[c]-1] : lookup[c+P[c]];
	s = lookup[c-P[c]] == -1 ? lookup[c-P[c]+1] : lookup[c-P[c]];

	printf("%d\n",P[c]);

	for(i = s; i <= e; ++i){
		printf("%c",A[i]);
	}

	printf("\n");


	return 0;
}

