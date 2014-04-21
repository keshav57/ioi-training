/*
 Created By: Malvika Joshi
 Problem: Crazy Fences (December-2012 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=207
*/

#include <cstdio>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

#define MAXC 3010
#define MAXN 510
#define x first
#define y second

struct cow{
	int x,y;
};

struct fen{
	int x1,y1,x2,y2;
};

set<int> P;
map<int,int> compr;

cow cows[MAXN];
fen fences[MAXN];
int C,F;

char G[MAXC][MAXC];
int X,Y;

void compress(){
	int i,c;

	c = 0;
	for(i = 0; i < C; i++){
		P.insert(cows[i].x);
	}
	for(i = 0; i < C; i++){
		P.insert(fences[i].x1);
		P.insert(fences[i].x2);
	}

	i = 2;
	for(set<int>::iterator it = P.begin(); it != P.end(); ++it){
		compr[(*it)] = i;
		i+=2;
	}
	X = i+2;

	for(i = 0; i < C; i++)	cows[i].x = compr[cows[i].x];

	for(i = 0; i < C; i++){
		fences[i].x1 = compr[fences[i].x1];
		fences[i].x2 = compr[fences[i].x2];
	}


	P.clear();
	compr.clear();
	c = 0;
	for(i = 0; i < C; i++){
		P.insert(cows[i].y);
	}
	for(i = 0; i < C; i++){
		P.insert(fences[i].y1);
		P.insert(fences[i].y2);
	}

	i = 2;
	for(set<int>::iterator it = P.begin(); it != P.end(); ++it){
		compr[(*it)] = i;
		i+=2;
	}
	Y = i+2;

	for(i = 0; i < C; i++)	cows[i].y = compr[cows[i].y];

	for(i = 0; i < C; i++){
		fences[i].y1 = compr[fences[i].y1];
		fences[i].y2 = compr[fences[i].y2];
	}

}

void init(){

	int i,j,k;

	//0 empty. 1 cow. 2 fence

	for(i = 0; i <= X; i++) G[i][0] = G[i][Y] = 2;
	for(i = 0; i <= Y; i++) G[0][i] = G[X][i] = 2;

	for(i = 0; i < C; i++){
		G[cows[i].x][cows[i].y] = 1;
	}

	for(i = 0; i < F; i++){
		for(j = fences[i].x1; j <= fences[i].x2; j++){
			for(k =fences[i].y1; k <= fences[i].y2 ; k++)
				G[j][k]= 2;
		}
	}

}

pair<short,short> Q[MAXC*MAXC];
int H,T;

int bfs(pair<int,int> s){
	int c = 0;
	pair<int,int> v;

	if(G[s.x][s.y] > 1) return 0;

	H = T = 0;
	c += G[s.x][s.y];
	G[s.x][s.y]= 3;
	Q[T++] = s;

	while(H < T){
		v = Q[H++];

		if(G[v.x+1][v.y] <= 1){
			c += G[v.x+1][v.y];
			G[v.x+1][v.y]= 3;
			Q[T++] = make_pair(v.x+1,v.y);
		}
		if(G[v.x-1][v.y] <= 1){
			c += G[v.x-1][v.y];
			G[v.x-1][v.y]= 3;
			Q[T++] = make_pair(v.x-1,v.y);
		}
		if(G[v.x][v.y+1] <= 1){
			c += G[v.x][v.y+1];
			G[v.x][v.y+1]= 3;
			Q[T++] = make_pair(v.x,v.y+1);
		}

		if(G[v.x][v.y-1] <= 1){
			c += G[v.x][v.y-1];
			G[v.x][v.y-1]= 3;
			Q[T++] = make_pair(v.x,v.y-1);
		}

	}

	return c;
}

int main(){

	int i,j;

	scanf("%d %d",&F,&C);

	for(i =0 ; i < F; i++){
		scanf("%d%d%d%d",&fences[i].x1,&fences[i].y1,&fences[i].x2,&fences[i].y2);
		if(fences[i].x1 > fences[i].x2) swap(fences[i].x1,fences[i].x2);
		if(fences[i].y1 > fences[i].y2) swap(fences[i].y1,fences[i].y2);
	}

	for(i = 0; i < C; i++){
		scanf("%d%d",&cows[i].x,&cows[i].y);
	}

	compress();
	init();

	int mcow,ccow;

	mcow = 0;
	for(i = 1; i < X; i++){
		for(j = 1; j < Y; j++){
			ccow = bfs(make_pair(i,j));
			mcow = max(mcow,ccow);
		}
	}

	printf("%d\n",mcow);

	return 0;
}
