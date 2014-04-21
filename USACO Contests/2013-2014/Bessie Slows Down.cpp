/*
 Created By: Malvika Joshi
 Problem: Bessie Slows Down (January-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=379
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

#define MAXN 10010

using namespace std;

vector<double> dch,tch;
int N;

double compute(){

    double cdist,time,dist,speed,ctime;
    int i,j,k;

    cdist = 0;
    ctime = 0;
    k = 1;
    speed = 1;

    i =j=0;
    while(i < dch.size() || j < tch.size()){
        ++k;
        time = dist = -1;

        if(i < dch.size()) time = (dch[i]-cdist)/speed;
        if(j < tch.size()) dist = (tch[j]-ctime)*speed;

        if(dist >= 0 && (time < 0 || dist+cdist < dch[i])){
            ctime = tch[j];
            cdist += dist;
            speed = 1.0/k;
            ++j;
        }else{
            ctime += time;
            cdist = dch[i];
            speed = 1.0/k;
            ++i;
        }
    }

    time = (1000-cdist)/speed;
    ctime += time;

    return ctime;
}

int main(){
    int i,k;
    char ch;

    freopen("slowdown.in","r",stdin);
    freopen("slowdown.out","w",stdout);

    scanf("%d",&N);

    for(i = 0; i < N; ++i){
        scanf(" %c%d",&ch,&k);
        if(ch == 'T') tch.push_back(k);
        else dch.push_back(k);
    }

    sort(dch.begin(),dch.end());
    sort(tch.begin(),tch.end());

    double sol = compute();
    sol = round(sol);
    printf("%d\n",(int)sol);

    return 0;
}
