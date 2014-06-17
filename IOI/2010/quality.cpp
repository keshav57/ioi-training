#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 3010

using namespace std;

int pref[NMAX][NMAX];
int A[NMAX][NMAX];
int M,N,H,W;

void init(){
	int i,j;

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			pref[i][j] += (i ? pref[i-1][j] : 0) + (j ? pref[i][j-1] : 0) \
					- (i && j ? pref[i-1][j-1] : 0);
 		}
	}
}

inline int sum(int i, int j, int k, int l){
	return (pref[k][l] - (i ? pref[i-1][l] : 0) - (j ? pref[k][j-1] : 0)\
			+ (i && j ? pref[i-1][j-1] : 0) );
}

int pos(int k){
	int i,j;

	for(i = 0; i < M; ++i){
		for(j =0 ; j < N; ++j){
			pref[i][j] = A[i][j] <= k;
		}
	}

	init();

	for(i = 0; i+H <= M; ++i){
		for(j = 0; j+W <= N; ++j){
			if(sum(i,j,i+H-1,j+W-1) > (H*W)/2) return 1;
		}
	}

	return 0;
}

int search(){
	int low,high,mid;

	low = 0;
	high = N*M-1;

	while(low < high){
		mid = (high+low)/2;

		if(pos(mid)){
			high = mid;
		}else{
			low = mid+1;
		}
	}

	return low+1;
}

int main(){
	int i,j;

	scanf("%d%d%d%d",&M,&N,&H,&W);

	for(i =0 ; i < M; ++i){
		for(j =0 ; j < N; ++j){
			scanf("%d",&A[i][j]);
			--A[i][j];
		}
	}

	printf("%d\n",search());

	return 0;
}
