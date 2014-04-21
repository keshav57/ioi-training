/*
 Created By: Malvika Joshi
 Problem: Cable Thieves (IOITC-2010 Final-1)
*/

#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>
#include <iostream>

#define MOD 100000
#define MAXN 100010
#define MAXD 6

typedef long long lli;

using namespace std;

int choose[MAXD][MAXD];

vector<int> children[MAXN];
int par[MAXN];

int x[MAXN][MAXD];
int y[MAXN][MAXD];

int data_epar[MAXN][MAXD];

vector<int> adj[MAXN];
pair<int,int> edges[MAXN];
int N,D;

int three_terms_exp(int d, int *aexlist, int *bexlist){
	int exp0,exp1;
	lli sol = 0,coeff;

	for(exp0 = 0; exp0 <= d; ++exp0){
		for(exp1 = 0; exp1+exp0 <= d; ++exp1){
			coeff = choose[d][exp0]*choose[d-exp0][exp1];
			coeff %= MOD;
			sol += (coeff*aexlist[exp0]*bexlist[exp1]);
			sol %= MOD;
		}
	}

	return (int)sol;
}

int two_terms_exp(int d, int *exlist){
    int exp,coeff;
    lli sol = 0;


    for(exp = 0; exp <= d; ++exp){
        coeff = choose[d][exp];
        sol += (lli)coeff*exlist[exp];
        sol %= MOD;
    }

    return (int)sol;
}

void computex(int v){
    int i,d;


    for(i = 0; i < (int)children[v].size(); ++i){
        computex(children[v][i]);
        for(d = 0; d <= D; ++d){
            x[v][d] += two_terms_exp(d,x[children[v][i]]);
            x[v][d]  %= MOD;
        }
    }

    x[v][0] += 1;


}

void computey(int v, int d){
    int i,all_paths,u;

    all_paths = 0;
    if(par[v] >= 0) all_paths = two_terms_exp(d,y[v]);

    for(i = 0; i < (int)children[v].size(); ++i){
    	u = children[v][i];
    	y[u][d] =	two_terms_exp(d,x[u]);
    	all_paths += y[u][d];
    	all_paths %= MOD;
    }

    for(i = 0; i < (int)children[v].size(); ++i){
    	u = children[v][i];
    	y[u][d] = all_paths-y[u][d];
    	if(y[u][d] < 0) y[u][d] += MOD;
    }

    for(i = 0; i < (int)children[v].size(); ++i) computey(children[v][i],d);
}

void compute(int v){
	int i,d;

	for(i = 0; i < (int)children[v].size(); ++i){
		compute(children[v][i]);
	}

	for(d = 0; d <= D; ++d){
		data_epar[v][d] = three_terms_exp(d,y[v],x[v]);
	}

}

void dfs(int v){
	int i,u;

	for(i = 0; i < (int)adj[v].size(); ++i){
		u = adj[v][i];
		if(u == par[v]) continue;
		par[u] = v;
		children[v].push_back(u);
		dfs(u);
	}
}

void init(){
	int i,k;

	choose[0][0] = 1;
	for(i = 0; i <= D; ++i){
		choose[i][0] = 1;
		for(k = 1; k <= i; ++k){
			choose[i][k] = choose[i-1][k] + choose[i-1][k-1];
			choose[i][k] %= MOD;
		}
	}

	par[0] = -1;
	dfs(0);

	for(i = 0; i < N-1; ++i){
		if(par[edges[i].first] == edges[i].second) continue;
		swap(edges[i].first,edges[i].second);
	}

	computex(0);
	for(i = 0; i < N; ++i) y[i][0] = N-x[i][0];
	for(i = 1; i <= D; ++i) computey(0,i);

	compute(0);
}



int main(){
	int i,u,v;

	scanf("%d%d",&N,&D);

	for(i = 0; i < N-1; ++i){
		scanf("%d%d",&u,&v);
		--u,--v;
		edges[i] = make_pair(u,v);
		adj[v].push_back(u);
		adj[u].push_back(v);
	}

	init();

	for(i = 0; i < N-1; ++i){
		v = edges[i].first;
		printf("%d\n",data_epar[v][D]);
	}

	return 0;
}
