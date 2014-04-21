/*
 Created By: Malvika Joshi
 Problem: Blink (US Open-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=279
*/

#include <stdio.h>

#define MAX_N 16
#define EXP_N (1<<MAX_N)

int loop[EXP_N+10];
int visited[EXP_N+10];
int li[EXP_N+10];
int C,N;
long long B;

void print(int bin, int n){
	if(!bin && !n) return;
	printf("%d\n",bin%2);
	print(bin>>1,n-1);
}


int final_state(int stat){
	int prev,cur,i,clen,cstr;

	C = 0;
	cur = stat;

	while(!visited[cur]){
		li[cur] = C;
		loop[C++] = cur;
		visited[cur] = 1;
		prev = cur;

		for(i = 0; i < N-1; ++i){
			if(prev & (1<<i))	cur ^= (1<<(i+1));
		}

		if(prev & (1<<i))	cur ^= 1;
	}

	cstr = li[cur];
	clen = C-cstr;

	if(B < C)	return loop[B];
	B -= C;
	B %= clen;

	return loop[B+cstr];
}


int main(){

	int i,b,init,fin;

	scanf("%d%lld",&N,&B);

	init = 0;
	for(i = 0 ; i < N; ++i){
		scanf("%d",&b);
		init |= (b<<i);
	}

	fin = final_state(init);
	print(fin,N);

	return 0;
}

