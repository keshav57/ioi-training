/*
 Created By: Malvika Joshi
 Problem: What's Up with Gravity (US Open-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=282
*/

#include <cstdio>
#include <algorithm>
#include <set>

#define MAXN 510
#define INF 1000010

using namespace std;

int world[MAXN][MAXN];
int visited[MAXN][MAXN][2];
int dist[MAXN][MAXN][2];
int N,M;

set<pair<int,pair<pair<int,int>,int> > > Q;

int dijkstra(pair<int,int> s){

	int i,j,dir,d;
	pair<int,int> v;

	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			dist[i][j][0] = dist[i][j][1] = INF;

	dist[s.first][s.second][1] = 0;
	Q.insert(make_pair(0,make_pair(s,1)));


	while(!Q.empty()){
		v = Q.begin()->second.first;
		d = Q.begin()->second.second;
		dir = d ? 1 : -1;

		Q.erase(Q.begin());

		if(visited[v.first][v.second][d]) continue;
		visited[v.first][v.second][d] = 1;
		if(world[v.first][v.second] == 2)  return dist[v.first][v.second][d];

		if(v.first+dir >= N || v.first+dir < 0) continue;

		if(world[v.first+dir][v.second]){
			if(dist[v.first][v.second][d] < dist[v.first+dir][v.second][d]){
				dist[v.first+dir][v.second][d] = dist[v.first][v.second][d];
				Q.insert(make_pair(dist[v.first][v.second][d],make_pair(make_pair(v.first+dir,v.second),d)));
			}
			continue;
		}

		if(v.second < M-1 && world[v.first][v.second+1]){
			if(dist[v.first][v.second][d] < dist[v.first][v.second+1][d]){
				dist[v.first][v.second+1][d] = dist[v.first][v.second][d];
				Q.insert(make_pair(dist[v.first][v.second][d],make_pair(make_pair(v.first,v.second+1),d)));
			}
		}

		if(v.second > 0 && world[v.first][v.second-1]){
			if(dist[v.first][v.second][d] < dist[v.first][v.second-1][d]){
				dist[v.first][v.second-1][d] = dist[v.first][v.second][d];
				Q.insert(make_pair(dist[v.first][v.second][d],make_pair(make_pair(v.first,v.second-1),d)));
			}
		}

		if(dist[v.first][v.second][d]+1 < dist[v.first][v.second][!d]){
			dist[v.first][v.second][!d] = dist[v.first][v.second][d]+1;
			Q.insert(make_pair(dist[v.first][v.second][d]+1,make_pair(make_pair(v.first,v.second),!d)));
		}

	}

	return -1;
}

int main(){

	int i,j;
	char c;
	pair<int,int> s;


	scanf("%d%d",&N,&M);

	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			scanf(" %c",&c);
			world[i][j] = c == 'D' ? 2 : c == '.';
			if(c == 'C'){
				world[i][j] = 1;
				s = make_pair(i,j);
			}
		}
	}

	i = dijkstra(s);

	printf("%d\n",i);

	return 0;
}
