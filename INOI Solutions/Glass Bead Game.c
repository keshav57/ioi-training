/*
 Created By: Malvika Joshi
 Problem: Glass Bead Game (INOI-2009)
 Link: http://www.iarcs.org.in/inoi/2009/inoi2009/inoi2009-qpaper.pdf
*/

#include <stdio.h>
#include <limits.h>

#define min INT_MIN
#define max INT_MAX

int M,N;
int a,b,c;

inline int f(int m, int n){
	return a*m*m + b*n*n + c*m*n;
}

int self(void){
	int f1,f2;
	f1 = f(M-1,N+1);
	f2 = f(M,N-1);

	if(M == 0)	{f1 = min;}
	if(N == 0)	{f2 = min;}

	if(f1 > f2){
		M--;
		N++;
		return f1;
	}

	N--;
	return f2;
}

int oponent(void){
	int f1,f2;
	f1 = f(M-1,N+1);
	f2 = f(M,N-1);

	if(M == 0) {f1 = max;}
	if(N == 0) {f2 = max;}

	if(f1 < f2){
		M--;
		N++;
		return f1;
	}

	N--;
	return f2;
}

int main(void){

	int score;
	scanf("%d%d%d%d%d",&M,&N,&a,&b,&c);

	score = f(M,N);

	while(M != 0 || N != 0){
		if((M+N)%2 == 0){
			score = score + self();
		}else {
			score = score + oponent();
		}
	}

	printf("%d",score);

	return 0;
}
