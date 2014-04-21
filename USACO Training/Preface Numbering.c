/*
 Created By: Malvika Joshi
 Problem: preface
 Link: http://cerberus.delos.com:791/usacoprob2?S=preface&a=RgNN8fPjLBi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Roman[4000][20];
int count[7] = {0};
char mark[7] = "IVXLCDM";
int N;

void init(){

	int i,prefix;

	strcpy(Roman[1],"0");
	strcpy(Roman[5],"1");
	strcpy(Roman[10],"2");
	strcpy(Roman[50],"3");
	strcpy(Roman[100],"4");
	strcpy(Roman[500],"5");
	strcpy(Roman[1000],"6");

	for(i = 1;i < 1000; i*=10){
		sprintf(Roman[i*10-i],"%s%s",Roman[i],Roman[i*10]);
		sprintf(Roman[i*5-i],"%s%s",Roman[i],Roman[i*5]);
	}

	for(i = 1;i <= N; i++){
		if(strcmp(Roman[i],"")){
			prefix = i;
		}else {
			sprintf(Roman[i],"%s%s",Roman[prefix],Roman[i-prefix]);
		}
	}
}

void count_occurrences(){
	int i,j,n;

	for(i = 1;i <= N; i++){
		n = strlen(Roman[i]);
		for(j = 0;j < n; j++){
			count[Roman[i][j]-'0']++;
		}
	}
}

int main(){
	int i;
	scanf("%d",&N);
	init();
	count_occurrences();
	for(i = 0;i < 7; i++){
		if(!count[i]) break;
		printf("%c %d\n",mark[i],count[i]);
	}
	exit(0);
}
