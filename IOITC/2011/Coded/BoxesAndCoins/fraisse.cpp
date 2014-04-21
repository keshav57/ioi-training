/*
 Created By: Malvika Joshi
 Problem: Boxes And Coins (IOITC-2011 Final-2)
*/

#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long lli;

lli pos[2][65];

lli N0,N1;
int K,move;

void fraisse_start(lli n0, lli n1, int k){
	K = k;
	N0 = n0;
	N1 = n1;
	move = 2;
	pos[0][0] = -1;
	pos[1][0] = -1;
	pos[1][1] = N1;
	pos[0][1] = N0;
}

int nearest(int row, lli box){
	int i,n;
	n = 0;
	for(i = 0; i < move; ++i){
		if(abs(pos[row][i]-box) < abs(pos[row][n]-box))	n = i;
	}


	return n;
}


lli fraisse_turn(int row, lli box){

	int place_row,near;
	lli dist;
	place_row = row^1;

	near = nearest(row,box);
	dist = pos[row][near] - box;
	pos[row][move] = box;

    if(dist < 0) dist = max(dist,-(1LL<<(K-move+1)));
    if(dist > 0) dist = min(dist,(1LL<<(K-move+1)));

	pos[place_row][move++] = pos[place_row][near]-dist;

	return pos[place_row][move-1];
}

