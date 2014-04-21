/*
 Created By: Malvika Joshi
 Problem: Nudnik Photographer
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1260
*/

#include  <stdio.h>

int A[60];
int N;

int DP(void){
    int i;
    A[0] = 0;
    A[1] = 1;
    A[2] = 1;

    for(i = 3; i<= N; ++i){
        A[i] = A[i-1] + A[i-3] + 1;
    }

    return A[N];
}

int main(void){
    scanf("%d",&N);
    printf("%d",DP());
    return 0;
}
