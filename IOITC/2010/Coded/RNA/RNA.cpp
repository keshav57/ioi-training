/*
 Created By: Malvika Joshi
 Problem: RNA (IOITC-2010 Test 4)
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

#define MAXN 2510

using namespace std;

char seq0[MAXN];
char par0[MAXN];

vector<int> bal[MAXN];

char seq1[MAXN];
char par1[MAXN];

int lcs_seq[MAXN][MAXN];
int lcs_par[MAXN][MAXN];
int N,M;

void DP(char *A, char *B, int (&lcs)[MAXN][MAXN]){
    int i, j;

    for(i = 0; i < M; ++i) lcs[i][N-1] = (A[i] == B[N-1]);
    for(j = 0; j < N; ++j) lcs[M-1][j] = (A[M-1] == B[j]);

    for(i = M-2; i >= 0; --i){
        for(j = N-2; j >= 0; --j){
            if(A[i] != B[j]) continue;
            lcs[i][j] = lcs[i+1][j+1]+1;
        }
    }
}

void balance(){
    int i,k,op,cl;

    for(i = 0; i < M; ++i){
        op = cl = 0;
        bal[i].push_back(0);

        for(k = 0; i+k < M; ++k){
            op += par0[i+k] == '(';
            cl += par0[i+k] == ')';
            if(cl < op) continue;
            if(cl > op) break;
            bal[i].push_back(k+1);
        }

    }
}

int lcss(int i, int j){
    int lim,k;
    lim = min(lcs_par[i][j], lcs_seq[i][j]);
    k = upper_bound(bal[i].begin(),bal[i].end(),lim) - bal[i].begin();
    k -= 1;

    return bal[i][k];
}

int main(){
    int i,j,lcs;

    scanf("%d%d",&M,&N);

    scanf("%s%s%s%s",seq0,par0,seq1,par1);

    DP(seq0,seq1,lcs_seq);
    DP(par0,par1,lcs_par);

    balance();

    lcs = 0;
    for(i = 0; i < M; ++i){
        for(j = 0; j < N; ++j){
            lcs = max(lcs,lcss(i,j));
        }
    }

    printf("%d\n",lcs);

    return 0;
}
