/*
 Created By: Malvika Joshi
 Problem: Cow Baseball (December-2013 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=359
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

#define MAXN 1010

using namespace std;

vector<int> throw_dist[MAXN];
int pos[MAXN];
int N;

int main(){
    int i,j;
    scanf("%d",&N);

    for(i = 0; i < N; ++i){
        scanf("%d",&pos[i]);
    }

    sort(pos,pos+N);

    for(i = 0; i < N; ++i){
        for(j = i+1; j < N; ++j){
            throw_dist[i].push_back(pos[j]-pos[i]);
        }
    }

    int total,tmp;
    total = 0;
    for(i = 0; i < N; ++i){
        for(j = i+1; j < N; ++j){
            tmp = upper_bound(throw_dist[j].begin(),throw_dist[j].end(),2*(pos[j]-pos[i])) -
                lower_bound(throw_dist[j].begin(),throw_dist[j].end(), pos[j]-pos[i]);
            total += tmp;
        }
    }

    printf("%d\n",total);
    return 0;
}
