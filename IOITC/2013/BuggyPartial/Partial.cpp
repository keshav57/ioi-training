/*
 Created By: Malvika Joshi
 Problem: Partial Series (IOITC-2013 Test-4)
*/

#include <algorithm>
#include <iostream>
#include <cstdio>

#define MAXN 15
#define SHIFT (1<<15)
#define MAXM 52
#define INF 100

using namespace std;

int A[MAXN+2];
int P[MAXM+2];
int index[MAXN];
int mem[SHIFT+10][MAXN+2][3];
pair<int,int> prev[SHIFT+10][MAXN+2][3];
int N,M,B;

void init(){

    int i,b,s;
    sort(A,A+N);

    b = 0;
    for(i =0; i < M; ++i){
        if(P[i] > 0) continue;
        index[b++] = i;
    }

    B = b;

    for(s = 0; s < (1<<N); ++s){
        for(i = 0; i < N; ++i){
            for(b = 0; b < 3; ++b) mem[s][i][b] = -1;
        }
    }

}

int min_extrema(int S, int k, int b){

    if(mem[S][k][b] != -1) return mem[S][k][b];

    mem[S][k][b] = INF;

    int i,j,k_,e,n,rel,tmp,b_;

    j = N-__builtin_popcount(S)-1;
    i = index[j];
    n = index[j+1];

    if(i<M-1 && P[i+1] != -1){
        rel = P[i+1] == A[k] ? 2 : A[k] < P[i+1];
        if(rel != b) return mem[S][k][b];
    }

    if(j == B-1){
        e = 0;
        if(i < M-2 && b != 2 && P[i+2] < P[i+1] == b) ++e;
        mem[S][k][b] = e;
        return mem[S][k][b];
    }


    for(k_ = 0; k_ < N; ++k_){
        if(!(S&(1<<k_))) continue;
        if(n == i+1){
           rel = A[k_] == A[k] ? 2 : A[k] < A[k_];
           if(rel != b) continue;
        }

        for(b_ = 0; b_ < 3; ++b_){
            if(n == M-1 && b_ != 2) continue;

            e = 0;
            if(n == i+1 && b_ != 2 && b != 2) e += (b^b_);
            else if(n < M && n == i+2){
                if(b != 2 && A[k_] < P[i+1] == b) ++e;
                if(b_ != 2 && A[k_] < P[i+1] == b_) ++e;
            }
            else{
                if(P[i+2] < P[i+1] == b) ++e;
                if(A[k_] < P[n-1] == b_) ++e;
            }

            tmp = min_extrema(S^(1<<k_),k_,b_)+e;

            if(tmp < mem[S][k][b]){
                mem[S][k][b] = tmp;
                prev[S][k][b] = make_pair(k_,b_);
            }
        }
    }

    return mem[S][k][b];
} 

void print(int S, int k,int b){

    int i,j;

    i = N-__builtin_popcount(S)-1;

    if(i == B-1){
        printf("%d ",A[k]);
        for(j = index[i]+1; j < M; ++j) printf("%d ",P[j]);

   
     printf("\n");
        return;
    }

    printf("%d ",A[k]);
    for(j = index[i]+1; j < index[i+1]; ++j) printf("%d ",P[j]);
    pair<int,int> tmp = prev[S][k][b];
    print(S^(1 << tmp.first),tmp.first,tmp.second);
}

int main(){
    int i,b,best,S,e,tmp;
    pair<int,int> start;
    scanf("%d%d",&M,&N);

    for(i =0 ; i < M; ++i) scanf("%d",&P[i]);
    for(i= 0; i <  N; ++i) scanf("%d",&A[i]);

    init();

    int idx = index[0];
    best = INF;

    S = (1<<N)-1;
    for(i = 0; i < N; ++i){
        for(b = 0; b < 3; ++b){
            e = 0;

            if(idx && A[i] < P[idx-1] == b) ++e;
            if(idx-1 > 0 && ((P[idx-1] > A[i] && P[idx-1] > P[idx-2]) || (P[idx-1] < A[i] && P[idx-1] < P[idx-2]))) ++e;
            tmp = min_extrema(S^(1<<i),i,b)+e;
            if(tmp < best){
                best = tmp;
                start = make_pair(i,b);
            }
        }
    }

    for(i = 0; i < idx; ++i) printf("%d ",P[i]);
    print(S^(1<<start.first),start.first,start.second);

    return 0;
}
