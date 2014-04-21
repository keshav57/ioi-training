/*
 Created By: Malvika Joshi
 Problem: ariprog
 Link: http://cerberus.delos.com:791/usacoprob2?a=AE6w43S9ISB&S=ariprog
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {int start,diff; } a_p;

int compare(const void *a, const void*b){
	const a_p *p1 = (a_p*)a;
	const a_p *p2 = (a_p*)b;
	return p1->diff == p2->diff ? p1->start-p2->start : p1->diff-p2->diff;
}

a_p solution[10000];
int is_bisq[200000] = { 0 };
int M,N;

int main(){

	int  i,j,k,n,a,b,flag,maxB;

	scanf("%d%d",&N,&M);

	maxB = 2*M*M +1;

	for(i = 0; i <= M; i++){
		for(j = i;j <= M; j++){
			is_bisq[i*i+j*j] = 1;
		}
	}

	n = 0;

	for(i = 0;i < maxB; i++){
		if(is_bisq[i]){
			for(j = i+1;j < maxB && i+(j-i)*(N-1) < maxB; j++){
				if(is_bisq[j]){
					a = i;
					b = j-i;
					flag = 1;
					for(k = 1; k < N; k++){
						if(!is_bisq[a+b*k]){
							flag = 0;
							break;
						}
					}
					if(flag){
						solution[n].start = a;
						solution[n].diff = b;
						n++;
					}
				}
			}
		}
	}


	qsort(solution,n,sizeof(a_p),compare);

	if(!n){
		printf("NONE\n");
	}
	for(i = 0;i < n; i++){
		printf("%d %d\n",solution[i].start,solution[i].diff);
	}

	return 0;
}
