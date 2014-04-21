/*
 Created By: Malvika Joshi
 Problem: LEAFEAT
 Link: http://opc.iarcs.org.in/index.php/problems/LEAFEAT
*/

#include <stdio.h>

unsigned gcd(unsigned a, unsigned b) {
    unsigned r;
    while(b) {
        r = a%b;
        a = b;
        b = r;
    }
    return a;
}

unsigned recur(unsigned *arr, unsigned len, unsigned idx, unsigned cumul, unsigned bound) {
    if (idx >= len || bound == 0) {
        return bound;
    }
    unsigned i, g, s = arr[idx], result;
    g = s/gcd(cumul,s);
    result = bound/g;
    for(i = idx+1; i < len; ++i) {
        result -= recur(arr, len, i, cumul*g, bound/g);
    }
    return result;
}

unsigned inex(unsigned *arr, unsigned len, unsigned bound) {
    unsigned i, result = bound, t;
    for(i = 0; i < len; ++i) {
        result -= recur(arr, len, i, 1, bound);
    }
    return result;
}


int main(){
        unsigned N;
        unsigned L;
        unsigned i;
        unsigned S[30];
        scanf("%u%u",&L,&N);

        for(i = 0;i < N; i++){
                scanf("%u",&S[i]);
        }

        printf("%u",inex(S,N,L-1));
        return 0;
}
