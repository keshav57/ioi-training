/*
 Created By: Malvika Joshi
 Problem: Playground (IOITC-2010 Final-2)
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

#define PI 3.14159265359
#define LIM 180.0000000
#define DEG LIM/PI
#define MOD 100000007
#define MAXN 65
#define INF -10000
#define x first
#define y second

using namespace std;
typedef pair<int,int> point;

int ways[MAXN][MAXN][MAXN][MAXN];
int marea[MAXN][MAXN][MAXN][MAXN];
char tree[MAXN][MAXN];
int ignore[MAXN][MAXN];

pair<double,point> next[MAXN*MAXN],prev[MAXN*MAXN];
int M,N;

inline int area(point a, point b, point c){
	int area;
	area = (a.x-c.x)*(b.y-a.y) - (a.x-b.x)*(c.y-a.y);
	return abs(area);
}

void DP(){

	int i,j,nx,ny,px,py,p0,p1;
	double tmp;
	int n,p;

	for(i = 0; i <= M; ++i){
		for(j = 0; j <= N; ++j){
			if(tree[i][j]) continue;
			if(ignore[i][j]) continue;
			n = p = 0;

			for(nx = i+1; nx <= M; ++nx){
				for(ny = j+1; ny <= N; ++ny){
					if(tree[nx][ny]) continue;
					if(ignore[nx][ny]) continue;
					tmp = atan2(ny-j,nx-i);
					tmp *= DEG;
					next[n++] = (make_pair(tmp,make_pair(nx,ny)));
				}
			}

			for(px = i-1; px >= 0; --px){
				for(py = j-1; py >= 0; --py){
					if(tree[px][py]) continue;
					if(ignore[px][py]) continue;
					tmp = atan2(py-j,px-i);
					tmp *= DEG;
					assert(tmp < 0);
					prev[p++] = (make_pair(-tmp+0.0001,make_pair(px,py)));
				}
			}

			sort(next,next+n);
			sort(prev,prev+p);
			reverse(next,next+n);

			p0 = p1 = 0;

			if(!i && n){
				ways[i][j][next[p0].second.x][next[p0].second.y] += 1;
				marea[i][j][next[p0].second.x][next[p0].second.y] = area(make_pair(M,0),make_pair(0,0),make_pair(i,j));
			}


			while(p1 < p && prev[p1].first+next[p0].first < LIM){
				nx = next[p0].second.x,ny = next[p0].second.y;
				px = prev[p1].second.x,py = prev[p1].second.y;
				ways[i][j][nx][ny] += ways[px][py][i][j];
				ways[i][j][nx][ny] %= MOD;
				marea[i][j][nx][ny] = max(marea[i][j][nx][ny],marea[px][py][i][j]);
				++p1;
			}


			for(++p0; p0 < n; ++p0){
				nx = next[p0].second.x,ny = next[p0].second.y;
				ways[i][j][nx][ny] += ways[i][j][next[p0-1].second.x][next[p0-1].second.y];
				marea[i][j][nx][ny] = marea[i][j][next[p0-1].second.x][next[p0-1].second.y];
				while(p1 < p && prev[p1].first+next[p0].first < LIM){
					nx = next[p0].second.x,ny = next[p0].second.y;
					px = prev[p1].second.x,py = prev[p1].second.y;
					ways[i][j][nx][ny] += ways[px][py][i][j];
					ways[i][j][nx][ny] %= MOD;
					marea[i][j][nx][ny] = max(marea[i][j][nx][ny],marea[px][py][i][j]);
					++p1;
				}
			}

			for(p0 = 0; p0 < n; ++p0){
				nx = next[p0].second.x,ny = next[p0].second.y;
				marea[i][j][nx][ny] += area(make_pair(i,j),make_pair(nx,ny),make_pair(M,0));
			}

		}
	}

}

inline int cross(point p1, point p2){
	return (p1.x*p2.y - p2.x*p1.y);
}

int main(){
	int i,j,t;

	scanf("%d%d%d",&M,&N,&t);

	while(t--){
		scanf("%d%d",&i,&j);
		if((!i && !j) ||(i == M && j == N)){
			printf("0\n");
			return 0;
		}
		//	if(!i || !j ) continue;
		tree[i][j] = 1;

	}

	for(i = 0 ; i <= M; ++i){
		for(j = 0; j <= N; ++j){
			ignore[i][j] = cross(make_pair(i,j),make_pair(M,N)) > 0;
		}
	}

	DP();

	int sol,px,py;
	int mar = 0,tmp;
	sol = 0;

	for(i = 0; i <= M; ++i){
		for(px = i-1; px >= 0; --px){
			for(py = N-1; py >= 0; --py){
				sol += ways[px][py][i][N];
				tmp = marea[px][py][i][N] + area(make_pair(M,N),make_pair(i,N),make_pair(M,0));
				mar = max(mar,tmp);
				sol %= MOD;
			}
		}
	}

	if(!tree[0][N]){
		++sol;
		mar = M*N*2;
	}

	printf("%d\n",sol);
	printf("%.1f\n",(double)mar/2);

	return 0;
}
