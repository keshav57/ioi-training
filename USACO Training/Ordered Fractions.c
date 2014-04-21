/*
 Created By: Malvika Joshi
 Problem: frac1
 Link: http://cerberus.delos.com:791/usacoprob2?a=YnrI700o9Fg&S=frac1
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int n,d; } fraction;

int compare(const void *a,const void *b){
	const fraction* f1 = (fraction*) a;
	const fraction* f2 = (fraction*) b;
	return (f1->n*f2->d) - (f2->n*f1->d);
}

int is_reduced(int a, int b){
	if(a == 1 || b == 1) return 1;
	int t;
	while(b > 0){
		t = b;
		b = a % t;
		a = t;
	}
	return a == 1;
}

fraction f[20000];
int N,K = 0;

int main(){
	int i,j;

	scanf("%d",&N);

	for(i = 1;i <= N;  i++){
		for(j = 0;j <= i; j++){
			if(is_reduced(i,j)){
				f[K].d = i;
				f[K].n = j;
				K++;
			}
		}
	}

	qsort(f,K,sizeof(fraction),compare);

	for(i = 0;i < K ;i++){
		printf("%d/%d\n",f[i].n,f[i].d);
	}

	return 0;
}

