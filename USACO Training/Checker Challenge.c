/*
 Created By: Malvika Joshi
 Problem: checker
 Link: http://cerberus.delos.com:791/usacoprob2?a=VuMBJS30c8i&S=checker
*/
#include <stdio.h>

int col_avail[15];
int diag_l[30];
int diag_r[30];
int sol[15];
int S = 0,N,maxn;

void print(){
	int i;
	for(i = 0;i < N-1; i++){
		printf("%d ",sol[i]+1);
	}
	printf("%d\n",sol[i]+1);
}

void backtrack(int row){
	if(row == N){
		if(S < 3) print();
		S++;
	}

	int i,d;
	for(i = 0;i < N; i++){
		d = row-i;
		if(col_avail[i] && diag_l[row-i+maxn] && diag_r[row+i]){
			sol[row] = i;
			diag_l[row-i+maxn] = 0;
			diag_r[row+i] = 0;
			col_avail[i] = 0;
			backtrack(row+1);
			diag_l[row-i+maxn] = 1;
			diag_r[row+i] = 1;
			col_avail[i] = 1;
		}
	}
}

int main(){

	int i;
	for(i = 0;i < 15; i++){
		col_avail[i] = 1;
	}
	for(i = 0;i < 30; i++){
		diag_l[i] = 1;
		diag_r[i] = 1;
	}

	scanf("%d",&N);
	maxn = N-1;
	backtrack(0);
	printf("%d\n",S);
	return 0;
}
