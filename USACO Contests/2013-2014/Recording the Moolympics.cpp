/*
 Created By: Malvika Joshi
 Problem: Recording The Moolympics (January-2014 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=381
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <cstring>

#define MAXN 160
#define s first
#define e second

using namespace std;

int max_rec[MAXN][MAXN][MAXN];
pair<int,int> range[MAXN];
int N;

int DP(){
    int i,j,k;

    for(j = 0; j <= N; ++j){
        for(k = 0; k  <= N; ++k){
            max_rec[0][j][k] = (range[0].e <= range[j].s || range[0].e <= range[k].s);
        }
    }

    for(i = 1; i < N; ++i){
        for(j = 0; j <= N; ++j){
            for(k = 0; k <= N; ++k){
                max_rec[i][j][k] = max_rec[i-1][j][k];
                if(range[i].e <= range[j].s) max_rec[i][j][k] = max(max_rec[i][j][k],max_rec[i-1][i][k]+1);
                if(range[i].e <= range[k].s) max_rec[i][j][k] = max(max_rec[i][j][k],max_rec[i-1][j][i]+1);
            }
        }
    }


    return max_rec[N-1][N][N];
}


int main(){

    int i;

    freopen("recording.in","r",stdin);
    freopen("recording.out","w",stdout);

    scanf("%d",&N);

    for(i = 0; i < N; ++i){
        scanf("%d%d",&range[i].s,&range[i].e);
    }

    sort(range,range+N);
    range[N] = make_pair(1000000010,1000000010);

    printf("%d\n",DP());

    return 0;
}
