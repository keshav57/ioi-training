/*
 Created By: Malvika Joshi
 Problem: Breed Proximity (March -2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=260
*/

#include <stdio.h>

#define MAX_id 1000000
#define MAX_N 50000

int St[MAX_id+10];
int A[MAX_N+10];
int N,K;

inline int max(int a, int b){ return a > b ? a : b; }

int main(){
	int i,j,m_id;
	scanf("%d%d",&N,&K);

	for(i = 0; i < N; i++) scanf("%d",&A[i]);

	m_id = -1;

	for(i = 0; i <= K; i++){
		if(St[A[i]]++) m_id = max(m_id,A[i]);
	}

	for(j = 0;i < N; i++,j++){
		--St[A[j]];
		if(St[A[i]]++) m_id = max(m_id,A[i]);
	}

	printf("%d\n",m_id);

	return 0;
}
