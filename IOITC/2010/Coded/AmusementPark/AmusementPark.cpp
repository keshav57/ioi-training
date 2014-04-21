/*
 Created By: Malvika Joshi
 Problem: Amusement Park (IOITC-2010 Final-2)
*/

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXN 200010
#define MAXLINK 20

using namespace std;
typedef long long lli;

int prev[MAXN][MAXLINK];
int llist[MAXN];

int high_ancestor[MAXN];

int height[MAXN];
vector<int> adj[MAXN];
int visited[MAXN];

int valid_a[MAXN];

int N;

int get_prev(int head, int target){
    if(head < 0) return -1;
    if(height[llist[head]] >= target) return head;

    int step_size,cur,link;

    cur = head;             //cur is the index in llist not height
    step_size = MAXLINK;


    while(step_size--){
        link = prev[cur][step_size];          //link is the index in llist
        if(link < 0 || height[llist[link]] >= target) continue;
        cur = link;
    }

    return prev[cur][0];
}


void init(int v, int head){
    if(visited[v]) return;

    int i,half_step,step;

    visited[v] = 1;

    llist[++head] = v;
    prev[head][0] = get_prev(head-1,height[v]);

    high_ancestor[v] = prev[head][0] < 0 ? -1 : llist[prev[head][0]];

    for(step = 1; step < MAXLINK; ++step){
        half_step = prev[head][step-1];
        if(half_step < 0){
            prev[head][step] = -1;
            continue;
        }
        prev[head][step] = prev[half_step][step-1];
    }


    for(i = 0; i < adj[v].size(); ++i){
        init(adj[v][i],head);
    }
}

int pcheck[MAXN];

lli dfs(int v, int parent){
    if(visited[v]) return 0;

    int i,q1,q2;
    lli peaks;

    visited[v] = 1;
    valid_a[v] = high_ancestor[v] < 0 ? 0 : valid_a[high_ancestor[v]]+ (height[high_ancestor[v]] > height[v]);

    q1 = parent < 0 ? 0 : valid_a[parent];
    q2 = high_ancestor[v] < 0 ? 0 : valid_a[high_ancestor[v]];

    peaks = q1-q2;

    for(i = 0; i < adj[v].size(); ++i){
        peaks += dfs(adj[v][i],v);
    }

    return peaks;
}

int main(){

    int i,u,v;

    scanf("%d",&N);

    for(i = 0; i < N-1; ++i){
        scanf("%d%d",&u,&v);
        --u,--v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(i = 0; i < N; ++i) scanf("%d",&height[i]);

    init(0,-1);

    memset(visited,0,sizeof(int)*MAXN);

    printf("%lld\n",dfs(0,-1)+N-1);

    return 0;
}
