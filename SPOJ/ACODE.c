/*
 Created By: Malvika Joshi
 Problem: Alphacode
 Link: http://www.spoj.com/problems/ACODE/
*/

#include <stdio.h>
#include <string.h>

#define MAXN 5010

typedef long long lli;

char enc[MAXN];
lli dec[MAXN];
int N;

lli decode(){
	int i;

	dec[0] = 1LL;

	for(i = 1; i < N; ++i){
		dec[i] = 0LL;
		if(enc[i]) dec[i] = dec[i-1];
		if(!enc[i-1] || enc[i-1]*10+enc[i] > 26) continue;
		dec[i] += i-1 ? dec[i-2] : 1LL;
	}

	return dec[N-1];
}

int main(){

	int i;

	while(1){
		scanf("%s",enc);
		if(!(enc[0]-'0')) break;
		N = strlen(enc);
		for(i = 0; i < N; ++i) enc[i] -= '0';
		printf("%lld\n",decode());
	}

	return 0;
}
