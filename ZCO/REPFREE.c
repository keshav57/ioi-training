/*
 Created By: Malvika Joshi
 Problem: REPFREE
 Link: http://opc.iarcs.org.in/index.php/problems/REPFREE
*/

#include <stdio.h>
#include <string.h>

int visited[10] = {0};
int digits[9];
int n = 0;

int main(){

	visited[0] = 1;
	int i,c,s = 1;
	char number[10];
	int num;
	scanf("%d",&num);

	if(num > 987654320){
		printf("0");
		return 0;
	}

	num++;

	if(num % 10 == 9){
		num++;
	}

	sprintf(number,"%d",num);

	n = strlen(number);
	c = n;


	for(i = 0;i < n; i++){
		digits[i] = number[i] - '0';
	}


	for(i = 0;i < n; i++){
		if(visited[digits[i]]){
			c = i;
			break;
		}
		visited[digits[i]] = 1;
	}

	s  = digits[c];
	if(digits[c] == 9){
		visited[digits[c-1]] = 0;
		digits[c-1]++;
		visited[digits[c-1]] = 1;
	}

	for(i = c; i < n; i++){

		while(visited[s]){
			if(s == 9){
				s = 1;
			}else {
				s++;
			}
		}
		visited[s] = 1;
		digits[i] = s;
	}

	for(i = 0;i < n; i++){
		printf("%d",digits[i]);
	}

	return 0;
}
