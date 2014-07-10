#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>

#define NMAX 510

using namespace std;

int dist[NMAX][NMAX];
int order[NMAX][NMAX];

int src;
int compare(int a, int b){
	return dist[src][a] < dist[src][b];
}

int N;
int stack[NMAX];
int S;

int compute(){
	int a,b,i,k,mb1,mb2,ma1,ma2,sol,tmp,st;

	sol = (1e9);

	for(a = 0; a < N; ++a){
		for(b = a+1; b < N; ++b){
			mb1 = mb2 = ma1 = ma2 = 0;
			S = 0;
			st = order[a][N-1] == b ? order[a][N-2] : order[a][N-1];
			for(i = 0; i < N; ++i){
				k = order[a][i];
				if(k == a || k == b) continue;
				if(i == st || dist[a][k] < dist[a][b]+dist[b][k]){
					stack[S++] = k;
					continue;
				}
				if(dist[b][k] > mb1){
					mb2 = mb1;
					mb1 = dist[b][k];
				}else{
					mb2 = max(mb2,dist[b][k]);
				}
			}

			while(S--){
				k = stack[S];

				ma1 = dist[a][k];
				ma2 = S ? dist[a][stack[S-1]] : 0;
				tmp = max(ma1+ma2,max(mb2+mb1,mb1+ma1+dist[a][b]));
				sol = min(sol,tmp);
				if(dist[b][k] > mb1){
					mb2 = mb1;
					mb1 = dist[b][k];
				}else{
					mb2 = max(mb2,dist[b][k]);
				}
			}

			tmp = max(mb1+mb2,mb1+dist[a][b]);
			sol = min(sol,tmp);
		}
	}

	return sol;
}

pair<int,int> pos[NMAX];

int main(){
	int i,j;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&pos[i].first,&pos[i].second);
	}

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			dist[i][j] = abs(pos[i].first-pos[j].first)+abs(pos[i].second-pos[j].second);
		}
	}

	for(i = 0; i < N; ++i){
		src = i;
		for(j = 0; j < N; ++j) order[i][j] = j;
		sort(order[i],order[i]+N,compare);
	}

	printf("%d\n",compute());

	return 0;
}

/*
 
 
 
 
or a point k which is closet to H1 than i, 
x = dist(H1,k)	
y = dist(H2,k)+dist(H1,H2)
I connect k to H1 if x < y, otherwise I connect it to H2.

 
 */
