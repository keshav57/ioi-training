/*
 Created By: Malvika Joshi
 Problem: Stock Market (IOITC-2011 Test 3)
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>

#define MAXN 1000010

using namespace std;

typedef long long lli;

lli msum[MAXN];
int diff[MAXN];
int N;

int init(lli sum){
    int i;

    for(i = 2; i <= N; ++i){
        msum[i] = msum[i-1] + i-1;
    }

    if(abs(sum) > msum[N]) return 1;
    if((msum[N]^sum)&1) return 1;

    return 0;
}


void compute(lli sum){

    int i,n;
    lli tmp;

    n = N;
    for(i = 0; i < N-1; ++i){
        --n;
        diff[i] = abs(sum+n) <= msum[n] ? -1 : +1;
        sum -= (n*diff[i]);
    }
}

int main(){

    int i,cur;
    lli sum;

    scanf("%d%lld",&N,&sum);

    if(init(sum)){
        printf("-1\n");
        return 0;
    }

    compute(sum);

    cur = 0;

    for(i = 0; i < N; ++i){
        printf("%d ",cur);
        cur += diff[i];
    }
    printf("\n");

    return 0;
}
