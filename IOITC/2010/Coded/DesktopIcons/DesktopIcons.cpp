/*
 Created By: Malvika Joshi
 Problem: Desktop Icons (IOITC-2010 Final 1)
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

#define MAXN 42

using namespace std;

vector<int> sol;
int mat[MAXN][MAXN];
int M,N,a,b;

int compute(int si, int sj){
    int i,j,ti,tj;
    int m0,m1;

    m0 = m1 = 0;

    for(i = 0; i < a; ++i){
        for(j = 0; j < b; ++j){
            ti = (i+si)%M;
            tj = (j+sj)%N;
            if(mat[ti][tj] > m0){
                m1 = m0;
                m0 = mat[ti][tj];
                continue;
            }
            m1 = max(m1,mat[ti][tj]);
        }
    }

    return m1;
}

int main(){
    int i,j;

    scanf("%d%d",&M,&N);

    for(i = 0; i < M; ++i){
        for(j = 0; j < N; ++j){
            scanf("%d",&mat[i][j]);
        }
    }

    scanf("%d%d",&a,&b);

    for(i = 0; i < M; ++i){
        for(j = 0; j < N; ++j){
            sol.push_back(compute(i,j));
        }
    }

    sort(sol.begin(),sol.end());

    for(i = 0; i < sol.size(); ++i){
        printf("%d\n",sol[i]);
    }

    return 0;
}
