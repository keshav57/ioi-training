#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cassert>

#define NMAX 310
#define LMAX 510

#define x first
#define y second

using namespace std;

vector<int> adj[NMAX];
int ssize[NMAX];

int lookup[NMAX];

#define PI 3.14159265359

typedef pair<int,int> point;

point pos[LMAX];

int compare(int a, int b){
	double i,j;
	i = atan2(pos[a].y,pos[a].x);
	j = atan2(pos[b].y,pos[b].x);

	i += i < 0 ? 2*PI : 0;
	j += j < 0 ? 2*PI : 0;

	return i  < j;
}

void connect(int v, int root, vector<int> &pts){
	lookup[v] = root;
	if(adj[v].empty()) return;

	int i,k,u;

	k = 0;

	for(i = 0; i <(int) pts.size(); ++i){

		assert(pts[i]^root);
		pos[pts[i]].x -= pos[root].x;
		pos[pts[i]].y -= pos[root].y;

	}

	sort(pts.begin(),pts.end(),compare);

	for(i =0 ; i <(int) pts.size(); ++i){
		pos[pts[i]].x += pos[root].x;
		pos[pts[i]].y += pos[root].y;
	}

	vector<int> tmp;
	int conn;

	for(i = 0; i <(int) adj[v].size(); ++i){
		u = adj[v][i];
		tmp.clear();
		assert(k < (int)pts.size());
		conn = pts[k++];

		while(--ssize[u]){
			assert(k < (int)pts.size());
			tmp.push_back(pts[k++]);
		}

		connect(u,conn,tmp);
	}
}

void dfs(int v,int p){
	int i,u;

	ssize[v] = 1;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];

		if(u == p){
			swap(adj[v][i],adj[v].back());
			adj[v].pop_back();
			--i;
			continue;
		}

		dfs(u,v);
		ssize[v] += ssize[u];
	}

}

int N,M,L;

int main(){
	int i,j;

	scanf("%d%d",&N,&M);

	while(M--){
		scanf("%d%d",&i,&j);
		--i,--j;
		adj[i].push_back(j);
		adj[j].push_back(i);
	}

	scanf("%d",&L);

	for(i =0 ; i < L; ++i){
		scanf("%d%d",&pos[i].x,&pos[i].y);
	}

	dfs(0,-1);

	vector<int> all;
	int conn;
	conn = -1;

	for(i =0 ; i < L; ++i){
		if(conn < 0 || make_pair(pos[i].y,pos[i].x) < make_pair(pos[conn].y,pos[conn].x)) conn = i;
	}

	for(i = 0; i < L; ++i){
		if(i == conn) continue;
		all.push_back(i);
	}


	connect(0,conn,all);

	for(i  = 0 ;i <N; ++i){
		printf("%d\n",lookup[i]+1);
	}

	return 0;
}

/**
 * 10 9
1 2
1 3
1 4
4 9
9 10
3 7
2 5
2 6
6 8
10
1 2
3 4
5 5
4 8
3 12
7 3
7 5
6 10
10 1
10 7
 *
 */
