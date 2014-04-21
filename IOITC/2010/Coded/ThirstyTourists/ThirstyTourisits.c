/*
 Created By: Malvika Joshi
 Problem: Thirsty Tourisits (IOITC-2010 Test 3)
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 5010

typedef long long lli;

int dist[MAXN];
int cost[MAXN];
int C,N,H;

inline int max(int a, int b){ return a > b ? a : b; }

lli min_cost(){
    int i,k,lit,rem;
    lli tot = 0;

    i = 0;
    rem = 0;
    while(i < N){
        for(k = i+1; k <= N && dist[k]-dist[i] <= C; ++k){
            if(cost[k] <= cost[i]) break;
        }

        if(k <= N && dist[k]-dist[i] <= C){
            tot += (max(0,dist[k]-dist[i]-rem))*(lli)cost[i];
            rem = max(rem-dist[k]+dist[i],0);
            i = k;
            continue;
        }

        tot += (C-rem)*(lli)cost[i];
        rem = C-dist[i+1]+dist[i];
        ++i;
    }

    return tot;
}

int main(){
    int i;

    scanf("%d%d%d",&H,&N,&C);

    for(i = 0; i < N; ++i){
        scanf("%d%d",&dist[i],&cost[i]);
    }
    dist[N] = H;

    printf("%lld\n",min_cost());
    return 0;
}
