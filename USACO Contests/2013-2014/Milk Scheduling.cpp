/*
 Created By: Malvika Joshi
 Problem: Milk Scheduling (December-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=361
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

#define MAXN 10010
#define MAXT 10010

using namespace std;


int max_milk[MAXT];
pair<int,int> det[MAXN];      //first is time, second is milk
int N,T;

int DP(){
    int i,k;

    for(k = 2; k <= T; ++k){
        max_milk[k] = det[0].second;
    }

    for(i = 1; i < N; ++i){
        for(k = T; k >= 2; --k){
            max_milk[k] = max(max_milk[k],max_milk[min(k-1,det[i].first)] + det[i].second);
        }
    }

    return max_milk[T];
}

int main(){
    int i;

    freopen("msched.in","r",stdin);
    freopen("msched.out","w",stdout);

    scanf("%d",&N);
    for(i = 0; i < N; ++i) scanf("%d%d",&det[i].second,&det[i].first);

    sort(det,det+N);
    T = det[N-1].first+1;

    printf("%d\n",DP());

    return 0;
}
