#include <algorithm>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>

#define NMAX 810
#define x first
#define y second

using namespace std;

const pair<int,int> adj[4] = {make_pair(0,-1), make_pair(0,1), make_pair(-1,0), make_pair(1,0) };

int occ_time[NMAX][NMAX];
int dist[NMAX][NMAX];

pair<int,int> Q[NMAX*NMAX];
int H,T;

int tree[NMAX][NMAX];
pair<int,int> honey,home;

int N,S;

int visited[NMAX][NMAX];

void init_bfs(){
	pair<int,int> u,v;
	int i;

	while(H < T){
		v = Q[H++];

		if(v == home) continue;

		for(i = 0; i < 4; ++i){
			u = make_pair(v.x+adj[i].x,v.y+adj[i].y);
			if(u.x < 0 || u.x >= N || u.y < 0 || u.y >= N) continue;
			if(tree[u.x][u.y] || visited[u.x][u.y]) continue;
			occ_time[u.x][u.y] = occ_time[v.x][v.y]+S;
			visited[u.x][u.y] = 1;
			Q[T++] = u;
		}
	}
}

int pos(int st){
	H = T = 0;
	memset(visited,0,sizeof(visited));

	pair<int,int> u,v;
	int i;

	dist[honey.x][honey.y] = st;
	Q[T++] = honey;

	while(H < T){
		v = Q[H++];

		if(v == home) return 1;
		if(dist[v.x][v.y] >= occ_time[v.x][v.y]) continue;

		for(i = 0; i < 4; ++i){
			u = make_pair(v.x+adj[i].x,v.y+adj[i].y);
			if(u.x < 0 || u.y < 0 || u.x >= N || u.y >= N) continue;
			if(visited[u.x][u.y] || tree[u.x][u.y]) continue;
			dist[u.x][u.y] = dist[v.x][v.y]+1;
			visited[u.x][u.y] = 1;
			Q[T++] = u;
		}

	}

	return 0;
}

int search(){
	int low,high,mid;

	low = 0;
	high = (800*800)+1;

	while(low < high){
		mid = low+(high-low)/2;

		if(pos(mid*S)){
			low = mid+1;
		}else{
			high = mid;
		}
	}

	return low-1;
}

int main(){
	int i,j;
	char c;

	scanf("%d%d",&N,&S);
	memset(occ_time,-1,sizeof(occ_time));


	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			scanf(" %c",&c);
			if(c == 'M') honey = make_pair(i,j);
			if(c == 'D') home = make_pair(i,j);
			if(c == 'H'){
				Q[T++] = make_pair(i,j);
				visited[i][j] = 1;
				occ_time[i][j] = 0;
			}
			tree[i][j] = c == 'T';
		}
	}

	init_bfs();

	printf("%d\n",search());

	return 0;
}
