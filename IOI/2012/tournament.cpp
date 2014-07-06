#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 100010

using namespace std;

class bit{
private:

	int tree[NMAX];
	int N,msb;

	int read(int x){
		int sum;
		sum = tree[0];
		for(;x;x-=(x&-x)) sum += tree[x];
		return sum;
	}

public:
	void update(int x, int val){
		if(!x){
			tree[x] += val;
			return;
		}
		for(;x<N; x+=(x&-x)) tree[x] += val;
	}

	void init(int n){
		N = n;
		while(n--){
			update(n,1);
		}
		msb = 32-__builtin_clz(N);
	}

	int search(int val){
		int i,n;
		val -= tree[0];
		if(!val) return 0;

		n = 1<<msb;
		i = 0;
		while(n){
			if(i+n < N && tree[i+n] < val){		//lower_bound
				i += n;
				val -= tree[i];
			}
			n >>= 1;
		}


		return i+1;
	}
};

int node[NMAX];
int next[NMAX];

int par[NMAX*2];			//0 through N-1 nodes are leaves
vector<int> child[NMAX*2];

int lev[NMAX];
pair<int,int> rounds[NMAX];
int R;

int V,N;

bit T;

void insert_interval(int s, int e){

	int i,n,k,st;

	n = e-s+1;
	st = T.search(s+1);

	i = st;


	for(k = 0; k < n; ++k){
		assert(i >= 0);
		par[node[i]] = V;
		child[V].push_back(node[i]);
		if(i^st) T.update(i,-1);
		i = next[i];
	}

	next[st] = i;
	node[st] = V;
	V++;
}

class lca_table{
private:

	int ances[NMAX*2][20];
	int N,log;

public:
	void init(int *par, int n){
		N = n;
		int i,k;

		memset(ances,-1,sizeof(ances));
		for(i = 0; i < N; ++i) ances[i][0] = par[i];

		for(k = 1; (1<<k) <= N; ++k){
			for(i =0 ; i < N; ++i){
				ances[i][k] = ances[i][k-1] < 0 ? -1 : ances[ances[i][k-1]][k-1];
			}
		}

		log = k;
	}

	int query(int u, int v, int *lev){
		if(lev[u] < lev[v]) swap(u,v);

		int k;

		for(k = log-1; k >= 0; --k){
			if(ances[u][k] < 0 || lev[ances[u][k]] < lev[v]) continue;
			u = ances[u][k];
		}

		if(u == v) return u;

		for(k = log-1; k >= 0; --k){
			if(ances[u][k] == ances[v][k]) continue;
			u = ances[u][k];
			v = ances[v][k];
		}

		return ances[u][0];
	}

};

void dfs(int v){
	int i;

	lev[v] = lev[par[v]] + 1;

	for(i = 0; i < (int)child[v].size(); ++i){
		dfs(child[v][i]);
	}
}

lca_table L;

void init(){
	int i;

	memset(par,-1,sizeof(par));
	for(i = 0; i < N; ++i){
		node[i] = i;
		next[i] = i+1 < N ? i+1 : -1;
	}

	T.init(N);
	V = N;

	for(i =0 ; i < R; ++i){
		insert_interval(rounds[i].first,rounds[i].second);
	}

	dfs(V-1);	//V-1 will be the root

	L.init(par,V);
}

int win[NMAX];
int rank;

int A[NMAX];

void compute(){
	int i,l;
	/* TODO:
	 * Find the f(i) and g(i) and query the lca table
	 * compute the sol
	 */

	int pre;
	pre=  -1;

	for(i = 0; i < N; ++i){
		pre = (i && A[i-1] > rank) ? i-1 : pre;

		if(pre < 0){
			win[i] = lev[i];
			continue;
		}
		l = L.query(pre,i,lev);
		win[i] = lev[i]-lev[l];
	}

	pre = -1;
	for(i = N-1; i >= 0; --i){
		pre = (i < N-1 && A[i] > rank) ? i+1 : pre;
		if(pre < 0) continue;
		l = L.query(pre,i,lev);
		win[i] = min(win[i],lev[i]-lev[l]);
	}
}

int main(){

	int i;

	scanf("%d%d",&N,&R);
	scanf("%d",&rank);

	for(i = 0; i < N-1; ++i) scanf("%d",&A[i]);

	for(i =0 ; i < R; ++i){
		scanf("%d%d",&rounds[i].first,&rounds[i].second);
	}

	init();
	compute();

	int w =0,pos = -1;

	for(i = 0; i < N; ++i){
		if(win[i] > w) w = win[i],pos = i;
	}

	printf("\n%d\n",pos);

	return 0;
}
