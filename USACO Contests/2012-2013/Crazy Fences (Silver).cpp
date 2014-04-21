/*
 Created By: Malvika Joshi
 Problem: Crazy Fences (December-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=208
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

#define MAXN 1010
#define INF 10000001LL

using namespace std;
struct point;
typedef pair<point,point> seg;
typedef long long lli;

struct point{
	lli x,y;

	inline point operator-(const point& rhs){
		point tmp;
		tmp.x = x-rhs.x;
		tmp.y = y-rhs.y;
		return tmp;
	};

	inline lli operator*(const point &rhs){
		return (x*rhs.y)-(rhs.x*y);
	}

	bool operator<(const point &rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}

	bool operator==(const point &rhs) const {
		return (x == rhs.x  && y == rhs.y);
	}
};

int diff_side(seg s, point p1, point p2){
	lli z1,z2;

	z1 = (s.second - s.first) * (p1 - s.first);
	z2 = (s.second - s.first) * (p2 - s.first);

	if(!z1 || !z2)	return -1;

	return ((z1 < 0) != (z2 < 0));
}

int intersect(seg s1, seg s2){
	int side1,side2;

	side1 = diff_side(s2,s1.first,s1.second);
	side2 = diff_side(s1,s2.first,s2.second);

	return side1 * side2;
}

const point FAR = {INF,INF};

point cows[MAXN];
seg fences[MAXN];
int visited[MAXN];

vector<int> poly[MAXN];		//segments forming the polygon
vector<int> intr[MAXN];		//points inside the polygon
int surr[MAXN];				//number of polygons surrounding the point

int P,N,C;

void dfs(int v){
	int u;
	if(visited[v]) return;
	visited[v] = 1;
	poly[P].push_back(v);

	for(u = 0; u < N; u++){
		if(u == v) continue;
		if(fences[v].first == fences[u].second || fences[v].first == fences[u].first) dfs(u);
		else if(fences[v].second == fences[u].second || fences[v].second == fences[u].first) dfs(u);
	}
}

void init(){
	int i,j,k;
	int ins,cross,bound;
	seg tmp;

	for(i = 0; i < N; i++){
		if(visited[i]) continue;
		dfs(i);
		++P;
	}

	for(i = 0; i < C; i++){
		for(j = 0; j < P; j++){
			tmp = make_pair(cows[i],FAR);
			cross = 0;
			bound = 0;

			for(k = 0; k < (int)poly[j].size(); k++){
				ins = intersect(fences[poly[j][k]],tmp);
				if(ins == -1){
					++cross;
					++bound;
					continue;
				}
				cross += ins;
			}

			bound /= 2;
			cross -= bound;
			if(!(cross%2)) continue;

			intr[j].push_back(i);
			++surr[i];
		}
	}

}

int max_comm(int pol){
	int i,comm,cow;
	int depth[MAXN] = {0};

	comm = 0;
	for(i = 0; i < (int)intr[pol].size(); ++i){
		cow = intr[pol][i];
		comm = max(comm,++depth[surr[cow]]);
	}

	return comm;
}

point make_point(int x, int y){
	point tmp = {x,y};
	return tmp;
}

int main(){
	int i,sol;

	scanf("%d%d",&N,&C);

	for(i = 0; i < N; i++)	scanf("%lld%lld%lld%lld",&fences[i].first.x,&fences[i].first.y,&fences[i].second.x,&fences[i].second.y);

	for(i = 0; i < C; i++) scanf("%lld%lld",&cows[i].x,&cows[i].y);

	sol = 0;

	init();
	for(i = 0; i < C; i++) if(!surr[i]) ++sol;
	for(i = 0; i < P; i++) sol = max(sol,max_comm(i));

	printf("%d\n",sol);

	return 0;
}
