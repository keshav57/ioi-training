/*
 Created By: Malvika Joshi
 Problem: The Bessie Shuffle (December-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=363
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>

#define MAXM 1000010

using namespace std;

int is_path[MAXM];
int shuf[MAXM];
int id[MAXM];
vector<int> cycle[MAXM];
int path[MAXM];
int pos[MAXM];

int visited[MAXM];
int P[MAXM];

int M,N,Q;

int cur_id;

void init(int i){


    if(!P[i]){
        visited[i] = 1;
        shuf[i] = 1;
        path[shuf[i]] = i;
        is_path[i] = 1;
        return ;
    }

    if(visited[i]){
        id[i] = cur_id++;
        return;
    }

    visited[i] = 1;

    init(P[i]-1);

    shuf[i] = shuf[P[i]-1]+1;
    is_path[i] = is_path[P[i]-1];
    id[i] = id[P[i]-1];

    if(!is_path[i]) cycle[id[i]].push_back(i);
    else path[shuf[i]] = i;
}

int main(){
    int i;

   freopen("shuffle.in","r",stdin);
    freopen("shuffle.out","w",stdout);

    scanf("%d%d%d",&N,&M,&Q);

    for(i = 0; i < M; ++i){
        scanf("%d",&P[i]);
        --P[i];
    }

    for(i = 0; i < M; ++i){
        if(visited[i]) continue;
        init(i);
    }

    int over,clen,tmp;
    for(i = 0; i < N; ++i){

        if(i < M && is_path[i] && shuf[i] <= (N-M+1)){
            pos[N-shuf[i]+1] = i;
            continue;
        }

        if(i >= M && is_path[M-1] && shuf[M-1]+(i-M+1) <= (N-M+1)){
            pos[N-(shuf[M-1]+(i-M))] = i;
            continue;
        }

        if(i < M && !is_path[i]){
            over = (N-M+1);
            clen = cycle[id[i]].size();
            over %= clen;
            tmp = shuf[i]-1-over;
            if(tmp < 0) tmp += clen;
            pos[M-cycle[id[i]][tmp]-1] = i;
            continue;
        }

        if(i >= M && !is_path[M-1]){
            over = (N-M+1)-(i-M+1);
            clen = cycle[id[M-1]].size();
            over %= clen;
            tmp = shuf[M-1]-1-over;
            if(tmp < 0) tmp += clen;
            pos[M-cycle[id[M-1]][tmp]-1] = i;
            continue;
        }

        if(i >= M && is_path[M-1] && shuf[M-1]+(i-M+1) > (N-M+1)){
            over = (N-M+1)-(i-M+1);
            tmp = shuf[M-1]-over;
            pos[M-path[tmp]-1] = i;
            continue;
        }

        if(i < M && shuf[i] > (N-M)+1){
            over = (N-M+1);
            tmp = shuf[i]-over;
            pos[M-path[tmp]-1] = i;
        }
    }

    while(Q--){
        scanf("%d",&i);
        printf("%d\n",pos[i]+1);
    }

    return 0;
}
