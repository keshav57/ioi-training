/*
 Created By: Malvika Joshi
 Problem: Unlocking Blocks (US Open-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=134
*/

#include <cstdio>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;

#define SH 12
#define MAX_REL 30
#define MAX_POS 30
#define MAXN 100

#define x first
#define y second

typedef pair<int,int> point;
typedef pair<point,point> box;
typedef pair<point,point> rel;

int invalid[3][3][MAX_REL+2][MAX_REL+2];
point puzzle[3][MAXN];
int n[MAXN];

box bound_box[3];

inline int overlap(box R1, box R2){
	return (R1.first.x < R2.second.x && R1.second.x > R2.first.x
			&& R1.first.y < R2.second.y && R1.second.y > R2.first.y);
}

void init(int b1, int b2){
	int inc_x, inc_y,i;
	point tmp;

	int taken[MAX_POS][MAX_POS] = {{0}};

	for(i = 0; i < n[b1]; i++) taken[puzzle[b1][i].x+SH][puzzle[b1][i].y+SH] = 1;

	for(inc_x = -12; inc_x <= 12; ++inc_x){
		for(inc_y = -12; inc_y <= 12; ++inc_y){
			for(i = 0; i < n[b2]; ++i){
				tmp = puzzle[b2][i];
				tmp.x +=  inc_x+SH;
				tmp.y += inc_y+SH;

				if(!taken[tmp.x][tmp.y]) continue;
				invalid[b1][b2][inc_x+SH][inc_y+SH] = 1;
				break;
			}
		}
	}
}

rel Q[MAX_REL*MAX_REL*MAX_REL*MAX_REL+5];
int H,T;

rel adj[12] = { make_pair(make_pair(1,0),make_pair(0,0)), make_pair(make_pair(-1,0),make_pair(0,0)), make_pair(make_pair(0,-1),make_pair(0,0)), make_pair(make_pair(0,1),make_pair(0,0)),
		 make_pair(make_pair(0,0),make_pair(1,0)), make_pair(make_pair(0,0),make_pair(-1,0)), make_pair(make_pair(0,0),make_pair(0,-1)), make_pair(make_pair(0,0),make_pair(0,1)),
		 make_pair(make_pair(1,0),make_pair(1,0)), make_pair(make_pair(-1,0),make_pair(-1,0)), make_pair(make_pair(0,-1),make_pair(0,-1)), make_pair(make_pair(0,1),make_pair(0,1))};



map<rel,int> visited;

int box_intersect(box b1, box b2, point rel_pos){

	b2.first.x += rel_pos.x;
	b2.first.y += rel_pos.y;
	b2.second.x += rel_pos.x;
	b2.second.y += rel_pos.y;

	return overlap(b1,b2);
}

int bfs(rel src){

	rel v,u;
	int i,dist,tar;
	point tmp;


	H = 0;
	T = 0;

	Q[T++] = src;
	visited.insert(make_pair(src,0));

	while(H < T){
		v = Q[H++];
		dist = visited[v];
		tar = 0;
		tar |= box_intersect(bound_box[0],bound_box[1],v.first);
		tar |= box_intersect(bound_box[0],bound_box[2],v.second);
		tar |= box_intersect(bound_box[1],bound_box[2],make_pair(v.second.x-v.first.x,v.second.y-v.first.y));


		if(!tar) return dist;


		for(i = 0; i < 12; i++){
			u = v;
			u.first.x += adj[i].first.x;
			u.first.y += adj[i].first.y;
			u.second.x += adj[i].second.x;
			u.second.y += adj[i].second.y;


			if(u.first.x > 30 || u.first.x < -30) continue;
			if(u.first.y > 30 || u.first.y < -30) continue;
			if(u.second.x > 30 || u.second.x < -30) continue;
			if(u.second.y > 30 || u.second.y < -30) continue;
			if(u.second.x-u.first.x > 30 || u.second.x-u.first.x < -30) continue;
			if(u.second.y-u.first.y > 30 || u.second.y-u.first.y < -30) continue;

			if(visited.count(u) >= 1) continue;

			if(abs(u.first.x) <= 10 && abs(u.first.y) <= 10) if(invalid[0][1][u.first.x+SH][u.first.y+SH]) continue;
			if(abs(u.second.x) <= 10 && abs(u.second.y) <= 10) if(invalid[0][2][u.second.x+SH][u.second.y+SH]) continue;
			if(abs(u.second.x-u.first.x) <= 10 && abs(u.second.y-u.first.y) <= 10) if(invalid[1][2][u.second.x-u.first.x+SH][u.second.y-u.first.y+SH]) continue;


			Q[T++] = u;
			visited[u] = dist+1;

		}

	}

	return -1;
}

int main(){

	int i,j;
	point pos[i];

	for(i = 0 ;i < 3; i++){
		scanf("%d",&n[i]);
	}

	for(i = 0; i < 3; i++){
		scanf("%d%d",&pos[i].x,&pos[i].y);
		bound_box[i].first = pos[i];
		bound_box[i].second = pos[i];
		for(j = 1; j < n[i]; j++){
			scanf("%d%d",&puzzle[i][j].x,&puzzle[i][j].y);
			bound_box[i].first.x = min(bound_box[i].first.x,puzzle[i][j].x);
			bound_box[i].first.y = min(bound_box[i].first.y,puzzle[i][j].y);
			bound_box[i].second.x = max(bound_box[i].second.x,puzzle[i][j].x);
			bound_box[i].second.y = max(bound_box[i].second.y,puzzle[i][j].y);
			puzzle[i][j].x -= pos[i].x;
			puzzle[i][j].y -= pos[i].y;
		}

		bound_box[i].first.x -= pos[i].x;
		bound_box[i].first.y -= pos[i].y;
		bound_box[i].second.x -= (pos[i].x-1);
		bound_box[i].second.y -= (pos[i].y-1);
	}

	init(0,1);
	init(0,2);
	init(1,2);

	int sol =\
			bfs(make_pair (make_pair(pos[1].x-pos[0].x,pos[1].y-pos[0].y),\
			make_pair(pos[2].x-pos[0].x, pos[2].y-pos[0].y)));

	printf("%d\n",sol);


	return 0;
}
