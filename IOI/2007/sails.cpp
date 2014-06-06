#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 100010
#define TMAX ((1<<18)+10)

using namespace std;

class segment_tree{
private:

	int min_el[TMAX];
	int max_el[TMAX];
	int lookup[NMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	void tree_init(int node, int s, int e){
		min_el[node] = N, max_el[node] = -1;
		if(s == e){
			lookup[s] = node;
			return;
		}
		tree_init(left(node),s,(s+e)/2);
		tree_init(right(node),(s+e)/2+1,e);
	}


	//1 for min 0 for max
	int tree_query(int node, int s, int e, int i, int j, int typ){
		if(s > j || e < i) return typ ? N : -1;
		if(s >= i && e <= j) return typ ? min_el[node] : max_el[node];

		int l,r;
		l = tree_query(left(node),s,(s+e)/2,i,j,typ);
		r = tree_query(right(node),(s+e)/2+1,e,i,j,typ);

		return typ ? min(l,r) : max(l,r);
	}

public:

	void init(int n){
		N = n;
		tree_init(0,0,N-1);
	}

	void update(int i, int val){
		int x;

		x = lookup[i];
		min_el[x] = val ? i : N;
		max_el[x] = val ? i : -1;

		while(x){
			x = parent(x);
			min_el[x] = min(min_el[left(x)],min_el[right(x)]);
			max_el[x] = max(max_el[left(x)],max_el[right(x)]);
		}
	}

	int query(int i, int j, int typ){
		return tree_query(0,0,N-1,i,j,typ);
	}
};


segment_tree T;

int height[NMAX];
int sails[NMAX];

int filled[NMAX];

int order[NMAX];
int N;

int compare(int a, int b){
	return height[a] < height[b];
}

void add_sails(int mast){
	int n,k,pr,nx,i;

	n = height[mast]-1;
	k = sails[mast];
	T.update(n,++filled[n]);


	i = n-k;
	if(i < 0) return;
	nx = T.query(i,n,1);
	pr = T.query(0,i,0);

//	assert(nx <= n);

	if(k) T.update(nx,--filled[nx]);
	T.update(pr+nx-i,++filled[pr+nx-i]);
	if(pr >= 0) T.update(pr,--filled[pr]);
}

int main(){

	int i,sum;
	long long ineff;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&height[i],&sails[i]);
		order[i] = i;
	}

	sort(order,order+N,compare);

	T.init(height[order[N-1]]);
	for(i =0 ; i < N; ++i){
		add_sails(order[i]);
	}

	ineff = 0;

	sum = 0;
//	cout << N << endl;
	for(i = height[order[N-1]]-1; i >= 0; --i){
		sum += filled[i];
//		cout << sum << " " << endl;
		ineff += 1LL*sum*(sum-1);
	}

	ineff /= 2;

	printf("%lld\n",ineff);

	return 0;
}
