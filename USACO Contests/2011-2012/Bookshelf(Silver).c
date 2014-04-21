/*
 Created By: Malvika Joshi
 Problem: Bookshelf (US Open-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=135
*/

#include <stdio.h>

#define MAXN 2010

int W[MAXN];
int H[MAXN];
int F[MAXN];

int N,L;

inline int min(int a, int b){ return a < b ? a : b; }
inline int max(int a, int b){ return a > b ? a : b; }

int DP(){
	int w,h,i,k;

	for(i = 1; i <= N; ++i){
		w = W[i];
		h = H[i];
		F[i] = F[i-1]+h;
		for(k = i-1; k > 0; --k){
			w += W[k];
			if(w > L) break;
			h = max(h,H[k]);
			F[i] = min(F[i],F[k-1]+h);
		}
	}

	return F[N];
}

int main(){

	int i;

	scanf("%d%d",&N,&L);
	for(i = 1; i <= N; i++)	scanf("%d%d",&H[i],&W[i]);

	printf("%d\n",DP());

	return 0;
}
