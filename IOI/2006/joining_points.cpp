#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

#include <utility>

#define NMAX 100010
#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

int cross(int x1, int y1, int x2, int y2){
	return (1LL*x1*y2-1LL*x2*y1) < 0;
}

int inside_triangle(point &p1, point &p2, point &p3, point &pt){
	int i;
	i = cross(pt.x-p1.x,pt.y-p1.y,p2.x-p1.x,p2.y-p1.y);

	return ( (cross(pt.x-p2.x,pt.y-p2.y,p3.x-p2.x,p3.y-p2.y) == i)
			&& (cross(pt.x-p3.x,pt.y-p3.y,p1.x-p3.x,p1.y-p3.y) == i) );
}

int col[NMAX];
point pos[NMAX];
int N;

char name[2] = {'g','r'};

void solve(vector<int> &pts, int *vert){
	if(pts.empty()) return;

	int conn[2],i,mid,mcol,v1,v2,part[3];

	mcol = 0;

	for(i = 0; i < 3; ++i){
		conn[col[vert[i]]] = vert[i];
		mcol^=col[vert[i]];
	}
	assert(conn[1] >= N);
	conn[1] -= N;

	vector<int> tmp;

	for(i = 0; i < (int)pts.size(); ++i) if(col[pts[i]]) break;

	if(!i || i >= (int)pts.size()){
		for(i = 0; i < (int)pts.size(); ++i){
			printf("%d %d %c\n",pts[i] - (col[pts[i]] ? N : 0)+1, conn[col[pts[i]]]+1,name[col[pts[i]]]);
		}
		return;
	}
	mid = mcol ? pts[i+rand()%(pts.size()-i)] : pts[rand()%i];

	printf("%d %d %c\n",mid - (col[mid] ? N : 0)+1,conn[col[mid]]+1,name[col[mid]]);

	part[0] = mid;
	for(v1 = 0; v1 < 2; ++v1){
		part[1] = vert[v1];
		for(v2 = v1+1; v2 < 3; ++v2){
			part[2] = vert[v2];
			tmp.clear();

			for(i = 0; i < (int)pts.size(); ++i){
				if(pts[i] == mid) continue;
				if(!inside_triangle(pos[vert[v1]], pos[vert[v2]] , pos[mid] , pos[pts[i]] )) continue;
				tmp.push_back(pts[i]);
			}
			solve(tmp,part);
		}
	}
}

int M;

int main(){
	int i;

	scanf("%d",&N);

	i = 0;
	for(i = 0; i < N; ++i){
		scanf("%d%d",&pos[i].x,&pos[i].y);
	}

	scanf("%d",&M);

	for(; i < M+N; ++i){
		col[i] = 1;
		scanf("%d%d",&pos[i].x,&pos[i].y);
	}

	int tri[2][3] = { {0,1,N+1} , {N,N+1,0} };

	vector<int> in1,in2;

	for(i = 2; i < M+N; ++i){
		if(i == N || i == N+1) continue;
		if(inside_triangle(pos[tri[0][0]] ,pos[tri[0][1]] ,pos[tri[0][2]], pos[i])){
			in1.push_back(i);
		}else{
			in2.push_back(i);
		}
	}

	printf("%d %d g",1,2);
	printf("%d %d r\n",1,2);

	solve(in1,tri[0]);
	solve(in2,tri[1]);

	return 0;
}
