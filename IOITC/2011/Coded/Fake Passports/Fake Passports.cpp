/*
 Created By: Malvika Joshi
 Problem: Fake Passport (IOITC-2011 Final-2)
*/

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>

#define N_MAX 510

#define INF 100000000000LL

typedef long long lli;

using namespace std;

lli adj[N_MAX][N_MAX];
char passport[N_MAX][N_MAX];
int N,M,K;

lli dist[N_MAX][N_MAX];
int Q[N_MAX];
int T;

vector<int> acc[N_MAX];

void dijktra(int src){
    int i,v;

    T = 0;
    for(i = 0; i < N; ++i){
    	if(passport[i][src]){
    		Q[T++] = i;
    	}
    	dist[src][i] = INF;
    }

    dist[src][src] = 0;

    while(T){

        v = -1;

        for(i = 0; i < T; ++i){
            if(dist[src][Q[T-1]] > dist[src][Q[i]]){
            	swap(Q[T-1],Q[i]);
            }
        }

        v = Q[--T];
        if(v < 0 || dist[src][v] >= INF) return;

        for(i = 0; i < N; ++i){
            if(!passport[i][src]) continue;
            dist[src][i] = min(dist[src][i],dist[src][v]+adj[v][i]);
        }
    }
}

lli dp[N_MAX][N_MAX];

lli init(){
    int i,j,k;

    for(i = 0; i < N; ++i) dijktra(i);

    for(i = 1; i < N; ++i) dp[i][1] = dist[0][i];

    for(k = 2; k <= K; ++k){
        for(i = 0; i < N; ++i){
            dp[i][k] = INF;
            for(j = 0; j < acc[i].size(); ++j) dp[i][k] = min(dp[i][k],dp[acc[i][j]][k-1]+dist[acc[i][j]][i]);
        }
    }

    return (dp[N-1][K] < INF ? dp[N-1][K] : -1);
}

int main(){
    int i,j,n;

    scanf("%d%d%d",&N,&M,&K);

    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            adj[i][j] = INF;
        }
    }

    while(M--){
        scanf("%d%d",&i,&j);
        --i,--j;
        scanf("%lld",&adj[i][j]);
        adj[j][i] = adj[i][j];
    }

    for(i = 0; i < N; ++i){
        scanf("%d",&n);
        while(n--){
            scanf("%d",&j);
            passport[j-1][i] = 1;
            acc[j-1].push_back(i);
        }
    }

    printf("%lld\n",init());

    return 0;
}
