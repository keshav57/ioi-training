/*
 Created By: Malvika Joshi
 Problem: Times17 (March-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=121
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 1010

char original[MAX_N];
char into_17[MAX_N];

int mul_17(){
	int i,n;
	strcpy(into_17,original);
	sprintf(original,"0000%s",into_17);
	strcat(into_17,"0000");

	n = strlen(into_17);
	for(i = 0; i < n; i++){
		original[i] -= '0';
		into_17[i] -= '0';
	}
	char carry = 0;
	for(i = n-1; i >=0 ; --	i){
		into_17[i] += original[i] + carry;
		carry = into_17[i]>>1;
		into_17[i] -= (carry<<1);
	}
	for(i = 0; i < n; i++)	into_17[i] += '0';

	return carry;
}

int main(){

	scanf("%s",original);
	if(mul_17()) printf("1");
	printf("%s\n",into_17);
	return 0;
}
