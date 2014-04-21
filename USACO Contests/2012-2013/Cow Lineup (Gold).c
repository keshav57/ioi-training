/*
 CreatedBy: Malvika Joshi
 Problem: Cows Lineup (January-2013 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=229
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int original,index,compressed; } c_e;

int compare(const void *a, const void *b){
    const c_e *c = a;
    const c_e *d = b;
	return c->original-d->original;
}

int A[100000];
int N,K;

void compress(void){
	c_e C[100000];
	int i,j;

	for(i = 0;i < N; i++){
		C[i].original = A[i];
		C[i].index = i;
	}

	qsort(C,N,sizeof(c_e),compare);

	for(i = 0,j = 0;i < N; i++){
		if(i > 0 && C[i-1].original != C[i].original){
			j++;
		}
		A[C[i].index] = j;
	}
	return;
}

int maxblock(){
	int i,j = 0,k = 0,max = 0;
	int lookup[100000] = {0};
	K++;

	compress();

	for(i = 0;i < N; i++){
		lookup[A[i]]++;
		if(lookup[A[i]] == 1){
			k++;
		}

		while(k > K){
			lookup[A[j]]--;
			if(lookup[A[j]] == 0){
				k--;
			}
			j++;
		}

		max = lookup[A[i]] > max ? lookup[A[i]] : max;
	}

	return max;
}

int main(){

	int i;

	scanf("%d%d",&N,&K);

	for(i = 0;i < N; i++){
		scanf("%d",&A[i]);
	}

	printf("%d",maxblock());

	return 0;
}
