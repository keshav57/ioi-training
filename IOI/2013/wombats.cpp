#include <cassert>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define NMAX 210
#define MMAX 5010
#define TMAX ((1<<10)+10)

int mid[NMAX][NMAX];
int M,N;

void merge(int (&p1)[NMAX][NMAX], int (&p2)[NMAX][NMAX], int (&sol)[NMAX][NMAX]){
	int i,j,k,n,dist,k1,k2;

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			sol[i][j] = (1e9)+5;
		}
	}

	//no path = (1e9)+5

	for(i = 0 ; i < N; ++i){
		j = i;
		mid[i][j] = -1;
		for(k = 0; k < N; ++k){
			dist = p1[i][k] + p2[k][j];
			if(mid[i][j] < 0 || sol[i][j] > dist){
				sol[i][j] = dist;
				mid[i][j] = k;
			}
		}
	}

	int dir;

	for(n = 1; n < N; ++n){
		for(dir = -1; dir < 2; ++++dir){
			for(i = 0; i < N; ++i){
				j = i+dir*n;

				if(j < 0 || j >= N) continue;

				if(dir > 0){
					k1 = j ? mid[i][j-1] : 0;
					k2 = i < N-1 ? mid[i+1][j] : N-1;
				}else{
					k1 = i ? mid[i-1][j] : 0;
					k2 = j < N-1 ? mid[i][j+1] : N-1;
				}

				for(k = k1; k <= k2; ++k){
					dist = p1[i][k] + p2[k][j];
					if(mid[i][j] < 0 || dist < sol[i][j]){
						sol[i][j] = dist;
						mid[i][j] = k;
					}
				}
			}
		}
	}
	//merge two segment tree nodes
}

int adj[MMAX][NMAX][3];

/*
 0 left
 1 right
 2 down
*/

int pref[NMAX];

int get_sum(int i, int j){
	return pref[j]-pref[i];
}

void base_case(int r1, int r2, int (&sol)[NMAX][NMAX]){
	int i,j;


	for(i =0 ; i< N; ++i){
		for(j = 0; j < N; ++j){
			sol[i][j] = (1e9)+5;
		}
	}

	for(i = 1; i < N; ++i){
		pref[i] = adj[r2][i][0] + pref[i-1];
	}

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			sol[i][j] = min(sol[i][j],adj[r1][i][2]+get_sum(min(i,j),max(i,j)));
			if(i) sol[i][j] = min(sol[i][j],sol[i-1][j]+adj[r1][i][0]);
		}
	}

	for(i = N-1; i >=0 ; --i){
		for(j = 0; j < N; ++j){
			sol[i][j] = min(sol[i][j],adj[r1][i][2]+get_sum(min(i,j),max(i,j)));
			if(i < N-1) sol[i][j] = min(sol[i][j],sol[i+1][j]+adj[r1][i][1]);
		}
	}

	//only two rows : merge them
}


class segment_tree{
private:
	int tree[TMAX][NMAX][NMAX];
	int st[TMAX];
	int en[TMAX];
	int lookup[MMAX][2];
	int upd[MMAX];
	int N,M;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }


	int leaves_extended[35][NMAX][NMAX];
	void compute_recursively(int node, int s, int e){
		if(e-s == 1){
			base_case(s,e,leaves_extended[node]);
			return;
		}

		int l,r;
		l = left(node);
		r = right(node);

		compute_recursively(l,s,(s+e)/2);
		compute_recursively(r,(s+e)/2,e);

		merge(leaves_extended[l],leaves_extended[r],leaves_extended[node]);
	}

	void compute_leaf(int node){
		compute_recursively(0,st[node],en[node]);
		int i,j;

		for(i = 0; i < N; ++i){
			for(j = 0; j < N; ++j){
				tree[node][i][j] = leaves_extended[0][i][j];
			}
		}
	}


	void tree_init(int node, int s, int e){
		st[node] = s;
		en[node] = e;

		if(e-s <= 10){
			compute_leaf(node);
			for(int i=s; i<=e; ++i) lookup[i][upd[i]++]=node;
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		tree_init(l,s,(s+e)/2);
		tree_init(r,(s+e)/2,e);

		merge(tree[l],tree[r],tree[node]);
	}

	void tree_update(int node){
		int x;

		x = node;
		compute_leaf(node);

		while(x){
			x = parent(x);
			merge(tree[left(x)],tree[right(x)],tree[x]);
		}

	}

public:

	void init(int m, int n){
		N = n;
		M = m;
		tree_init(0,0,M-1);
	}

	int query(int i, int j){
		return tree[0][i][j];
	}


	void update(int x){
		int i;
		for(i = 0; i < upd[x]; ++i){
			tree_update(lookup[x][i]);
		}
	}
};


segment_tree T;

int main(){
	int i,j;

//	memset(adj,-1,sizeof(adj));

	scanf("%d%d",&M,&N);

	for(i =0 ; i < M; ++i){
		for(j =0 ; j < N-1; ++j){
			scanf("%d",&adj[i][j][1]);
			adj[i][j+1][0] = adj[i][j][1];
		}
	}

	for(i = 0; i < M-1; ++i){
		for(j = 0; j < N; ++j){
			scanf("%d",&adj[i][j][2]);
		}
	}

	T.init(M,N);

	int q;

	scanf("%d",&q);

	int typ;
	while(q--){
		scanf("%d",&typ);
		scanf("%d%d",&i,&j);

		if(typ == 1){
			scanf("%d",&adj[i][j][1]);
			adj[i][j+1][0] = adj[i][j][1];
			T.update(i);
			continue;
		}

		if(typ == 2){
			scanf("%d",&adj[i][j][2]);
			T.update(i);
			continue;
		}

		printf("%d\n",T.query(i,j));
	}


	return 0;
}
