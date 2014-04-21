/*
 Created By: Malvika Joshi
 Problem: Awkward Digits (November-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=85
*/

#include <stdio.h>
#include <string.h>

#define MAX_T 20
#define MAX_B 30

char inc[MAX_T];
char ter[MAX_T];
int bin;
int tsize,t;

void ternary(int dec){
	if(!dec) return;
	ternary(dec/3);
	ter[tsize++] = dec%3+'0';
}

int cmp(){
	int mis = 0,i;
	for(i = 0; i < t; i++){
		mis += inc[i] != ter[i];
		if(mis > 1) return 0;
	}

	return mis;
}

int main(){
	int i,n;
	char ip[MAX_B];

	scanf("%s",ip);
	n = strlen(ip);
	for(i = 0; i < n; ++i)	bin |= ((ip[n-1-i]-'0')<<i);


	scanf("%s",inc);
	t= strlen(inc);

	for(i = 0; i < n; ++i){
		bin ^= (1<<i);
		tsize = 0;
		memset(ter,'0',sizeof(char)*MAX_T);
		ternary(bin);
		if(cmp()) break;
		bin ^= (1<<i);
	}

	printf("%d\n",bin);

	return 0;
}
