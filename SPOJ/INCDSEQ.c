/*
 Created By: Malvika Joshi
 Problem: Distinct Increasing Subsequences
 Link: http://www.spoj.com/problems/INCDSEQ/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXK 50
#define MOD 5000000

typedef struct { int key,id; } cc;

int compare(const void *a, const void *b){
	const cc *p1 = (cc*)a;
	const cc *p2 = (cc*)b;
	return p1->key-p2->key;
}

int T[MAXN+5];
int pre[MAXN+5];
int Seq[MAXK+5][MAXN+5];
int A[MAXN+5];
int N,K;

void init(){
	int i,k;
	cc tmp[MAXN];

	for(i = 0; i < N; i++) tmp[i].id = i,tmp[i].key = A[i];
	qsort(tmp,N,sizeof(cc),compare);

	k = 1;
	for(i = 0; i < N; i++){
		if(!i || tmp[i].key == tmp[i-1].key){
			A[tmp[i].id] = k;
			continue;
		}
		A[tmp[i].id] = ++k;
	}
}

int read(int x){
	int sum = 0;
	while(x){
		sum += T[x];
		if(sum >= MOD) sum -= MOD;
		x -= (x&-x);
	}

	return sum;
}

void update(int x, int val){
	if(val < 0) val += MOD;
	while(x <= MAXN){
		T[x] += val;
		if(T[x] >= MOD) T[x] -= MOD;
		x += (x&-x);
	}
}

int DP(){
	int i,k,s;

	for(i = 0; i < N; i++)	Seq[0][i] = 1;


	for(k = 1; k < K; k++){
		memset(T,0,sizeof(int)*(MAXN+5));
		memset(pre,0,sizeof(int)*(MAXN+5));
		for(i = 0; i < N; i++){
			Seq[k][i] = read(A[i]-1);
			update(A[i],Seq[k-1][i]-pre[A[i]]);
			pre[A[i]] = Seq[k-1][i];
		}
	}

	s = 0;
	for(i = 0;  i < N; i++) pre[A[i]] = Seq[K-1][i];
	for(i = 1;  i <= N; i++){
		s += pre[i];
		if(s >= MOD) s -= MOD;
	}

	if(s < 0) s /= 0;
	return s;
}

int main(){
	int i;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N; i++)	scanf("%d",&A[i]);

	init();
	printf("%d\n",DP());

	return 0;
}
