/*
 Created By: Malvika Joshi
 Problem: Binary Codes (IOITC-2010 Test-2)
*/

#include <algorithm>
#include <cstdio>
#define MAXN 1000010

using namespace std;

int next[MAXN];
char first[MAXN];
char last[MAXN];

int N;

int order(){
	int i,cur;

	cur = 0;

	for(i = 0; i < N; ++i){
		if(last[i]) continue;
		next[cur++] = i;
	}

	for(i = 0; i < N; ++i){
		if(!last[i]) continue;
		next[cur++] = i;
	}

	return next[0];
}

int main(){
	int i,zero,one;

	scanf("%d",&N);

	zero = one = 0;
	for(i = 0; i < N; ++i){
		scanf(" %c",&last[i]);
		last[i] -= '0';
		zero += !last[i];
		one += last[i];
	}

	while(one--){
		first[one+zero] = 1;
	}


	i = order();
	printf("%d",last[i]);

	while(i){
		i = next[i];
		printf(" %d",last[i]);
	}

	printf("\n");

	return 0;
}

