/*
 Created By: Malvika Joshi
 Problem: lamps
 Link: http://cerberus.delos.com:791/usacoprob2?a=yRksFvQ5xM2&S=lamps
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int final_config[200];
int N,C,S = 0;
char sols[20][200];

int compare(const void *a, const void *b){
	const char *p1 = (char*) a;
	const char *p2 = (char*) b;
	return strcmp(p1,p2);
}

int matches_config(int A[]){
	int i;
	for(i = 0;i < N; i++){
		if(final_config[i] == -1 || final_config[i] == A[i]) continue;
		return 0;
	}
	return 1;
}

void press_button(int *A,int b){
	int i,start,diff;
	if(b == 1){
		start = 0;
		diff = 1;
	}else if(b == 2){
		start = 1;
		diff = 2;
	}else if(b == 3){
		start = 0;
		diff = 2;
	}else {
		start = 0;
		diff = 3;
	}

	for(i = start; i < N; i+=diff){
		A[i] ^= 1;
	}
}

void add_sol(int A[200]){
	int i;
	for(i = 0;i < N; i++){
		sols[S][i] = A[i] + '0';
	}
	S++;
}

void get_config(int b,int cur_config[200],int press){
	if(b > 4){
		if(C%2 == press %2 && C >= press && matches_config(cur_config)){
			add_sol(cur_config);
		}
		return;
	}

	get_config(b+1,cur_config,press);

	int after_press[200];
	memcpy(after_press,cur_config,sizeof(int)*200);
	press_button(after_press,b);
	get_config(b+1,after_press,press+1);
}

int main(){
	int i,cur_conf[200];

	scanf("%d%d",&N,&C);

	for(i = 0;i < N; i++){
		final_config[i] = -1;
		cur_conf[i] = 1;
	}

	scanf("%d",&i);
	while(i != -1){
		final_config[i-1] = 1;
		scanf("%d",&i);
	}

	scanf("%d",&i);
	while(i != -1){
		final_config[i-1] = 0;
		scanf("%d",&i);
	}

	get_config(1,cur_conf,0);
	qsort(sols,S,sizeof(char)*200,compare);
	for(i = 0;i < S; i++){
		printf("%s\n",sols[i]);
	}

	if(!S){
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
