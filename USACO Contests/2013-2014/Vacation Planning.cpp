/*
 Created By: Malvika Joshi
 Problem: Vactation Planning (December-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=362
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

#define MAXN 210
#define MAXK 110

#define INF 1000000000LL

using namespace std;

typedef long long lli;

lli dist[MAXN][MAXN];

int N,M,Q,K;

void floyd_warshall(){
    int i,j,k;

    for(k = 0; k < N; ++k){
        for(i = 0; i < N; ++i){
            for(j = 0; j < N; ++j){
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

int main(){
    int i,j,a,b,valid;
    lli total,cur;
    scanf("%d%d%d%d",&N,&M,&K,&Q);

    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            dist[i][j] = INF;
        }
        dist[i][i] = 0LL;
    }

    for(i = 0; i < M; ++i){
        scanf("%d%d",&a,&b);
        --a,--b;
        scanf("%lld",&dist[a][b]);
    }

    floyd_warshall();

    total = 0LL;
    valid = 0;
    while(Q--){
        scanf("%d%d",&a,&b);
        --a,--b;
        cur = INF;
        for(i = 0; i < K; ++i){
            cur = min(cur,dist[a][i]+dist[i][b]);
        }
        if(cur >= INF) continue;

        ++valid;
        total += cur;
    }

    printf("%d\n%lld\n",valid,total);

    return 0;
}
