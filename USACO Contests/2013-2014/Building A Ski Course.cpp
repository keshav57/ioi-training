/*
 Created By: Malvika Joshi
 Problem: Building A Ski Course (January-2014 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=383
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>

#define NMAX 110

using namespace std;

int square[NMAX][NMAX][2];
int contains[NMAX][NMAX][2];
int N,M;
int mi,mj;

int cur;

int state[NMAX][NMAX];

int init(){
	int i,j,q,b;

	mi = mj = -1;
	cur = 0;

	for(i = M-1; i >= 0; --i){
		square[i][N-1][1] = square[i][N-1][0] = 0;

		if(state[i][N-1] >= 0){
			square[i][N-1][state[i][N-1]] = 1;
			mi = i, mj = N-1;
			cur = 1;
		}
		else square[i][N-1][1] = square[i][N-1][0] = 1;

		for(b = 0; b < 2; ++b){
			contains[i][N-1][b] = contains[i+1][N-1][b]+(state[i][N-1] == b);
		}
	}

	for(j = N-1; j >= 0; --j){
		square[M-1][j][1] = square[M-1][j][0] = 0;

		if(state[M-1][j] >= 0){
			square[M-1][j][state[M-1][j]] = 1;
			mi = M-1, mj = j;
			cur = 1;
		}
		else square[M-1][j][1] = square[M-1][j][0] = 1;

		for(b = 0; b < 2; ++b){
			contains[M-1][j][b] = contains[M-1][j+1][b]+(state[M-1][j] == b);
		}
	}

	for(i = M-2; i >= 0; --i){
		for(j = N-2; j >= 0; --j){

			for(b = 0; b < 2; ++b){
				square[i][j][b] = 0;

				if(state[i][j]^(!b)) square[i][j][b] = min(square[i+1][j+1][b],min(square[i+1][j][b],square[i][j+1][b]))+1;
				contains[i][j][b] = contains[i][j+1][b]+contains[i+1][j][b]-contains[i+1][j+1][b]+(state[i][j] == b);

				q = square[i][j][b];

				if(q > cur && contains[i][j][b]+contains[i+q][j+q][b]-contains[i][j+q][b]-contains[i+q][j][b]){
					mi = i,mj = j,cur = q;
				}
			}
		}
	}

	return cur;
}

int compute(){
	int i,j,q,sq;
	q = init();
	sq = q;

	while(q){
		sq = min(sq,q);
		for(i = mi; i < mi+q; ++i){
			for(j = mj; j < mj+q; ++j){
				state[i][j] = -1;
			}
		}
		q=init();
	}

	return sq;
}

int main(){
	int i,j;
	char c;

	scanf("%d%d",&M,&N);

	for(i = 0; i < M; ++i){
		for(j =0 ; j < N; ++j){
			scanf(" %c",&c);
			state[i][j] = c == 'S';
		}
	}

	printf("%d\n",compute());

	return 0;
}
