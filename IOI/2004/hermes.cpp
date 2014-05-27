#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>

#define CMAX 2000
#define NMAX 20010

using namespace std;

int min_dist[2][CMAX+2][2];
int X[NMAX];
int Y[NMAX];

int N;

int compute(){
	int i,b,k,x,y,v;

	for(i = N-2; i >= 0; --i){
		for(k = 0; k <= CMAX; ++k){
			for(b = 0; b < 2; ++b){
				x = b ? k : X[i];
				y = b ? Y[i] : k;
				v = i&1;
				min_dist[v][k][b] = min(min_dist[!v][x][1]+abs(y-Y[i+1]),min_dist[!v][y][0]+abs(x-X[i+1]));
			}
		}
	}

	return min_dist[0][1000][0];
}

int main(){
	int i;

	scanf("%d",&N);
	++N;

	X[0] += 1000;
	Y[0] += 1000;
	for(i = 1; i < N; ++i){
		scanf("%d%d",&X[i],&Y[i]);
		X[i] += 1000;
		Y[i] += 1000;
	}

	printf("%d\n",compute());

	return 0;
}
