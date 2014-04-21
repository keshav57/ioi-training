/*
 Created By: Malvika Joshi
 Problem: COINCHNG
 Link: http://www.codechef.com/problems/COINCHNG
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MAXS 510
#define MAXD 60
#define INF 1000000000000000000

typedef unsigned long long lli;

lli f[MAXD][MAXS];

int C,S;
lli K;

int init(){
	int i,s,n;

	for(s = 0; s <= S; ++s)	f[0][s] = s < C;

	for(i = 1; i < MAXD; ++i){
		for(s = 0; s <= S; ++s){
			f[i][s] = 0;
			for(n = 0; n < C; ++n){
				if(n > s) break;
				f[i][s] += f[i-1][s-n];
				assert(f[i][s] <= INF);
			}
		}
		if(f[i][S] >= K)	return i;
	}

	assert(0);
	return -1;
}

lli ipow(lli base, lli exp){
    lli result = 1;
    while (exp){
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}


lli query(int i, int s, lli k){
	if(!i)	return  s;

	int n;
	lli sol = 0;

	for(n = 0; n < C; ++n){
		if(f[i-1][s-n] >= k){
			sol += query(i-1,s-n,k);
			break;
		}
		k -= f[i-1][s-n];
		sol += (lli)ipow(C,i);
	}

	return sol;
}

int main(){

	int i,t;
	scanf("%d",&t);

	while(t--){
		scanf("%d%d%lld",&C,&S,&K);
		i = init();
		printf("%llu\n",query(i,S,K));
	}

	return 0;
}
