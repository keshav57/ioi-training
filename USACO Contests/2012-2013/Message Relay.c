/*
 Created By: Malvika Joshi
 Problem: Message Relay (February-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=241
*/

#include <stdio.h>

int N,H = 0,T = 0;
int Q[1000];
int A[1000];

int bfs(){

	int i,v,nonloopy = 0;
	for(i = 0;i < N; i++){
		if(A[i] == -1){
			Q[T] = i;
			T++;
		}
	}

	while(H < T){
		nonloopy++;
		v = Q[H];
		H++;

		for(i = 0;i < N; i++){
			if(A[i] == v){
				Q[T] = i;
				T++;
			}
		}
	}

	return nonloopy;
}

int main(){

	int i;
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d",&A[i]);
		A[i]--;
	}

	printf("%d\n",bfs());

	return 0;
}
