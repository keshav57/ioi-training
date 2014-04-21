/*
 Created By: Malvika Joshi
 Problem: Lemon Tale
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1513
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

#define MAXD 3050
#define MAXN 10010

using namespace std;

struct bignum {
    char digit[MAXD];
    int len;

    void init(){
    	memset(digit,0,sizeof(char)*MAXD);
    	len = 0;
    }

    void print(){
    	int i;
    	for(i = len-1; i >= 0; --i){
    		printf("%d",digit[i]);
    	}
    	printf("\n");
    }

    bignum& operator +=(const bignum& rhs){
    	char carry;
    	int i,nlen;

    	carry = 0;
    	nlen = max(len,rhs.len);
    	for(i = 0; i < nlen; ++i){
    		digit[i] += carry+rhs.digit[i];
    		carry = 0;
    		if(digit[i] < 10) continue;
    		carry = 1;
    		digit[i] -= 10;
    	}

    	if(carry) digit[nlen++] = 1;
    	len = nlen;

    	return *this;
    }

    bignum& operator -=(const bignum& rhs){
    	char borrow;
    	int i;

    	assert(rhs.len <= len);

    	borrow = 0;
    	for(i = 0; i < len; ++i){
    		digit[i] -= (borrow+rhs.digit[i]);
    		borrow = 0;
    		if(digit[i] >= 0) continue;
    		borrow = 1;
    		digit[i] += 10;
    	}

    	assert(!borrow);
    	while(len && !digit[len-1]) --len;

    	return *this;
    }
};

bignum num_ways[MAXN];
int N,K;

void dp(){

	int i;
	bignum last_k;

	for(i = 0; i < N; ++i) num_ways[i].init();

	num_ways[0].digit[num_ways[0].len++] = 1;
	last_k = num_ways[0];

	for(i = 1; i <= N && i <= K; ++i){
		num_ways[i] = num_ways[i-1];
		num_ways[i] += num_ways[i-1];
		last_k += num_ways[i];
	}

	for(i = K+1; i <= N; ++i){
		num_ways[i] = last_k;
		last_k += num_ways[i];
		last_k -= num_ways[i-K-1];
	}
}

int main(){

	scanf("%d%d",&N,&K);
	dp();
	num_ways[N].print();

	return 0;
}
