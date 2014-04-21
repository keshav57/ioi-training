/*
 Created By: Malvika Joshi
 Problem: fence9
 Link: http://cerberus.delos.com:791/usacoprob2?S=fence9&a=TCIzuW7u0rk
*/

#include <stdio.h>
#include <stdlib.h>

inline int gcd(int a, int b){
	int t;
	while(b != 0){
		t = b;
		b = a % t;
		a = t;
	}
	return a;
}

int p,n,m;

int geti(){
	int A,b,i;

	A = m*p;
	b = gcd(n,m) + p + gcd(abs(n-p),m);
	i = A + 2 - b;

	return i/2;
}

int main(){

	int I;
	scanf("%d%d%d",&n,&m,&p);
	I= geti();
	printf("%d\n",I);
	return 0;
}
