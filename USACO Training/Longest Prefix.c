/*
 Created By: Malvika Joshi
 Problem: prefix
 Link: http://cerberus.delos.com:791/usacoprob2?S=prefix&a=WV4NTPbEa4F
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char primitive[250][20];
char S[200010];
int N,L;

int prefix_check(int start, int n, char T[20]){
	int i,j = start;

	for(i = 0;i < n; i++,j++){
		if(j >= N || T[i] != S[j])	return 0;
	}

	return 1;
}

int longest_prefix(){

	int i,j,n,max = 0;
	int prefix[200000] = {0};

	for(i = 0;i < N; i++){
		if(i && !prefix[i]){ continue; }
		max = i;
		for(j = 0;j < L; j++){
			n = strlen(primitive[j]);
			 if(prefix_check(i,n,primitive[j])){
				if(i+n >= N) return N;
				prefix[i+n] = 1;
			}
		}
	}

	return max;
}

int main(){
	char c;
	L = -1;
	N = 0;

	freopen("prefix.in","r",stdin);

	do{
		scanf("%s",primitive[++L]);
	}while(primitive[L][0] != '.');

	while(scanf("%c",&c) != EOF){
		if(c != '\n') S[N++] = c;
	}


	int  m = longest_prefix();

	printf("%d\n",m);
	return 0;
}


