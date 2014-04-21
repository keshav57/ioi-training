/*
 Problem: Zorgian Genetics
*/

#include <stdio.h>
#include <algorithm>

int A[100000];
int N;

int main(){
	int i,j,n;
	int oc[4] = {0};
	int rm[4] = {0};
	int replace[4] = {0};

	scanf("%d\n",&N);

	n = N *2;
	for(i = 0;i < n; i++){
		A[i] = getchar() - 'A';
	}

	for(i = 1;i < N; i++){
		if(A[i-1] == A[i]){
			printf("-1");
			return 0;
		}
	}

	for(i = 0;i < n; i++){
		oc[A[i]]++;
		if(oc[A[i]] > N){
			printf("-1");
			return 0;
		}
	}

	for(i = 0;i < 4; i++){
		rm[i] = N-oc[i];
	}

	for(i = 0;i < 4;i ++){
		for(j = 0;j < 4; j++){
			if(i != j && oc[i] == rm[j]){
				replace[i] = j;
				rm[j] = -1;
				break;
			}
		}
	}

	for(i = 0;i < n; i++){
		putchar(replace[A[i]] + 'A');
	}

}
