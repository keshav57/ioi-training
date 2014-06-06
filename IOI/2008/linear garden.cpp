#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>

#define NMAX 1000010

using namespace std;

int pos[NMAX][4][4];
int N,mod;

void dp(){
	int i,mx,mn;

	for(i = N; i >= 0; --i){
		for(mx = 0; mx <= 2; ++mx){
			for(mn = 0; mn <= 2; ++mn){
				if(i == N){
					pos[i][mx][mn] = 1;
					continue;
				}
				pos[i][mx][mn] = pos[i+1][mx+1][max(0,mn-1)]+pos[i+1][max(0,mx-1)][mn+1];
				pos[i][mx][mn] -= pos[i][mx][mn] >= mod ? mod : 0;
			}
		}
	}
}

char str[NMAX];

//L = -1, P = 1;

int get_rank(){
	int rank,i,mx,mn;

	mx = 0, mn = 0;
	rank = 0;
	for(i = 0; i < N; ++i){
		if(str[i] == 'L'){
			mx = max(0,mx-1);
			mn++;
			continue;
		}
		rank += pos[i+1][max(0,mx-1)][mn+1];
		rank -= rank >= mod ? mod : 0;
		mx++;
		mn = max(0,mn-1);
	}

	rank ++;
	rank -= rank >= mod ? mod : 0;

	return rank;
}

int main(){
	scanf("%d%d",&N,&mod);
	scanf("%s",str);
	dp();
	printf("%d\n",get_rank());
	return 0;
}
