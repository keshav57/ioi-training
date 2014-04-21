/*
 Created By: Malvika Joshi
 Problem: Cows in a Row (US Open-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=130
*/

#include <stdio.h>

#define MAX_N 1010
#define MAX_ID 1000000

int cows[MAX_N];
int sel[MAX_ID];
int N;

inline int max(int a, int b){ return a > b ? a : b; }

int block(int id){
	if(sel[id]) return 0;
	sel[id] = 1;

	int seq[MAX_N];
	int i,n,maxs,curs;

	n = 0;
	for(i = 0; i <N; ++i){
		if(cows[i] == id) continue;
		else seq[n++] = cows[i];
	}

	maxs = 0;
	for(i = 0; i < n; ++i){
		if(i && seq[i] == seq[i-1]) curs++;
		else curs = 1;
		maxs = max(maxs,curs);
	}

	return maxs;
}

int main(){

	int i,maxseq;

	scanf("%d",&N);

	for(i = 0; i < N; ++i) scanf("%d",&cows[i]);

	maxseq = 0;

	for(i = 0; i < N; ++i)	maxseq = max(maxseq,block(cows[i]));

	printf("%d\n",maxseq);

	return 0;
}

