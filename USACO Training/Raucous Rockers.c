/*
 Created By: Malvika Joshi
 Problem: rockers
 Link: http://cerberus.delos.com:791/usacoprob2?S=rockers&a=A8GTi4chPxD
*/

#include <stdio.h>

int M,N,T;

int Stack[20];
int length[20];
int S = 0,maxstack = 0;

int can_include(){
	int sum = 0, disks = 1,i;
	for(i = 0;i < S; i++){
		if(sum + Stack[i] <= T){
			sum += Stack[i];
		}else{
			if(Stack[i] > T) return 0;
			if(++disks > M) return 0;
			sum = Stack[i];
		}
	}
	return 1;
}

void dfs(int song){
	if(song >= N){
		if(can_include()){
			maxstack = S > maxstack ? S : maxstack;
		}
		return;
	}

	Stack[S++] = length[song];
	dfs(song+1);
	--S;
	dfs(song+1);
}

int main(){
	int i;

	scanf("%d%d%d",&N,&T,&M);

	for(i = 0;i < N; i++){
		scanf("%d",&length[i]);
	}

	dfs(0);

	printf("%d\n",maxstack);

	return 0;
}
