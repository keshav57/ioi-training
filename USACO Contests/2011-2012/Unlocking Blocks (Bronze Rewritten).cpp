/*
 Created By: Malvika Joshi
 Problem: Unlocking Blocks (US Open-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=133
*/

#include <cstdio>
#include <map>

#define MAXN 110
#define B 3

#define x first
#define y second
#define add 11

using namespace std;
typedef pair<int,int> point;

int n[B];
point rel[B][MAXN];
point o[B];
pair<point,point> box[B];
pair<int,int> adj[4] = { make_pair(0,1) , make_pair(0,-1) ,  make_pair(-1,0) ,  make_pair(1,0)  };

//b1.x-b2.x b1.y-b2-y b1.x-b3.x b1.y-b3.y
map<pair<point,point>, bool> visited;

inline int overlap(pair<point,point> R1, pair<point,point> R2){
	return (R1.first.x <= R2.second.x && R1.second.x >= R2.first.x
			&& R1.first.y <= R2.second.y && R1.second.x >= R2.first.y);
}

int dfs(point *cpos){

	pair<point,point> m = make_pair(make_pair(cpos[0].x-cpos[1].x,cpos[0].y-cpos[1].y),
			make_pair(cpos[0].x-cpos[2].x,cpos[0].y-cpos[2].y));

	if(visited[m]) return 0;
	visited[m] = 1;

	int i,k,ov;
	pair<point,point> bound_box[2];
    point p,t;
    char grid[40][40] = {{0}};

    for(i = 0 ; i < B; ++i){
        p = cpos[i];
        if(p.x > o[i].x+10 || p.x < o[i].x-10 || p.y > o[i].y+10 || p.y < o[i].y-10) return 0;
        for(k = 0; k < n[i]; k++){
            t.x = p.x+rel[i][k].x + 11;
            t.y = p.y+rel[i][k].y + 11;
            if(grid[t.x][t.y]) return 0;
            grid[t.x][t.y] = i+1;
        }
    }

	ov = 0;
	for(i = 0; i < B-1; i++){
		for(k = i+1; k < B; k++){
			for(int b = 0; b < 2; b++){
				bound_box[b] = box[i];
				bound_box[b].first.x += cpos[i].x;
				bound_box[b].first.y += cpos[i].y;
				bound_box[b].second.x += cpos[i].x;
				bound_box[b].second.y += cpos[i].y;
			}
			ov = ov || overlap(bound_box[0],bound_box[1]);
			ov = ov || overlap(bound_box[1],bound_box[0]);
		}
	}

	if(!ov) return 1;


	for(i = 0; i < B; i++){
		for (k = 0; k < 4; k++) {
			cpos[i].x += adj[k].x;
			cpos[i].y += adj[k].y;
			if(dfs(cpos)) return 1;
			cpos[i].x -= adj[k].x;
			cpos[i].y -= adj[k].y;
		}
	}

	return 0;
}



int main(){
	int i,j,x0,y0;
	point pos[B];

	for(i =0 ; i < B; i++) scanf("%d",&n[i]);

	for(i = 0; i < B; i++){
		scanf("%d%d", &pos[i].x,&pos[i].y);

		box[i].first = pos[i];
		box[i].second = pos[i];

		for(j = 1; j < n[i];j ++){
			scanf("%d%d",&x0,&y0);
			box[i].first.x = min(box[i].first.x,x0);
			box[i].first.y = min(box[i].first.y,y0);
			box[i].second.x = max(box[i].second.x,x0);
			box[i].second.y = max(box[i].second.y,y0);
            rel[i][j] =  make_pair(x0-pos[i].x,y0-pos[i].y);
		}

		box[i].first.x -= pos[i].x;
		box[i].first.y -= pos[i].y;
		box[i].second.x -= pos[i].x;
		box[i].second.y -= pos[i].y;
		o[i] = pos[i];

	}

	printf("%d\n", dfs(pos));
}
