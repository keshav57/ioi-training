/*
 Created By: Malvika Joshi
 Problem: milk3
 Link: http://cerberus.delos.com:791/usacoprob2?S=milk3&a=f6osg6hpn9A
*/

#include <stdio.h>
#include <stdlib.h>

int cap_A,cap_B,cap_C;
int sol[80000];
int visited[21][21][21];
int S = 0,p = 0;

inline int min(int a,int b){ return a < b ? a : b; }

void pour(int A,int B,int C){
	if(visited[A][B][C]){ return; }
	if(!A){ sol[S++] = C; }

	visited[A][B][C] = 1;
p++;
	int pval;

	if(A){
		if(B < cap_B){
			pval = min(A,cap_B-B);
			pour(A-pval,B+pval,C);
		}
		if(C < cap_C){
			pval = min(A,cap_C-C);
			pour(A-pval,B,C+pval);
		}
	}
	if(B){
		if(A < cap_A){
			pval = min(cap_A-A,B);
			pour(A+pval,B-pval,C);
		}
		if(C < cap_C){
			pval = min(B,cap_C-C);
			pour(A,B-pval,C+pval);
		}
	}
	if(C){
		if(A < cap_A){
			pval = min(cap_A-A,C);
			pour(A+pval,B,C-pval);
		}
		if(B < cap_B){
			pval = min(C,cap_B-B);
			pour(A,B+pval,C-pval);
		}

	}
}

int compare(const void* a, const void *b){ return *(int*)a - *(int*)b; }

int main(){

	int i,j,k;

	for(i = 0;i < 21; i++){
		for(j = 0;j < 21; j++){
			for(k = 0;k < 21; k++){
				visited[i][j][k] = 0;
			}
		}
	}

	scanf("%d%d%d",&cap_A,&cap_B,&cap_C);

	pour(0,0,cap_C);

	qsort(sol,S,sizeof(int),compare);

	for(i = 0; i < S-1; i++){
		if(i > 0 && sol[i] == sol[i-1]) continue;
		printf("%d ",sol[i]);
	}
	printf("%d\n",sol[i]);

	return 0;
}
