/*
 Created By: Malvika Joshi
 Problem: Table Sum (INOI-2012)
 Link: http://www.iarcs.org.in/inoi/2012/inoi2012/inoi2012-qpaper.pdf
*/

#include <stdio.h>

int N;
int A[200000];
int M[200000];

int main(){
    int i,m,cur,j,o_max,max_i;

    scanf("%d",&N);

    for(i = 0;i < N; i++){
        scanf("%d",&A[i]);
        A[i] = A[i]+i+1;
    }

    m = 0;
    cur = 0;
    M[0] = 0;

    for(i = 1;i < N; i++){
        if(A[i] > A[cur]){
            m++;
            M[m] = i;
            cur = i;
        }
    }

    o_max = A[cur] - N;
    max_i = cur;

    for(i = N-1,j = 0;i >=0;i --,j++){
        printf("%d ", A[cur]+j);

        A[i] = A[i] - N;

        if(i == cur){
            if (A[i] < o_max) {
                cur = max_i;
            } else if(m > 0 && A[i] < A[M[m-1]]){
                cur = M[m-1];
                m--;
            }
        }
    }

    return 0;
}
