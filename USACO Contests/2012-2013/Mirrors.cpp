/*
 Created By: Malvika Joshi
 Problem: Mirrors (January-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=223
*/

#include <cstdio>
#include <algorithm>
#include <utility>

#define MAXN 210

using namespace std;

typedef pair<pair<int,int>,int> point;

struct dir {
	int d,inc;
	void  change_dir(int mir){
		d ^= 1;
		inc = mir ? inc*-1 : inc;
	}
};

int compare(point a, point b){
	return a.first.second== b.first.second ? a.first.first < b.first.first : a.first.second < b.first.second;
}

point orderx[MAXN];
point ordery[MAXN];
int visited[MAXN][2][2];
int type[MAXN];
int N;

int look(){

	int i,v;
	point pos;
	dir cdir;

	for(i = 0;i < N; i++)
		for(v = 0; v < 2; v++)
			visited[i][v][0] = visited[i][v][1] = 0;

	pos = make_pair(make_pair(0,0),0);
	cdir.d = 0;
	cdir.inc = 1;


	while(1){
		v = cdir.inc == 1;
		if(visited[pos.second][cdir.d][v]) return 0;
		visited[pos.second][cdir.d][v] = 1;

		if(pos.second == N-1) return 1;

		if(cdir.d){
			i = lower_bound(orderx,orderx+N,pos)-orderx;
			i += cdir.inc;
			if(i < 0 || i >= N)	return 0;

			if(pos.first.first != orderx[i].first.first) return 0;
			pos = orderx[i];
		}else{
			i = lower_bound(ordery,ordery+N,pos,compare)-ordery;
			i += cdir.inc;
			if(i < 0 || i >= N) return 0;
			if(pos.first.second != ordery[i].first.second) return 0;
			pos = ordery[i];
		}
		if(pos.second) cdir.change_dir(type[pos.second]);
	}

	return 0;
}

int main(){

	int i;
	char c;

	scanf("%d",&N);
	N+=2;
	orderx[0] = ordery[0] = make_pair(make_pair(0,0),0);
	scanf("%d%d",&orderx[N-1].first.first,&orderx[N-1].first.second);
	orderx[N-1].second = N-1;
	ordery[N-1] = orderx[N-1];

	for(i = 1; i < N-1; ++i){
		scanf("%d%d",&orderx[i].first.first,&orderx[i].first.second);
		orderx[i].second = i;
		ordery[i] = orderx[i];
		scanf(" %c",&c);
		type[i] = c == '\\';
	}

	sort(orderx,orderx+N);
	sort(ordery,ordery+N,compare);

	if(look()){
		printf("0\n");
		return 0;
	}

	for(i = 1; i < N-1; i++){
		type[i] ^= 1;
		if(look()){
			printf("%d\n",i);
			return 0;
		}
		type[i] ^= 1;
	}

	type[3] ^= 1;

	printf("-1\n");

	return 0;
}
