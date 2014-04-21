/*
 Created By: Malvika Joshi
 Problem: Matrix Game (IOITC-2010 Final 2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXS ((1<<20)+10)
#define MAXN 22
#define INF INT_MAX

inline int min(int a, int b){ return a < b ? a : b ; }

int min_sum[MAXS];
int mat[MAXN][MAXN];
int N;

int DP(){
    int i,sel,k,row;

    min_sum[0] = 0;

    for(sel = 1; sel < (1<<N); ++sel){
        row = __builtin_popcount(sel)-1;
        min_sum[sel] = INF;
        for(i = 0; i < N; ++i){
            if(!(sel&(1<<i))) continue;
            min_sum[sel] = min(min_sum[sel],min_sum[(sel^(1<<i))]+mat[row][i]);
        }
    }

    return min_sum[(1<<N)-1];
}

int main(){
    int i,j;

    scanf("%d",&N);

    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            scanf("%d",&mat[i][j]);
        }
    }

    printf("%d\n",DP());

    return 0;
}
