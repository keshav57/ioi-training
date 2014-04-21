/*
 Created By: Malvika Joshi
 Problem: Mnemonics and Palindromes
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1635
*/

#include <stdio.h>
#include <string.h>

short is_palindrome[4010][4010] = {{0}};
int N;
char str[4010];
int num[4010];
int start[4010];

void init(){
	int i,j,k;
	for(i = 1;i < N; i++){
		j = i-1;
		k = i+1;
		while(j > 0 && k < N && str[j] == str[k]){
			is_palindrome[j][k] = 1;
			j--, k++;
		}
		j = i;
		k = i+1;
		while(j > 0 && k < N && str[j] == str[k]){
			is_palindrome[j][k] = 1;
			j--, k++;
		}
	}
}

int DP(){
	int i,j,temp;
	num[0] = 0;

	for(i = 1; i < N; i++){
		num[i] = num[i-1] + 1;
		start[i] = i;

		for(j = i-1; j > 0; j--){
			if(!is_palindrome[j][i]) continue;
			temp = num[j-1] + 1;
			if(temp < num[i]){
				num[i] = temp;
				start[i] = j;
			}
		}
	}

	return num[N-1];
}

void print(int x){
	if(x <= 0){
		return;
	}
	int k;
	print(start[x]-1);
	for(k = start[x]; k <= x; k++){
		printf("%c",str[k]);
	}
	if(x != N-1) printf(" ");
	else printf("\n");
}

int main(){
	str[0] = '#';
	scanf("%s",str+1);
	N = strlen(str);
	init();
	printf("%d\n",DP());
	print(N-1);
	return 0;
}
