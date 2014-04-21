/*
 Created By: Malvika Joshi
 Problem: Ordering the soldiers
 Link: http://www.spoj.com/problems/ORDERS/
*/

#include <stdio.h>

#define MAXN 200010

int T[MAXN];
int low[MAXN];
int N,root;

void init(){
	int i;

	i = N;
	root = 0;
	while(i >>= 1)	root++;

	root = 1 << root;

	for(i = 1; i <= N; i++) low[i] = i-low[i];

	T[0] = 0;
	for(i = 1; i <= N; i++){
		T[i] = i- (i - (i & -i));
	}
}

void update(int x, int v){
	while(x <= N){
		T[x] -= v;
		x += (x & -x);
	}
}

int search(int t){
	int n,i;
	n = root;
	i = 0;

	while(n && i < N){
		if(i+n <= N && t > T[i+n]){
			i += n;
			t -= T[i];
		}
		n >>= 1;
	}


	return i+1;
}

void print(int i){
	if(!i) return;
	int k = search(low[i]);
	update(k,1);
	print(i-1);
	printf("%d ",k);
}

int main(){
	int i,t;

	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);
		for(i = 1; i <= N; i++){
			scanf("%d",&low[i]);
		}

		init();
		print(N);
		printf("\n");
	}

	return 0;
}
