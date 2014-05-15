#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

#define SUM 2010
#define NMAX 1010
#define TMAX ((1<<12)+10)
#define MOD (int)((1e9)+7)

using namespace std;

int mat[NMAX][NMAX];

class segment_tree{
private:
	int tree[TMAX];
	int incr[TMAX];
	int M,N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }

	void tree_init(int node, int s, int e, int sum){
		incr[node] = 0;
		if(s == e){
			tree[node] = (sum-s >= 0 && sum-s < N) ? mat[s][sum-s] : 0;
			return;
		}
		int l,r;

		l = left(node);
		r = right(node);

		tree_init(l,s,(s+e)/2,sum);
		tree_init(r,(s+e)/2+1,e,sum);
		tree[node] = tree[l]+tree[r];
		tree[node]%= MOD;
	}

	int tree_query(int node, int s, int e, int i, int j, int val){
		if(s > j || e < i) return 0;

		if(s >= i && e<=j){
			return (tree[node]+((1LL*(e-s+1)*val)%MOD))%MOD;
		}

		int l,r,tmp;

		tmp = incr[node]+val;
		tmp %= MOD;
		l = tree_query(left(node),s,(s+e)/2,i,j,tmp);
		r = tree_query(right(node),(s+e)/2+1,e,i,j,tmp);

		return (l+r)%MOD;
	}

	void tree_update(int node, int s, int e, int i, int j, int val){
		if(s > j || e < i) return;

		if(s >= i && e <= j){
			incr[node] += val;
			incr[node] %= MOD;
			tree[node] += ((1LL*val*(e-s+1))%MOD);
			tree[node] %= MOD;
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		tree_update(l,s,(s+e)/2,i,j,val);
		tree_update(r,(s+e)/2+1,e,i,j,val);

		tree[node] = tree[l]+tree[r];
		tree[node] %= MOD;
		tree[node] += ((1LL*incr[node]*(e-s+1))%MOD);
		tree[node] %= MOD;
	}

public:
	void init(int m, int n, int sum){
		M = m;
		N = n;
		tree_init(0,0,M-1,sum);
	}

	int query(int i, int j){
		if(j < i) return 0;
		return tree_query(0,0,M-1,i,j,0);
	}

	void update(int i, int j, int val){
		if(j < i) return;
		tree_update(0,0,M-1,i,j,val);
	}
};

segment_tree buckets[SUM];

//min x1 z
//max x2 z

int query(int sum, int x1, int x2, int y1, int y2){
	int vx1,vx2;

	vx2 = min(sum-y1,x2);
	vx1 = max(sum-y2,x1);

//	cout << "for " << sum << " " << vx1 << " " << vx2 << endl;
	return buckets[sum].query(vx1,vx2);
}

void update(int sum, int x1, int x2, int y1, int y2, int val){
	int vx1,vx2;

	vx2 = min(sum-y1,x2);
	vx1 = max(sum-y2,x1);

	buckets[sum].update(vx1,vx2,val);
}

int N,M;

void init(){
	int i,j;

	for(j = 0; j < N+M-1; ++j){
		buckets[j].init(M,N,j);
	}
}

vector<int> fac;
int Q;

int main(){
	int i,j,b,x1,x2,y1,y2,val,k;

	scanf("%d%d%d",&M,&N,&Q);

	M++,N++;

	for(i = 1; i < M; ++i){
		for(j = 1; j < N; ++j){
			scanf("%d",&mat[i][j]);
		}
	}

	init();

	int sum;
	while(Q--){

		scanf("%d%d%d%d%d%d",&b,&x1,&y1,&x2,&y2,&k);
		fac.clear();

		for(i = 1; i*i <= k; ++i){
			if(k%i) continue;
			if(k/i != i) fac.push_back(k/i);
			fac.push_back(i);
		}

		if(b){
			sum = 0;
			for(i = 0; i < fac.size(); ++i){
				sum += query(fac[i],x1,x2,y1,y2);
				sum %= MOD;
			}
			printf("%d\n",sum);
			continue;
		}

		scanf("%d",&val);
		for(i = 0; i < fac.size(); ++i){
			update(fac[i],x1,x2,y1,y2,val);
		}

	}

	return 0;
}
