/*
 Created By: Malvika Joshi
 Problem: One-Two, One-Two 2
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1495
*/

#include <stdio.h>

#define MAXN 1000010
#define D 31

char sol[D];
char mem[MAXN][D];
int N,S;

inline int ipow(long long base, int exp){
	long long result = 1;
	while (exp){
      if (exp & 1){
           result *= base;
           result %= N;
      }
       exp >>= 1;
       base *= base;
       base %= N;
   }
   return result;
}

//Strange but a dfs with memoization runs faster than a DP with an exactly same recurrence
int ext(int mod, int dg){

	if(mem[mod][dg]) return 0;
	mem[mod][dg] = 1;

	if(dg == 1){
		 if(mod  == 1 || mod == 2){
			 sol[S++] = mod;
			 return 1;
		 }
		 return 0;
	}

	int tmp = ipow(10LL,dg-1),tmd;

	tmd = mod-tmp;
	if(tmd < 0) tmd += N;

	tmd %= N;

	if(ext(tmd,dg-1)){
		sol[S++] = 1;
		return 1;
	}

	tmp *= 2;
	tmp %= N;

	tmd = mod-tmp;
	if(tmd < 0) tmd += N;

	tmd %= N;

	if(ext(tmd,dg-1)){
		sol[S++] = 2;
		return 1;
	}

	return 0;
}

int main(){

	scanf("%d",&N);

	if(N < 3){
		printf("%d\n",N);
		return 0;
	}

	int i;

	for(i = 1; i < D; i++){
		if(ext(0,i)){
			while(S--)	printf("%d",sol[S]);
			printf("\n");
			return 0;
		}
	}

	printf("Impossible\n");

	return 0;
}
