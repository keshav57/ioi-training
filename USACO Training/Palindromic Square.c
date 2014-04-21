/*
 Created By: Malvika Joshi
 Problem palsquare
 Link: http://cerberus.delos.com:791/usacoprob2?a=vO5sS8b2zo5&S=pprime
*/
#include <stdio.h>
#include <string.h>

int B,temp;
char subs[] = {'0','1','2','3','4','5','6','7','8','9',
		'A','B','C','D','E','F','G','H','I','J'};
char square[20];
char num[20];

int is_palindrome(void){
	int i,j,n;
	n = strlen(square);
	for(i = 0,j = n-1; i < n; ++i,--j){
		if(square[i] != square[j]){
			return 0;
		}
	}
	return 1;
}

void empty(char *str){
	int i;
	for(i =0 ;i < 20; i++){
		str[i] = '\0';
	}
}

void base_B(char *b,int dec){
	if(dec == 0){
		temp = 0;
		return;
	}
	base_B(b,dec/B);
	b[temp] = subs[dec%B];
	temp++;
}

void print_palindromes(void){
	int dec;
	for(dec = 1;dec < 301; ++dec){
		empty(num);
		empty(square);
		base_B(num,dec);
		base_B(square,dec*dec);
		if(is_palindrome()){
			printf("%s %s\n",num,square);
		}
	}
}

int main(){
	scanf("%d",&B);
	print_palindromes();
	return 0;
}
