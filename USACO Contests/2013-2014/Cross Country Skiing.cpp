/*
 Created By: Malvika Joshi
 Problem: Cross Country Skiing (January-2014 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=380
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <cstring>

#define MAXN 510
#define MAXD 1000000010

using namespace std;

typedef pair<int,int> pt;

const pt adj[4] = { make_pair(0,1), make_pair(0,-1), make_pair(1,0), make_pair(-1,0) };

char waypt[MAXN][MAXN];
int height[MAXN][MAXN];
int M,N,W;

char visited[MAXN][MAXN];
pt Q[MAXN*MAXN];
int H,T;

int bfs(pt s, int d){
    pt v,u;
    int i,way;

    way = 0;
    H = T = 0;
    memset(visited,0,sizeof(char)*MAXN*MAXN);

    Q[T++] = s;
    visited[s.first][s.second]  =1;

    while(H < T){
        v = Q[H++];
        way += waypt[v.first][v.second];

        for(i = 0; i < 4; ++i){
            u = make_pair(v.first+adj[i].first,v.second+adj[i].second);
            if(u.first < 0 || u.first >= M) continue;
            if(u.second < 0 || u.second >= N) continue;
            if(visited[u.first][u.second]) continue;

            if(abs(height[u.first][u.second]-height[v.first][v.second]) > d) continue;

            Q[T++] = u;
            visited[u.first][u.second] = 1;
        }
    }


    return way;
}

int bin_search(pt src){

    int high,low,mid;

    high = MAXD;
    low = 0;

    while(low < high){

        mid = low + (high-low)/2;
        if(bfs(src,mid) >= W){
            high = mid;
        }else{
            low = mid+1;
        }
    }

    return low;
}

int main(){

    int i,j;
    pt src;

    freopen("ccski.in","r",stdin);
    freopen("ccski.out","w",stdout);

    scanf("%d%d",&M,&N);

    src = make_pair(0,0);

    for(i = 0; i < M; ++i){
        for(j =0 ; j < N; ++j){
            scanf("%d",&height[i][j]);
        }
    }

    for(i = 0; i < M; ++i){
        for(j = 0; j < N; ++j){
            scanf(" %c",&waypt[i][j]);
            waypt[i][j] -= '0';
            if(!waypt[i][j]) continue;
            src = make_pair(i,j);
            ++W;
        }
    }

    printf("%d\n",bin_search(src));

    return 0;
}
