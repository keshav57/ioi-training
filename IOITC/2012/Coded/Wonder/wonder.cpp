/*
 Created By: Malvika Joshi
 Problem: Wonder (IOITC-2012 Test-6)
*/

#include <stdio.h>
#include <iostream>
#include "wonderlib.h"


using namespace std;

#define MAXN 2020

int hpath[MAXN];
int N,S;

void insert(int pos){
    int i;

    for(i = S; i > pos; --i){
        hpath[i] = hpath[i-1];
    }
    ++S;
    hpath[i] = S;
}

int bin_search(int tar){
    int high,low,mid;

    low = 0;
    high = S-1;

    while(low <= high){
        mid = low + (high-low)/2;
        if(prefer(hpath[mid],tar+1)){
            low = mid+1;
        }else{
            high = mid-1;
        }
    }

    return low;
}

int hamiltonian_path(){
    int i;

    for(i = 0; i < N; ++i){
        insert(bin_search(i));
    }
}

int main(){

    N = init();
    hamiltonian_path();
    solution(hpath);

    return 0;
}
