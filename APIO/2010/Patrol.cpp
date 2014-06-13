#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <numeric>
#include <vector>

#define NMAX 100010

using namespace std;

vector<int> child[NMAX];
int par[NMAX];

int st_sub[NMAX];
int st_out[NMAX];
int out[NMAX];
int sub[NMAX];

int max_st[NMAX][4];
int max_sub[NMAX][2];

void init(int v){
	int i,u;

	for(i =0 ; i < (int)child[v].size() ;++i){
		u = child[v][i];
		if(u == par[v]){
			swap(child[v][i],child[v].back());
			child[v].pop_back();
			--i;
			continue;
		}

		par[u] = v;
		init(u);
	}
}

void dfs(int v){
	int i,k,u,ins;

	for(i = 0 ; i < (int)child[v].size(); ++i){
		u = child[v][i];
		dfs(u);

		ins = st_sub[u]+1;
		for(k = 0; k < 4; ++k){
			if(max_st[v][k] > ins) continue;
			swap(ins,max_st[v][k]);
		}

		ins = sub[u];
		for(k = 0; k < 2; ++k){
			if(max_sub[v][k] > ins) continue;
			swap(max_sub[v][k],ins);
		}
	}

	sub[v] = max(max_sub[v][0],max_st[v][0]+max_st[v][1]);
	st_sub[v] = max_st[v][0];
}

void dfs2(int v){
	int i,u,k,l,p,tmp;

	if(par[v] < 0){
		for(i =0 ; i < (int)child[v].size(); ++i){
			u = child[v][i];
			dfs2(u);
		}

		return;
	}

	p = par[v];
	k = st_sub[v]+1 == max_st[p][0];
	st_out[v] = max(st_out[p],max_st[p][k])+1;

	k = sub[v] == max_sub[p][0];
	out[v] = max(out[p],max_sub[p][k]);

	k = 0, l = 1;
	if(max_st[p][0] == st_sub[v]+1) ++k,++l;
	else if(max_st[p][1] == st_sub[v]+1) ++l;

	tmp = max_st[p][k] + max(max_st[p][l],st_out[p]);
	out[v] = max(out[v],tmp);


	for(i = 0; i < (int)child[v].size(); ++i){
		u = child[v][i];
		dfs2(u);
	}
}

int N,K;

int main(){
	int i,len,u,v;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N-1; ++i){
		scanf("%d%d",&u,&v);
		--u,--v;
		child[u].push_back(v);
		child[v].push_back(u);
	}

	par[0] = -1;
	init(0);

	dfs(0);
	dfs2(0);

	if(K == 1){
		len = 2*(N-1)-sub[0]+1;
		printf("%d\n",len);
		return 0;
	}

	len = 0;
	for(i =0 ; i < N; ++i){
		len = max(len,sub[i]+out[i]);
		len = max(len,accumulate(max_st[i],max_st[i]+4,0) + max(0,st_out[i]-max_st[i][3]));
	}

	printf("%d\n",2*(N-1)+2-len);

	return 0;
}

