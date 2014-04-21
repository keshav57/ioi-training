/*
 Created By: Malvika Joshi
 Problem: Card Trick
 Link: http://www.spoj.com/problems/CTRICK/
*/

#include <stdio.h>
#include <string.h>

#define MAXN 20010

int T[MAXN];
int perm[MAXN];
int pos[MAXN];
int N,msb;

void update(int x, int val){
	while(x <= N){
		T[x] += val;
		x += (x&-x);
	}
}

int read(int x){
	int sum = T[0];

	while(x){
		sum += T[x];
		x -= (x&-x);
	}

	return sum;
}

int upper_bound(int tar){
	int i = 0,b,tmp,t;
	b = msb;
	t = tar;

	while(b && i < N){
		tmp = i + b;
		if(tmp <= N && tar >= T[tmp]){
			i = tmp;
			tar -= T[tmp];
		}
		b >>= 1;
	}

	return i;
}

void init(){
	int i;

	memset(T,0,sizeof(int)*MAXN);
	memset(perm,0,sizeof(int)*MAXN);

	msb = 1<<(31-__builtin_clz(N));

	for(i = 1; i <= N; i++){
		update(i,1);
		pos[i] = i%(N-i+1);
	}

}

void ctrick(){
	int i,lef,t,emt,s;

	s = 0;
	for(i = 1; i <= N; i++){

		emt = read(N);
		lef = read(s);
		t = pos[i] + lef;
		if(t >= emt) t -= emt;

		t = upper_bound(t);
		perm[t] = i;
		update(t+1,-1);
		s = t;
	}
}

int main(){
	int i,t;

	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);

		init();
		ctrick();

		for(i = 0 ; i < N; i++)
			printf("%d%c",perm[i],(i == N-1 ? '\n' : ' '));

	}

	return 0;
}

