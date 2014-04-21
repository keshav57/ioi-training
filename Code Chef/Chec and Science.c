/*
 Created By: Malvika Joshi
 Problem: CHITHH
 Link: http://www.codechef.com/problems/CHITHH
*/

#include <stdio.h>
#include <string.h>

#define MAXN 100000
#define MAXV2 500

int len[MAXN+2];
int pre[MAXN+2][MAXV2+2];
char str[MAXN+2][10];
int N,M;

void init(){
	int v,i;

	for(v = 0; v < MAXV2; ++v){
		//v is actually v+1
		for(i = 0; i < v+1; i++){
			pre[i][v] = len[i];
		}
		for(;i < N; i++){
			pre[i][v] = pre[i-v-1][v] + len[i];
		}
	}
}

int bin(int l, int gap,int k){
	int high,low,mid,s,i;

	s = l%gap;
	low = l/gap;
	high = N/gap;
	k += l == s ? 0 : pre[l-gap][gap-1];

	if(high*gap + s >= N) --high;
	if(k >= pre[high*gap+s][gap-1]) return 0;

	while(low <= high){
		mid = (high+low)/2;
		if(pre[mid*gap+s][gap-1] > k){
			high = mid-1;
		}else{
			low = mid+1;
		}
	}

	i = low*gap+s;
	k -= i == s ? 0 : pre[i-gap][gap-1];
	printf("%c\n",str[i][k]);

	return 1;
}

void lin(int s, int gap, int k){
	int i = s;

	while(i < N){
		if(k < len[i]){
			printf("%c\n",str[i][k]);
			return;
		}
		k -= len[i];
		i += gap;
	}

	printf("So sad\n");
}

int main(){
	int i,l,v,k;
	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%s",str[i]);
		len[i] = strlen(str[i]);
	}

	init();
	scanf("%d",&M);

	while(M--){
		scanf("%d%d%d",&l,&v,&k);
		if(v > MAXV2){
			lin(l-1,v,k-1);
			continue;
		}
		if(bin(l-1,v,k-1)) continue;
		printf("So sad\n");
	}

	return 0;
}
