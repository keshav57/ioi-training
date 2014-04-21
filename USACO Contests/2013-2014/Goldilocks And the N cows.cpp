/*
 Problem: Goldilocks And the N cows (November-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=341
*/

#include <cstdio>
#include <algorithm>

#define MAXN 20010

using namespace std;

typedef pair<int,int> pii;

int N,X,Y,Z;
pii T[MAXN];
pii stk[(MAXN*2)];
int S = 0;

int main(){
    int i,cur,milk;

    scanf("%d%d%d%d",&N,&X,&Y,&Z);

    for(i = 0; i < N; i++){
        scanf("%d%d",&T[i].first,&T[i].second);
        stk[S++] = make_pair(T[i].first,Y-X);
        stk[S++] = make_pair(T[i].second+1,Z-Y);
   }

    milk = 0;
    cur = N*X;

    sort(stk,stk+S);

    for(i = 0; i < S; i++){
        if(!i || stk[i].first == stk[i-1].first){
            cur += stk[i].second;
            continue;
        }
        milk = max(milk,cur);
        cur += stk[i].second;
    }

    milk = max(milk,cur);

    printf("%d\n",milk);

    return 0;
}
