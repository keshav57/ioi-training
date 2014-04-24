/*
 Created By: Malvika Joshi
 Problem: Figure Eight (US-Open 2013 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=287
*/

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#define NMAX 310

#define INF 3000

using namespace std;

short max_below[NMAX][NMAX][NMAX];
short max_top[2][NMAX][NMAX];
int max_inside[NMAX][NMAX];

int N;

int diamond[NMAX][NMAX];

void init(){
	int i,j,k,spoilt;

	for(i =0 ; i < N; ++i){
		for(j = 0; j < N; ++j){
			for(k = 0;k < N; ++k){
				max_below[i][j][k] = -INF;
			}
		}
	}

	for(i = N-1; i>= 0; --i){
		for(j = 0; j < N; ++j){
			spoilt = diamond[i][j];
			for(k = j+1; k < N; ++k){
				spoilt |= diamond[i][k];
				if(!spoilt) max_below[i][j][k] = 0;
				if(i < N-1 && !diamond[i][j] && !diamond[i][k]) max_below[i][j][k] = max(max_below[i][j][k]+0,max_below[i+1][j][k]+1);
			}
		}
	}
}

int spoilt[NMAX];

long long compute(){
	int i,j,k,d;
	long long area;
	area = 0;

	for(i = 0; i < N ; ++i){
		for(j = 0; j < N; ++j) spoilt[j] = diamond[i][j];
		for(d = 1; d < N; ++d){
			for(j = 0; j+d < N; ++j){
				k = j+d;
				spoilt[j] |= diamond[i][k];

				max_top[i&1][j][k] = -INF;
				if(!spoilt[j]) max_top[i&1][j][k] = 0;

				if(i && !diamond[i][j] && !diamond[i][k]) max_top[i&1][j][k] = max(max_top[i&1][j][k]+0,max_top[!(i&1)][j][k]+1);

				max_inside[j][k] = -INF*INF;
				if(spoilt[j]) continue;
				if(d-1) max_inside[j][k] = max(max_inside[j+1][k],max_inside[j][k-1]);
				max_inside[j][k] = max(max_inside[j][k],(max_top[i&1][j][k]-1)*(d-1));
				if(max_inside[j][k] <= 0) continue;

				area = max(area,1LL*max_inside[j][k]*(max_below[i][j][k]-1)*(d-1));
			}
		}
	}

	return area ? area : -1;
}

int main(){
	int i,j;
	char c;

	scanf("%d",&N);

	for(i =0 ; i < N; ++i){
		for(j =0 ; j < N; ++j){
			scanf(" %c",&c);
			diamond[i][j] = c == '*';
		}
	}

	init();

	printf("%lld\n",compute());

	return 0;
}




