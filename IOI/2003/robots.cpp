#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

#define TIME 12
#define NMAX 24
#define GMAX 12
#define VMAX NMAX*NMAX*NMAX*NMAX*TIME
#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

int N[2],M[2];

/*
 N:0
 W:1
 S:2
 E:3
*/

const point adj[4] = { make_pair(-1,0), make_pair(0,-1), make_pair(1,0), make_pair(0,1) };

inline int boundary(point pos, int maze){
	return (pos.x < 1 || pos.y < 1 || pos.x > M[maze] || pos.y > N[maze]);
}

point gpos[GMAX][2];
int len[GMAX][2];
int dir[GMAX][2];
int G[2];

char board[NMAX][NMAX][2];

int valid[5][NMAX][NMAX][TIME+2][2];

int ch;
inline point get_pos(int guard, int time, int maze){

	int t,d;
	point pos;

	pos = gpos[guard][maze];
	d = dir[guard][maze];

	time %= (2*len[guard][maze]-2);
	if(time < 0) time += (2*len[guard][maze]-2);
	t = min(len[guard][maze]-1,time);

	pos.x += (t*adj[d].x);
	pos.y += (t*adj[d].y);

	time -= t;
	d = (d+2)%4;

	pos.x += (time*adj[d].x);
	pos.y += (time*adj[d].y);

	return pos;
}

int is_valid(int rel, point pos, int time, int maze){
	if(valid[rel+1][pos.x][pos.y][time][maze] >= 0) return valid[rel+1][pos.x][pos.y][time][maze];

	int i;

	valid[rel+1][pos.x][pos.y][time][maze] = 0;

	point guard_old, guard,old;

	old = rel < 0 ? pos : make_pair(pos.first-adj[rel].x,pos.second-adj[rel].y);

	for(i = 0; i < G[maze]; ++i){
		guard = get_pos(i,time,maze);
		guard_old = get_pos(i,time-1,maze);
		if(guard == pos) return 0;
		if(guard_old == pos && guard == old) return 0;			//cross
	}

	valid[rel+1][pos.x][pos.y][time][maze] = 1;
	return 1;
}

point robot_pos(point pos, int time, int maze, int d){
	ch = 0;
	if(boundary(pos,maze)) return pos;

	point old;

	old = pos;

	pos.x += adj[d].x;
	pos.y += adj[d].y;

	if(!boundary(pos,maze) && board[pos.x][pos.y][maze] == '#') return old;

	ch = 1;
	return pos;
}

struct vertex{
	point pos[2];
	int time;
};

vertex Q[VMAX];
int H,T;
short dist[NMAX][NMAX][NMAX][NMAX][TIME];
char prev[NMAX][NMAX][NMAX][NMAX][TIME];
vertex prev_vertex[NMAX][NMAX][NMAX][NMAX][TIME];
vertex tar;

short bfs(vertex src){
	vertex u,v;
	int i;
	memset(dist,-1,sizeof(short)*VMAX);
	memset(prev,-1,sizeof(char)*VMAX);

	Q[T++] = src;
	dist[src.pos[0].x][src.pos[0].y][src.pos[1].x][src.pos[1].y][src.time] = 0;

	while(H < T){
		u = Q[H++];

		if(boundary(u.pos[0],0) && boundary(u.pos[1],1)){
			tar = u;
			return dist[u.pos[0].x][u.pos[0].y][u.pos[1].x][u.pos[1].y][u.time];
		}

		for(i = 0; i < 4; ++i){
			v.time = (u.time+1)%TIME;
			v.pos[0] = robot_pos(u.pos[0],v.time,0,i);
			if(!is_valid((ch ? i : -1),v.pos[0],v.time,0)) continue;
			v.pos[1] = robot_pos(u.pos[1],v.time,1,i);
			if(!is_valid((ch ? i : -1),v.pos[1],v.time,1)) continue;
			if(dist[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time] >= 0) continue;
			dist[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time] = \
					dist[u.pos[0].x][u.pos[0].y][u.pos[1].x][u.pos[1].y][u.time] + 1;

			prev[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time] = i;
			prev_vertex[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time] = u;


			Q[T++] = v;
		}
	}

	return -1;
}

char dkey[4] = { 'N', 'W', 'S', 'E'};

void print(vertex v){
	int d = prev[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time];

	if(d < 0) return;


	print(prev_vertex[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time]);


	printf("%c\n",dkey[d]);
}

int main(){
	int i,j,b;
	vertex st;
	char c;

	memset(valid,-1,sizeof(valid));

	for(b = 0; b < 2; ++b){
		scanf("%d%d",&M[b],&N[b]);

		for(i = 1; i <= M[b]; ++i){
			for(j = 1; j <= N[b]; ++j){
				scanf(" %c",&board[i][j][b]);
				if(board[i][j][b]^'X') continue;
				board[i][j][b] = '.';
				st.pos[b] = make_pair(i,j);
			}
		}

		scanf("%d",&G[b]);

		for( i= 0; i < G[b]; ++i){
			scanf("%d%d%d %c",&gpos[i][b].x,&gpos[i][b].y,&len[i][b],&c);
			dir[i][b] = (c == 'E' ? 3 : (c == 'S' ? 2 : c == 'W'));
		}
	}

	st.time = 0;

	i = bfs(st);
	printf("%d\n",i);

	if(i == -1) exit(0);

	print(tar);

	return 0;
}
