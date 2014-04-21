/*
 Created By: Malvika Joshi
 Problem: Increasing Subsequences
 Link: http://www.spoj.com/problems/INCSEQ/
*/

#include <stdio.h>
#include <string.h>

#define MAXN 10000
#define MAXT 100001
#define MAXK 50
#define MOD 5000000

int T[MAXT+5];
int Seq[MAXK+5][MAXN+5];
int A[MAXN+5];
int N,K;

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
	while(x <= MAXT){
		T[x] += val;
		if(T[x] >= MOD) T[x] -= MOD;
		x += (x&-x);
	}
}

int DP(){
	int i,k,s;

	for(i = 0; i < N; i++)	Seq[0][i] = 1;

	for(k = 1; k < K; k++){
		memset(T,0,sizeof(int)*(MAXT+5));
		for(i = 0; i < N; i++){
			Seq[k][i] = read(A[i]-1);
			update(A[i],Seq[k-1][i]);
		}
	}

	s = 0;
	for(i = 0;  i < N; i++) {
		s += Seq[K-1][i];
		if(s >= MOD) s-= MOD;
	}

	return s;
}

int main(){
	int i;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N; i++){
		scanf("%d",&A[i]);
		++A[i];
	}
	printf("%d\n",DP());

	return 0;
}
