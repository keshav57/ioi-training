/*
 Created By: Malvika Joshi
 Problem: Typo (November-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=188
*/

#include <stdio.h>
#include <string.h>

char S[100000];
int N;

int main(void){

	int i,opened = 0,closed = 0;

	scanf("%s",S);
	N = strlen(S);

	for(i = 0;i < N; i++){
		if(S[i] == '('){
			opened++;
		}else {
			closed++;
		}

		if(closed > opened){
			printf("%d",closed);
			return 0;
		}
	}

	int count = 0;

	for(i = N-1;i >= 0;i--){
		if(opened-closed <= 1){
			printf("%d",count);
			break;
		}
		if(S[i] == '('){
			count++;
			opened--;
		}else{
			closed--;
		}
	}

	return 0;
}
