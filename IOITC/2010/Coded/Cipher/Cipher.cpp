/*
 Created By: Malvika Joshi
 Problem: Substitution Ciphers (IOITC-2010 Test 3)
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>

#define MAXN 1010
#define MAXM 10010

using namespace std;

int N,M;

vector<int> mess[MAXM];
vector<int> adj[MAXN];

int deg[MAXN];
int Q[MAXN];
int d_time[MAXN];
int top[MAXN];

int H,T;

int swap0 = -1;

void top_sort(){
    int v,i,u,k;

    for(i = 0; i < N; ++i){
        if(deg[i]) continue;
        d_time[i] = 0;
        Q[T++] = i;
    }

    k = 0;

    while(H < T){
        v = Q[H++];
        top[k++] = v;

        for(i = 0; i < adj[v].size(); ++i){
            u = adj[v][i];
            if(--deg[u]) continue;
            Q[T++] = u;
            d_time[u] = d_time[v]+1;
        }
    }
}

int init(){
    int i,k,off;

    for(i = 0; i < M-1; ++i){
        for(k = 0; k < mess[i].size() && k < mess[i+1].size(); ++k){
            if(mess[i][k] == mess[i+1][k]) continue;
            adj[mess[i][k]].push_back(mess[i+1][k]);
            ++deg[mess[i+1][k]];
            break;
        }
    }


    top_sort();

    off = 0;

    for(i = 0; i < N; ++i){
        d_time[top[i]] += off;
        if(i < N && d_time[top[i]] == d_time[top[i+1]]+off){
            ++off;
            swap0 = i;
        }
    }

    return !off;
}


int main(){
    int i,n,k;

    scanf("%d%d",&N,&M);

    for(i = 0; i < M; ++i){
        scanf("%d",&n);
        while(n--){
            scanf("%d",&k);
            mess[i].push_back(k-1);
        }
    }

    if(init()){
        printf("YES\n");
        for(i = 0 ; i < N; ++i) printf("%d ",top[i]+1);
        printf("\n");
        return 0;
    }


    printf("NO\n");
    for(i = 0; i < N; ++i) printf("%d ",top[i]+1);
    printf("\n");
    swap(top[swap0],top[swap0+1]);
    for(i = 0; i < N; ++i) printf("%d ",top[i]+1);
    printf("\n");

    return 0;
}
