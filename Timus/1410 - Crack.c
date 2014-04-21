/*
 Created By: Malvika Joshi
 Problem: Crack
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1410
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int Len[10010];
int S[10010];
int N;

inline int max(int a, int b){ return a > b ? a : b; }

int DP(){
	int i;
	S[0] = Len[0];
	S[1] = Len[1];
	S[2] = S[0]+Len[2];

	for(i = 3; i < N; i++){
		S[i] = max(S[i-2],S[i-3]) + Len[i];
	}

	return max(S[N-1],S[N-2]);
}

int main(){
	int i,n,l;
	char c[3000000];

	N = 0;

	while(fgets(c,3000000,stdin) != NULL){
		l = strlen(c);
		n = 0;
		for(i = 0;i < l ; i++){
			if(!isalpha(c[i])){
				if(n) Len[N++] = n;
				n = 0;
			}else{
				n++;
			}
		}
	}

	printf("%d",DP());

	return 0;
}
