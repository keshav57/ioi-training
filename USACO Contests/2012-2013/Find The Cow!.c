/*
 Created By: Malvika Joshi
 Problem: Find the Cow! (November-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=187
*/

#include <stdio.h>
#include <string.h>

char A[500000];
int N;

int main(void){

	int i,open,total;

	scanf("%s",A);
	N = strlen(A);

	open = 0;
	total = 0;

	for(i = 1;i < N; i++){
		if(A[i] == '(' && A[i-1] == '('){
			open++;
		}if(A[i] == ')' && A[i-1] == ')'){
			total += open;
		}
	}

	printf("%d",total);

	return 0;
}
