/*
 Created By: Malvika Joshi
 Problem: fracdec
 Link: http://cerberus.delos.com:791/usacoprob2?S=fracdec&a=pCHmrNTn9hl
*/
#include <stdio.h>
#include <string.h>

int N,D;
int sol[100000];
int visited[100000] = {0};
int S = 0;

int dec(){

	while(!visited[N]){
		visited[N] = S+1;
		N *= 10;
		sol[S++] = N/D;
		N %= D;
		if(N == 0){
			return 0;
		}
	}


	return N;
}


int main(){
	scanf("%d%d",&N,&D);

	if(N % D == 0){
		printf("%d.0\n",N/D);
		return 0;
	}

	char buf[100000];
	sprintf(buf,"%d",N/D);
	N %= D;

	int i = 0,ch = 0;

	printf("%s.",buf);
	ch = strlen(buf) + 1;

	int recur;

	recur = dec();


	if(recur){
		for(i = 0;i < S; i++){
			if(i == visited[recur]-1){
				printf("(");
				ch++;
			}
			printf("%d",sol[i]);
			ch++;
			if(ch % 76 == 0){ printf("\n"); }
		}
		printf(")\n");
	}else{
		for(i = 0;i < S; i++){
			printf("%d",sol[i]);
			ch++;
			if(ch % 76 == 0 || i == S-1){ printf("\n"); }
		}
	}

	return 0;
}
