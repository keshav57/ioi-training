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
typedef pair<int,int> pt;

//directions N = 0,1 ;  E =

const pt forward[4] =  { make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
const pt right[4] = { make_pair(1,0), make_pair(0,-1), make_pair(-1,0), make_pair(0,1) };

int dir[MAXN];
pt pos[MAXN];

pt endpts[MAXN*3];
char cmd[MAXN];		//0 forward, 1 right, -1 left
int N,M;

void init(){
	int i;

	for(i = 1; i < N; i++){
		dir[i] = dir[i-1];
		pos[i] = pos[i-1];

		if(cmd[i]){
			dir[i] = dir[i] + cmd[i];
			dir[i] = dir[i] < 0 ? 3 : (dir[i] > 3 ? 0 : dir[i]) ;
		}else{
			pos[i].x += forward[dir[i]].x;
			pos[i].y += forward[dir[i]].y;
		}

	}
}

void end_at(int i){
	int fwd,rht,tdir;
	pt tpos;
	char cmd2;

	fwd = (pos[N-1].y-pos[i].y)*forward[dir[i]].y + (pos[N-1].x-pos[i].x)*forward[dir[i]].x;
	rht = (pos[N-1].x-pos[i].x)*right[dir[i]].x + (pos[N-1].y-pos[i].y)*right[dir[i]].y;

	for(cmd2 = -1; cmd2 < 2; ++cmd2){
		if(cmd2 == cmd[i]) continue;

		tdir = dir[i-1];
		tpos = pos[i-1];

		if(cmd2){
			tdir = tdir + cmd2;
			tdir = tdir < 0 ? 3 : (tdir > 3 ? 0 : tdir);
		}else{
			tpos.x += forward[tdir].x;
			tpos.y += forward[tdir].y;
		}

		tpos.x += fwd * forward[tdir].x + rht * right[tdir].x;
		tpos.y += fwd * forward[tdir].y + rht * right[tdir].y;

		endpts[M++] = tpos;

	}
}

int main(){
	int i;
	scanf("%s",cmd+1);
	cmd[0] = '#';
	N = strlen(cmd);

	for(i = 1; i < N; i++) cmd[i] = cmd[i] == 'L' ? -1 : cmd[i] == 'R';

	init();

	for(i = 1; i < N; i++) end_at(i);

	int c = 0;
	sort(endpts,endpts+M);
	for(i = 0; i < M; i++){
		if(i && endpts[i] == endpts[i-1]) continue;
		++c;
	}

	printf("%d\n",c);
}

