/*
 Created By: Malvika Joshi
 Problem: hamming
 Link: http://cerberus.delos.com:791/usacoprob2?S=hamming&a=YnrI700o9Fg
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sel[64];
int N,B,D,S = 0;

int hamming_dist(int a, int b){
	int dist = 0,val = a^b;
	while(val){
		++dist;
		val &= val-1;
	}
	return dist;
}

int is_compatable(int test){
	int i;
	for(i = 0;i < S; i++){
		if(hamming_dist(sel[i],test) >= D) continue;
		return 0;
	}
	return 1;
}

void generate(){
	int i,limit = (int)pow(2,B);
	for(i = 0; i < limit && S < N; i++){
		if(is_compatable(i)){
			sel[S++] = i;
		}
	}
}

int main(){

	int i;

	scanf("%d%d%d",&N,&B,&D);

	generate();

	i = 0;
	printf("%d",sel[i++]);
	while(i < S){
		if(i % 10){
			printf(" %d",sel[i++]);
		}else{
			printf("\n%d",sel[i++]);
		}
	}

	printf("\n");

	exit(0);
}
