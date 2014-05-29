#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>

#define NMAX 110
#define KMAX 52
#define INF (2e9)

using namespace std;

int f(int,int,int,int);
int g(int,int,int,int);

int fmem[NMAX][KMAX][NMAX];
int gmem[NMAX][KMAX][NMAX];

int last[NMAX];
int sib[NMAX];
int par_dist[NMAX];
int trees[NMAX];

int g(int i, int k, int lst, int dist){
	if(i < 0) return 0;
	int &val = gmem[i][k][lst];
	if(val >= 0) return val;

	if(sib[i] < 0){
		val = f(i,k,lst,dist);
		return val;
	}

	int j;

	val = INF;
	for(j = 0; j <= k; ++j){
		val = min(val,g(sib[i],k-j,lst,dist)+f(i,j,lst,dist));
	}

	return val;
}

int f(int i, int k, int lst, int dist){
	int &val = fmem[i][k][lst];
	if(val >= 0) return val;

	dist += par_dist[i];

	val = k ? min( g(last[i],k,lst,dist)+dist*trees[i] , g(last[i],k-1,i,0)) \
			: g(last[i],k,lst,dist)+dist*trees[i];

	return val;
}

vector<int> child[NMAX];
int N,K;

void dfs(int v){
	int i,u,p;

	p = -1;
	for(i = 0; i < (int)child[v].size(); ++i){
		u = child[v][i];
		sib[u] = p;
		p = u;
		dfs(u);
	}

	last[v] = p;
}

int main(){
	int i,p;

	memset(fmem,-1,sizeof(fmem));
	memset(gmem,-1,sizeof(gmem));

	scanf("%d%d",&N,&K);
	++N;

	for(i = 1; i < N; ++i){
		scanf("%d%d%d",&trees[i],&p,&par_dist[i]);
		child[p].push_back(i);
	}

	sib[0] = -1;
	dfs(0);

	printf("%d\n",f(0,K,0,0));

	return 0;
}
