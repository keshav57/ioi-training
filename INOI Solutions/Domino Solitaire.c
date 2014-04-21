/*
 Created By: Malvika Joshi
 Problem: Domino Solitaire (INOI-2008)
 Link: http://www.iarcs.org.in/inoi/2008/inoi2008/inoi2008-qpaper.pdf
*/

#include <stdio.h>
#include <stdlib.h>

inline int max(int a, int b){
	return a > b ? a : b;
}


int M[2][10000];
int A[10000];
int N;

int main(){
	int i,j,s1,s2;

	scanf("%d",&N);

	for(i = 0;i < 2; i++){
		for(j = 1;j <= N;j ++){
			scanf("%d", &M[i][j]);
		}
	}

	A[0] = 0;
	A[1] = abs(M[0][1] - M[1][1]);

	for(i = 2;i <= N;i ++){
		s1 = A[i-2] + abs(M[0][i-1] - M[0][i]) + abs(M[1][i-1] - M[1][i]);
		s2 = A[i-1] + abs(M[0][i] - M[1][i]);
		A[i] = max(s1,s2);
	}

	printf("%d",A[N]);

	return 0;
}
