/*
 Created By: Malvika Joshi
 Problem: Clumsy Cows (November-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=190
*/

#include <stdio.h>
#include <string.h>

int main(){

	char str[1000000];
	int n,err=0,i,opened=0,closed=0;

	scanf("%s",str);
	n = strlen(str);

	for(i = 0;i < n; i++){
		if(str[i] == '('){
			opened++;
		}else {
			closed++;
		}
		if(closed > opened){
			err++;
			closed--;
			opened++;
		}
	}

	err = err + (opened - closed)/2;

	printf("%d",err);
	return 0;
}
