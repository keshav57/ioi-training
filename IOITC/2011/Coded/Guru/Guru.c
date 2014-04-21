/*
 Created By: Malvika Joshi
 Problem: Stats Guru (IOITC-2011 Final 1)
 */

#include <stdio.h>

typedef struct { long long num,den; } frac;

int A[1000000];
int B[1000000];
frac C[1000000];
int maxima[1000000];
int N;


void init(void){

	int i;
	C[0].num = A[0];
	C[0].den = B[0];

	for(i = 1; i < N; i++){
		A[i] += A[i-1];
		B[i] += B[i-1];
		C[i].num = A[i];
		C[i].den = B[i];
	}
	return;
}

int isgreater(frac a, frac b){
	return (a.num*b.den) >= (b.num*a.den);
}

int main(){

	int i,m;
	frac max = {0,1};
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d",&A[i]);
	}

	for(i = 0;i < N; i++){
		scanf("%d",&B[i]);
	}

	init();
	m = 0;

	for(i = N-1;i >=0 ;--i){
		if(isgreater(C[i],max)){
			max = C[i];
			maxima[m] = i;
			m++;
		}
	}

	int j = m-1;
	for(i = 0;i < N; i++){
		if(i > maxima[j]){
			j--;
		}
		printf("%d ",maxima[j]+1);
	}

	return 0;
}
