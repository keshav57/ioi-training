/*
 Created By: Malvika Joshi
 Problem: Pogo-Cow (November-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=345
*/

#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstring>
#include <iostream>

#define MAXN 1010

using namespace std;

pair<int,int> det[MAXN];  //det.first is pos and det.second is pts

int max_pts[MAXN][MAXN];
int stopped[MAXN][MAXN];
int N;

int DP_right(){
    int i,k,j;

    for(k = 0; k < N; ++k){
        max_pts[N-1][k] = det[N-1].second;
        stopped[N-1][k] = N-2;
    }

    for(i = N-2; i >= 0; --i){
        for(k = 0; k <= i; ++k){
            if(!k){
                max_pts[i][k] = det[i].second;
                for(j = N-1; j > i; --j){
                    if(det[j].first-det[i].first < det[i].first-det[k].first) break;
                    max_pts[i][k] = max(max_pts[i][k],max_pts[j][i] + det[i].second);
                }
                stopped[i][k] = j;
                continue;
            }

            max_pts[i][k] = max_pts[i][k-1];

            for(j = stopped[i][k-1]; j > i; --j){
                if(det[j].first-det[i].first < det[i].first-det[k].first) break;
                max_pts[i][k] = max(max_pts[i][k],max_pts[j][i] + det[i].second);
            }

            stopped[i][k] = j;
        }
    }

    int m = 0;
    for(i = 0; i < N; ++i){
        m = max(m,max_pts[i][i]);
    }

    return m;
}

int DP_left(){
    int i,j,k;

    for(k = N-1; k >= 0; --k){
        max_pts[0][k] = det[0].second;
        stopped[0][k] = 1;
    }

    for(i = 1; i < N; ++i){
        for(k = N-1; k >= i; --k){
            if(k == N-1){
                max_pts[i][k] = det[i].second;

                for(j = 0; j < i; ++j){
                    if(det[i].first-det[j].first < det[k].first-det[i].first) break;
                    max_pts[i][k] = max(max_pts[i][k], max_pts[j][i] + det[i].second);
                }

                stopped[i][k] = j;
                continue;
            }

            max_pts[i][k] = max_pts[i][k+1];

            for(j = stopped[i][k+1]; j < i; ++j){
                if(det[i].first-det[j].first < det[k].first-det[i].first) break;
                max_pts[i][k] = max(max_pts[i][k],max_pts[j][i]+det[i].second);
            }

            stopped[i][k] = j;
        }
    }

    int m = 0;
    for(i = 0; i < N; ++i){
        m = max(m,max_pts[i][i]);
    }

    return m;
}

int main(){

    int i;

    scanf("%d",&N);

    for(i = 0; i < N; ++i){
        scanf("%d%d",&det[i].first,&det[i].second);
    }

    sort(det,det+N);

    int sol = DP_left();
    sol = max(sol,DP_right());

    printf("%d\n",sol);

    return 0;
}
