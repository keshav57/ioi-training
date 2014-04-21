/*
 Created By: Malvika Joshi
 Problem: Landfill (IOITC-2011 Final-3)
*/

#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAXN 110
#define MAXS ((1<<11)+10)
#define INF 100000010
#define MAXH (long long)(1e12)

using namespace std;

typedef long long lli;

int cost[MAXN];
int height[MAXN];
int increase[MAXN];

int mem[MAXN][MAXS];

lli H;
int N,K,C;

int min_cost(int i, int mod){
	if(i >= N) return 0;
	if(mem[i][mod] > -1) return mem[i][mod];
	mem[i][mod] = INF;

	lli new_height = height[i];
	int k,prev,mod1;

	prev = i-K+1;

	for(k = 0; k < K-1; ++k){
		if(!(mod&(1<<k))) continue;
		new_height += increase[prev+k];
	}

	if(new_height+increase[i] < H) return mem[i][mod];

	mod1 = (mod>>1);
	if(new_height >= H) mem[i][mod] = min_cost(i+1,mod1);

	if(K-2 >= 0) mod1|=(1<<(K-2));
	mem[i][mod] = min(mem[i][mod],min_cost(i+1,mod1)+cost[i]);

	return mem[i][mod];
}

void init(){
	int i,k;

	for(i = 0; i < MAXN; ++i){
		for(k = 0; k < MAXS; ++k){
			mem[i][k] = -1;
		}
	}
}

lli search(){
	lli high,low,mid;

	high = MAXH;
	low = 0;

	while(low < high){
		mid = (low+high+1)/2;
		init();
		H = mid;
		if(min_cost(0,0) > C){
			high = mid-1;
		}else{
			low = mid;
		}
	}

	return low;
}

int main(){

	int i;

	scanf("%d%d%d",&N,&C,&K);

	for(i = 0; i < N; ++i){
		scanf("%d%d%d",&height[i],&increase[i],&cost[i]);
	}

	printf("%lld\n",search());

	return 0;
}
