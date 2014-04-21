/*
 Created By: Malvika Joshi
 Problem: Cars (IOITC-2012 Finals 2)
*/

#include <algorithm>
#include <cstdio>
#include <utility>

#define MAXN 5010

using namespace std;

int happy[MAXN][MAXN];
int slowest[MAXN];
pair<int,int> speed[MAXN];
int N;

void init(){
    int i;

    sort(speed,speed+N);

    for(i = 0 ; i < N; ++i){
        speed[i].first = i;
        swap(speed[i].first,speed[i].second);
    }

    sort(speed,speed+N);

    slowest[0] = N;
    for(i = 1; i <= N; ++i){
        slowest[i] = min(slowest[i-1],speed[i-1].second);
    }
}

int DP(){

    int i,j,t1,t2;

    for(i = N-1; i >= 0; --i){
        for(j = 0; j <= N; ++j){
            if(j < slowest[i]) continue;
            t1 = happy[i+1][j] + (speed[i].second < slowest[i]);
            t2 = happy[i+1][max( min(j,speed[i].second) ,slowest[i] )] + (speed[i].second < j);
            happy[i][j] = max(t1,t2);
        }
    }

    return happy[0][N];
}

int main(){
    int i;

    scanf("%d",&N);

    for(i = 0; i < N; ++i){
        scanf("%d",&speed[i].first);
        speed[i].second = i;
    }

    init();

    printf("%d\n",DP());

    return 0;
}
