/*
 Created By: Malvika Joshi
 Problem: Wrong Directions (March-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=123
*/

#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 100010
#define x first
#define y second

using namespace std;
//typedef pair<int,int> pt;

char dir[MAXN];
pair<int,int> pos[MAXN];
pair<int,int> ends[3*MAXN];
char cmd[MAXN];
int N,M;

void init(){
	int i;

	dir[0] = 'N';
	pos[0] = make_pair(0,0);

	for(i = 1; i < N; i++){
		dir[i] = dir[i-1];
		pos[i] = pos[i-1];


		if(dir[i] == 'N'){
			if(cmd[i] == 'R') dir[i] = 'E';
			if(cmd[i] == 'L') dir[i] = 'W';
			if(cmd[i] == 'F') ++pos[i].y;
		}else if(dir[i] == 'S'){
			if(cmd[i] == 'R') dir[i] = 'W';
			if(cmd[i] == 'L') dir[i] = 'E';
			if(cmd[i] == 'F') --pos[i].y;
		}else if(dir[i] == 'E'){
			if(cmd[i] == 'R') dir[i] = 'S';
			if(cmd[i] == 'L') dir[i] = 'N';
			if(cmd[i] == 'F') ++pos[i].x;
		}else{
			if(cmd[i] == 'R') dir[i] = 'N';
			if(cmd[i] == 'L') dir[i] = 'S';
			if(cmd[i] == 'F') --pos[i].x;
		}
	}
}

void end_at(int i){
	int fwd,side;

	if(dir[i] == 'N'){
		fwd = pos[N-1].y-pos[i].y;
		side = pos[N-1].x-pos[i].x;
	}else if(dir[i] == 'S'){
		fwd = pos[i].y-pos[N-1].y;
		side = pos[i].x-pos[N-1].x;
	}else if(dir[i] == 'E'){
		fwd = pos[N-1].x-pos[i].x;
		side = pos[i].y-pos[N-1].y;
	}else{
		fwd = pos[i].x-pos[N-1].x;
		side = pos[N-1].y-pos[i].y;
	}

	if(dir[i-1] == 'N'){
		//change to F, dir = N
		if(dir[i] != 'N') ends[M++] = make_pair(pos[i-1].x+side,pos[i-1].y+1+fwd);
		//change to R, dir = E
		if(dir[i] != 'E') ends[M++] = make_pair(pos[i-1].x+fwd,pos[i-1].y-side);
		//change to L, dir = W
		if(dir[i] != 'W') ends[M++] = make_pair(pos[i-1].x-fwd,pos[i-1].y+side);
	}else if(dir[i-1] == 'S'){
		//change to F, dir = S
		if(dir[i] != 'S') ends[M++] = make_pair(pos[i-1].x-side,pos[i-1].y-1-fwd);
		//change to R, dir = W
		if(dir[i] != 'W') ends[M++] = make_pair(pos[i-1].x-fwd,pos[i-1].y+side);
		//change to L, dir = E
		if(dir[i] != 'E') ends[M++] = make_pair(pos[i-1].x+fwd,pos[i-1].y-side);
	}else if(dir[i-1] == 'E'){
		//change to F, dir = E
		if(dir[i] != 'E') ends[M++] = make_pair(pos[i-1].x+1+fwd,pos[i-1].y-side);
		//change to R, dir = S
		if(dir[i] != 'S') ends[M++] = make_pair(pos[i-1].x-side,pos[i-1].y-fwd);
		//change to L, dir = N
		if(dir[i] != 'N') ends[M++] = make_pair(pos[i-1].x+side,pos[i-1].y+fwd);
	}else{
		//change to F, dir = W
		if(dir[i] != 'W') ends[M++] = make_pair(pos[i-1].x-1-fwd,pos[i-1].y+side);
		//change to R, dir = N
		if(dir[i] != 'N') ends[M++] = make_pair(pos[i-1].x+side,pos[i-1].y+fwd);
		//change to L, dir = S
		if(dir[i] != 'S') ends[M++] = make_pair(pos[i-1].x-side,pos[i-1].y-fwd);
	}

}

int main(){

	int i;
	scanf("%s",cmd+1);
	cmd[0] = '#';
	N = strlen(cmd);

	init();
	for(i = 1; i < N; i++){
		end_at(i);
	}

	int c = 0;
	sort(ends,ends+M);
	for(i = 0; i < M; i++){
		if(i && ends[i] == ends[i-1]) continue;
		++c;
	}

	printf("%d\n",c);

	return 0;
}
