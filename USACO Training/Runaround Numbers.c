/*
 Created By: Malvika Joshi
 Problem: runround
 Link: http://cerberus.delos.com:791/usacoprob2?a=A2KThTc5TTs&S=runround
*/
#include <stdio.h>
#include <string.h>

int is_runaround(long long unsigned num){
	char digits[20];
	int visited[10] = {0};
	int vis = 0,i,n;

	sprintf(digits,"%llu",num);
	n = strlen(digits);

	i = 0;
	while(vis < n){
		if(visited[digits[i]-'0']){	return 0; };
		if(!(digits[i]-'0')) return 0;
		visited[digits[i]-'0'] = 1;
		vis++;
		i = (i+digits[i]-'0')%n;
	}

	if(i){
		return 0;
	}

	return 1;
}


long long unsigned get_next(long long unsigned cur){
	int i = cur;
	while(++i){
		if(is_runaround(i)){
			return i;
		}
	}
	return -1;
}

int main(){
	long long unsigned M;
	scanf("%llu",&M);
	printf("%llu\n",get_next(M));
	return 0;
}
