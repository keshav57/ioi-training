/*
 Creted By: Malvika Joshi
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

set<int> P;
map<int,int> compr;

int cows[MAXN][2];
int fences[MAXN][2][2];
int C,F;

char G[MAXC][MAXC];
int XY[2];

void compress(int c){
	int i;

	P.clear();
	compr.clear();


	for(i = 0; i < C; i++){
		P.insert(cows[i][c]);
	}

	for(i = 0; i < F; i++){
		P.insert(fences[i][0][c]);
		P.insert(fences[i][1][c]);
	}

	i = 2;
	for(set<int>::iterator it = P.begin(); it != P.end(); ++it){
		compr[(*it)] = i;
		i+=2;
	}

	XY[c] = i+2;

	for(i = 0; i < C; i++){
		cows[i][c] = compr[cows[i][c]];
	}

	for(i = 0; i < F; i++){
		fences[i][0][c] = compr[fences[i][0][c]];
		fences[i][1][c] = compr[fences[i][1][c]];
	}
}

void init(){

	int i,j,k;

	//0 empty. 1 cow. 2 fence

	for(i = 0; i <= XY[0]; i++) G[i][0] = G[i][XY[1]] = 2;
	for(i = 0; i <= XY[1]; i++) G[0][i] = G[XY[0]][i] = 2;

	for(i = 0; i < C; i++){
		G[cows[i][0]][cows[i][1]] = 1;
	}

	for(i = 0; i < F; i++){
		for(j = fences[i][0][0]; j <= fences[i][1][0]; j++){
			for(k =fences[i][0][1]; k <= fences[i][1][1] ; k++)
				G[j][k]= 2;
		}
	}

}

pair<short,short> Q[MAXC*MAXC];
int H,T;

const pair<int,int> adj[4] = { make_pair(1,0),make_pair(-1,0) , make_pair(0,1), make_pair(0,-1) };

int bfs(pair<int,int> s){
	int k,c = 0;
	pair<int,int> v;

	if(G[s.x][s.y] > 1) return 0;

	H = T = 0;
	c += G[s.x][s.y];
	G[s.x][s.y]= 3;
	Q[T++] = s;

	while(H < T){
		v = Q[H++];

		for(k = 0; k < 4; k++){
			if(G[v.x+adj[k].x][v.y+adj[k].y] <= 1){
				c += G[v.x+adj[k].x][v.y+adj[k].y];
				G[v.x+adj[k].x][v.y+adj[k].y]= 3;
				Q[T++] = make_pair(v.x+adj[k].x,v.y+adj[k].y);
			}
		}

	}

	return c;
}

int main(){

	int i,j;

	scanf("%d %d",&F,&C);

	for(i =0 ; i < F; i++){
		scanf("%d%d%d%d",&fences[i][0][0],&fences[i][0][1],&fences[i][1][0],&fences[i][1][1]);
		if(fences[i][0][0] > fences[i][1][0]) swap(fences[i][0][0],fences[i][1][0]);
		if(fences[i][0][1] > fences[i][1][1]) swap(fences[i][0][1],fences[i][1][1]);
	}

	for(i = 0; i < C; i++){
		scanf("%d%d",&cows[i][0],&cows[i][1]);
	}

	compress(0);
	compress(1);
	init();

	int mcow,ccow;

	mcow = 0;

	for(i = 1; i < XY[0]; i++){
		for(j = 1; j < XY[1]; j++){
			ccow = bfs(make_pair(i,j));
			mcow = max(mcow,ccow);
		}
	}

	printf("%d\n",mcow);

	return 0;
}
