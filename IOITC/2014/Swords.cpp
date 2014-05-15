#include <algorithm>
#include <iostream>
#include <cstdio>

#define NMAX 100010
#define TMAX ((1<<18)+10)

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
		tree[node] = -1;
		if(s == e){
			lookup[s] = node;
			return;
		}

		tree_init(left(node),s,(s+e)/2);
		tree_init(right(node),(s+e)/2+1,e);
	}

	int tree_query(int node, int s, int e, int i, int j){
		if(s > j || e < i) return -1;
		if(s >= i && e <= j){
			return tree[node];
		}

		return max( tree_query(left(node),s,(s+e)/2,i,j),\
				tree_query(right(node),(s+e)/2+1,e,i,j));
	}

public:

	void init(int n){
		N = n;
		tree_init(0,0,N-1);
	}

	int query(int i, int j){
		return tree_query(0,0,N-1,i,j);
	}

	void update(int i, int val){
		int x;
		x = lookup[i];
		tree[x] = val;

		while(x){
			x = parent(x);
			tree[x] = max(tree[left(x)],tree[right(x)]);
		}
	}
};



int N;
int dp[NMAX];

int D[NMAX];
int X[NMAX];

segment_tree T;

int compute(){
	int i,j;

	T.init(N+1);
	dp[N] = 0;

	T.update(N,N);

	for(i = N-1; i >= 0; --i){
		dp[i] = dp[i+1];	//dodge i

		dp[i] = max(dp[i],T.query(X[i]+1,min(N,X[i]+D[i]))-X[i]);
		T.update(i,dp[i]+i);
	}

	return dp[0];
}

int main(){
	int i;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&X[i],&D[i]);
		X[i] += i+1;
	}

	printf("%d\n",compute());

	return 0;
}
