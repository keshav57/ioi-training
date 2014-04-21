/*
 Created By: Malvika Joshi
 Problem: Wormholes (December-2103 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=360
*/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

#define x first
#define y second

using namespace std;

int next[15];
int paired[15];
int visited[15][2];


int cyc(int cur, int jumped){
    if(cur < 0) return 0;
    if(visited[cur][jumped]) return 1;
    visited[cur][jumped] = 1;
    if(!jumped) return cyc(paired[cur],1);
    return cyc(next[cur],0);
}

int tot;
int N;

void generate(int i){

    if(i >= N){
        int k;

        for(k = 0; k < N; ++k){
            memset(visited,0,sizeof(int)*15*2);
            if(!cyc(k,0)) continue;
            ++tot;
            break;
        }

        return;
    }

    if(paired[i] >= 0){
        generate(i+1);
        return;
    }

    int k;

    for(k = i+1; k < N; ++k){
        if(paired[k] >= 0) continue;
        paired[i] = k;
        paired[k] = i;
        generate(i+1);
        paired[k] = -1;
        paired[i] = -1;
    }
}

pair<int,int> pos[15];

int main(){
    int i,j;

    scanf("%d",&N);

    for(i = 0; i < N; ++i) scanf("%d%d",&pos[i].x,&pos[i].y);
    for(i = 0; i < N; ++i) next[i] = paired[i] = -1;


    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            if(j == i || pos[j].y != pos[i].y || pos[j].x < pos[i].x) continue;

            if(next[i] >= 0 && pos[next[i]].x < pos[j].x) continue;
            next[i] = j;
        }
    }

    generate(0);

    printf("%d\n",tot);

    return 0;
}



