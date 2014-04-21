/*
 Created By: Malvika Joshi
 Problem: Ball Machine (BOI-2013)
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <cstring>
#include <cassert>
#include <vector>

#define NMAX 100010
#define LOGN 18
#define TMAX (1<<LOGN)
#define INF (int)1e9

using namespace std;

class segment_tree{
private:

	int tree[TMAX];
	int lookup[NMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	void tree_init(int node, int s, int e){
		if(s == e){
			tree[node] = s;
			lookup[s] = node;
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		tree_init(l,s,(s+e)/2);
		tree_init(r,(s+e)/2+1,e);

		tree[node] = min(tree[l],tree[r]);
	}

public:

	void init(int n){
		N = n;
		tree_init(0,0,N-1);
	}

	void update(int i, int val){
		int x;

		x = lookup[i];
		tree[x] = val;

		while(x){
			x = parent(x);
			tree[x] = min(tree[left(x)],tree[right(x)]);
		}
	}

	int query(){
		return tree[0];
	}
};

class sparse_table{
private:
	int ancestor[NMAX][LOGN];
	int dist;

public:


	void init(int n, int *par){
		int i,j;

		memset(ancestor,-1,sizeof(int)*NMAX*LOGN);

		for(i = 0; i < n; ++i){
			ancestor[i][0] = par[i];
		}

		for(j = 1; j < LOGN; ++j){
			for(i =0 ; i < n ;++i){
				if(ancestor[i][j-1] < 0) continue;
				ancestor[i][j] = ancestor[ancestor[i][j-1]][j-1];
			}
		}
	}

	int query(int x, int *occ){
		int i;
		assert(occ[x]);

		dist = 0;
		for(i = LOGN-1; i >= 0; --i){
			if(ancestor[x][i] < 0 || !occ[ancestor[x][i]]) continue;
			x = ancestor[x][i];
			dist += (1<<i);
		}

		return x;
	}

	int get_dist(){
		return dist;
	}
};

vector<int> child[NMAX];
int ftime[NMAX];
int pos[NMAX];

int par[NMAX];

int occ[NMAX];
int id[NMAX];

int cur_time;

int N,Q,root;

segment_tree tree;
sparse_table ans_table;

int compare(int i, int j){
	return id[i] < id[j];
}

void dfs(int v){
	int i,u;

	for(i = 0; i < (int)child[v].size(); ++i){
		u = child[v][i];
		par[u] = v;
		dfs(u);
	}

	pos[cur_time] = v;
	ftime[v] = cur_time++;
}

int insert(int k){
	int reach,i;

	for(i = 0; i < k; ++i){
		reach = tree.query();
		assert(reach < cur_time);
		tree.update(reach,INF);
		occ[pos[reach]] = 1;
	}

	return pos[reach]+1;
}


int dfs0(int v){
	int sm,i;

	sm = v;

	for(i = 0; i < (int)child[v].size(); ++i){
		sm = min(sm,dfs0(child[v][i]));
	}

	id[v] = sm;
	return sm;
}

int remove(int x){
	int down;

	down = ans_table.query(x,occ);
	occ[down] = 0;
	tree.update(ftime[down],ftime[down]);

	return ans_table.get_dist();
}


void init(){
	int i;

	dfs0(root);

	for(i =0 ; i < N; ++i){
		sort(child[i].begin(),child[i].end(),compare);
	}

	dfs(root);
	assert(cur_time == N);
	tree.init(cur_time);
	ans_table.init(N,par);
}


int main(){
	int i,typ;

	scanf("%d%d",&N,&Q);

	for(i = 0; i < N; ++i){
		scanf("%d",&par[i]);
		--par[i];
		if(par[i] < 0){
			root = i;
			continue;
		}

		child[par[i]].push_back(i);
	}

	init();

	while(Q--){
		scanf("%d%d",&typ,&i);

		if(typ == 1){
			printf("%d\n",insert(i));
			continue;
		}

		printf("%d\n",remove(i-1));
	}

	return 0;
}
