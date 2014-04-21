/*
 Created By: Malvika Joshi
 Problem: Hyper Mall (IOITC-2010 Final 2)
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>

#define MAXN 110
#define MAXK 52

using namespace std;

int free_time[MAXK];
pair<int,int> det[MAXN];
int N,K;

int main(){

    int i,cur_time,counter,k;

    scanf("%d%d",&N,&K);

    for(i = 0; i < N; ++i){
        scanf("%d%d",&det[i].first,&det[i].second);
    }

    sort(det,det+N);


    for(i = 0; i < N; ++i){

        cur_time = det[i].first;
        counter = 0;

        for(k = 0; k < K; ++k){
            if(free_time[k] <= cur_time) break;
            if(free_time[k] < free_time[counter]) counter = k;
        }

        counter = k < K ? k : counter;

        free_time[counter] = max(free_time[counter],cur_time)+det[i].second;
    }


    printf("%d\n",*max_element(free_time,free_time+K));

    return 0;
}
