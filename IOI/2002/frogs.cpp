#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cassert>

#define NMAX 5010
#define x first
#define y second

using namespace std;

pair<int,int> pos[NMAX];
short path[NMAX][NMAX];
int N,R,C;

int occ[NMAX+NMAX];

int sol(){
	int len,i,j,k,dx,dy;
	pair<int,int> next;

	len = 0;
	for(i = N-1; i >= 0; --i){
		for(j = N-1; j > i; --j){

			dx = pos[j].x-pos[i].x;
			dy = pos[j].y-pos[i].y;
			next = make_pair(pos[j].x+dx,pos[j].y+dy);

			k = lower_bound(pos+occ[next.x-1],pos+N,next)-pos;

			assert(next.x >= 1);
			assert(k > j);

			if(k < N && next == pos[k]){
				path[i][j] = path[j][k]+1;
			}else if(next.x < 1 || next.x > R || next.y < 1 || next.y > C){
				path[i][j] = 1;
			}else{
				path[i][j] = -10000;
			}

			assert(pos[i].x-dx <= R);
			if(pos[i].x-dx < 1 || pos[i].x-dx > R || pos[i].y-dy < 1 || pos[i].y-dy > C){
				len = max(len,(int)path[i][j]);
			}
		}
	}

	return len+1 < 3 ? 0 : len+1;
}

int main(){

	int i;

	scanf("%d%d%d",&R,&C,&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&pos[i].x,&pos[i].y);
		++occ[pos[i].x];
	}

	sort(pos,pos+N);
	for(i = 1; i <= 5000; ++i){
		occ[i] += occ[i-1];
	}

	printf("%d\n",sol());

	return 0;
}

