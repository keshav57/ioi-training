#include"tile.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <numeric>

using namespace std;


inline int in_range(int x1, int y1, int x2, int y2, int i, int j){
	return ((i >= x1 && i <= x2) && (j >= y1 && j <= y2));
}

int T;

void place(int n, int x, int y, int pos[][6], int inci, int incj){
//	cout << n << " " << x << " " << y << endl;
	if(n <= 1){
		return;
	}

	int i;

	int top[4][2] = { {0,0} , {0,n/2} , {n/2,0}, {n/2,n/2} };
	int bottom[4][2] = { {n/2-1,n/2-1},{n/2-1,n-1},{n-1,n/2-1},{n-1,n-1} };
	int block[4][2] = { {n/2-1, n/2-1} , {n/2-1,n/2}, {n/2,n/2-1} , {n/2,n/2} };
	int tile[4] = {0};

	for(i =0 ; i < 4; ++i){
		tile[i] = in_range(top[i][0],top[i][1],bottom[i][0],bottom[i][1],x,y);
	}

	assert(accumulate(tile,tile+4,0) == 1);

	for(i = 0; i < 4; ++i){
		place(n/2, (tile[i] ? x : block[i][0])-top[i][0], (tile[i] ? y : block[i][1])-top[i][1] , pos, inci+top[i][0], incj+top[i][1] );
	}

	int k = 0;
	for(i = 0; i < 4; ++i){
		if(tile[i]) continue;
		pos[T][k++] = block[i][1]+incj;
		pos[T][k++] = block[i][0]+inci;
	}
	++T;
}


void placeTile(int n, int x, int y, int pos[][6]){
	int i,j;

	i = (1<<n)-y-1;
	j = x;

	place(1<<n,i,j,pos,0,0);

	int k;
	for(i = 0; i < T; ++i){
		for(k = 1; k < 6; k += 2){
			pos[i][k] = (1<<n)-pos[i][k]-1;
		}

		for(k = 0; k < 6; ++k){
			++k;
		}
	}
}

