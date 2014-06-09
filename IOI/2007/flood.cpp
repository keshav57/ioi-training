#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <numeric>

#define x first
#define y second
#define NMAX 100010
#define MMAX 200010
#define DIR 4

using namespace std;

typedef pair<int,int> point;

point pos[NMAX];

pair<int,int> out[NMAX][DIR];
pair<int,int> inc[NMAX][DIR];

int visited[NMAX][DIR];
int del[MMAX];
int ct[MMAX];

int M,N;

int stack[MMAX*2];
int S;

void walk(int pt, int dir){
	if(del[inc[pt][dir].second]) return;

	int i;
	S = 0;

	while(!visited[pt][dir]){
		visited[pt][dir] = 1;
		++ct[inc[pt][dir].second];
		stack[S++] = inc[pt][dir].second;

		for(i = (dir+DIR-1)%DIR; i != (dir+2)%DIR; i = (i+1)%DIR){
			if(out[pt][i].first >= 0 && !del[out[pt][i].second]) break;
		}

		pt = out[pt][i].first;
		dir = i;
	}

	while(S--){
		del[stack[S]] = 1;
	}
}

pair<int,int> order[MMAX];

int compare(pair<int,int> a, pair<int,int> b){
	//| has priority
	return pos[a.first].x == pos[b.first].x ? a.second < b.second : pos[a.first].x < pos[b.first].x;
}

int main(){
	int i,dir,u,v,k;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&pos[i].x,&pos[i].y);
	}

	scanf("%d",&M);

	for(i = 0; i < N; ++i){
		for(dir = 0; dir < DIR; ++dir){
			out[i][dir].first = inc[i][dir].first = -1;
		}
	}

	for(i = 0; i < M; ++i){
		scanf("%d%d",&u,&v);
		--u,--v;
		dir = pos[u].y == pos[v].y;
		if(pos[v] < pos[u]) swap(u,v);

		out[u][dir] = make_pair(v,i);
		inc[v][dir] = make_pair(u,i);

		out[v][dir+2] = make_pair(u,i);
		inc[u][dir+2] = make_pair(v,i);
		order[i] = make_pair(u,dir);
	}

	sort(order,order+M,compare);
	for(i = 0; i < M; ++i){
		walk(out[order[i].first][order[i].second].first,order[i].second);
	}

	k = accumulate(ct,ct+M,-M);

	printf("%d\n",k);

	for(i = 0; i < M; ++i){
		if(ct[i] < 2) continue;
		printf("%d\n",i+1);
	}

	return 0;
}
