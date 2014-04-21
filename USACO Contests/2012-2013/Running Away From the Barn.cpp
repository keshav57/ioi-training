/*
 Created By: Malvika Joshi
 Problem: Running Away Form the Barn (December-2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=213
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

#define NMAX 200010
#define TMAX (1<<19)

typedef long long lli;

using namespace std;

inline int left(int x){ return (x+1)*2-1; }
inline int right(int x){ return (x+1)*2; }

lli dist[NMAX];
vector<int> child[NMAX];
lli weight[NMAX];

int endtime[NMAX];
int starttime[NMAX];

int N;
lli L;
int cur_time;

int compare(int a, int b){
	return dist[a] < dist[b];
}

vector<int> tree[TMAX];

void tree_init(int node, int s, int e){

	if(s == e){
		tree[node].push_back(s);
		return;
	}

	int l,r;
	l = left(node);
	r = right(node);

	tree_init(l,s,(s+e)/2);
	tree_init(r,(s+e)/2+1,e);


	tree[node].resize(e-s+1);
	merge(tree[l].begin(),tree[l].end(),tree[r].begin(),tree[r].end(),tree[node].begin(),compare);
}

int tree_query(int node , int s, int e, int i, int j, lli k){
	if(s > j || e < i) return 0;

	if(s >= i && e <= j){
		return upper_bound(tree[node].begin(),tree[node].end(),k,compare)-tree[node].begin();
	}

	return tree_query(left(node),s,(s+e)/2,i,j,k) + tree_query(right(node),(s+e)/2+1,e,i,j,k);
}


void init(int v){
	int i,u;

	for(i = 0; i < (int)child[v].size(); ++i){
		u = child[v][i];
		starttime[u] = ++cur_time;
		dist[starttime[u]] = dist[starttime[v]]+weight[u];
		init(u);
	}

	endtime[v] = cur_time;
}


int main(){

	int i,p;

	scanf("%d%lld",&N,&L);

	for(i = 1; i < N; ++i){
		scanf("%d%lld",&p,&weight[i]);
		child[p-1].push_back(i);
	}

	init(0);
	tree_init(0,0,N-1);

	for(i = 0 ; i < N; ++i){
		dist[N] = dist[starttime[i]]+L;
		printf("%d\n",tree_query(0,0,N-1,starttime[i],endtime[i],N));
	}

	return 0;
}
