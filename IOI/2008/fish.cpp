#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#define NMAX 500010
#define TMAX ((1<<20)+10)

using namespace std;

int mod;

class segment_tree{
private:
	int tree[TMAX];
	int lookup[NMAX];
	int N,mod;

	inline int left(int x){	return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	void tree_init(int node, int s, int e, int *A){
		if(s == e){
			tree[node] = A[s];
			lookup[s] = node;
			return;
		}

		int l,r;
		l = left(node);
		r = right(node);

		tree_init(l,s,(s+e)/2,A);
		tree_init(r,(s+e)/2+1,e,A);

		tree[node] = (1LL*tree[l]*tree[r])%mod;
	}

	int tree_query(int node, int s, int e, int i, int j){
		if(s > j || e < i) return 1;

		if(s >= i && e <= j) return tree[node];

		int l,r;

		l =tree_query(left(node),s,(s+e)/2,i,j);
		r = tree_query(right(node),(s+e)/2+1,e,i,j);

		return (1LL*l*r)%mod;
	}

public:

	void init(int n, int m, int *A){
		N = n;
		mod = m;
		tree_init(0,0,N-1,A);
	}

	int query(int i, int j){
		return tree_query(0,0,N-1,i,j);
	}

	int query_leaf(int i){
		return tree[lookup[i]];
	}

	void update(int i, int val){
		int x;
		x = lookup[i];
		tree[x] = val;

		while(x){
			x = parent(x);
			tree[x] = (1LL*tree[left(x)]*tree[right(x)])%mod;
		}
	}
};


segment_tree T1,T2;

pair<int,int> cat[NMAX];
pair<int,int> det[NMAX];
int typ_map[NMAX];

int K,N;

int compute(){
	int i,j,val,q1,q2,q3,tot,p;

	tot =0;
	j = N-1;
	for(i = K-1; i >= 0; --i){
		while(j >= 0 && cat[i].first < det[j].first*2){
			val = T1.query_leaf(det[j].second)-1;
			if(val) T1.update(det[j].second,val);					//otherwise all elements of this typ are already deleted
			val = T2.query_leaf(det[j].second)-1;
			T2.update(det[j].second,val);
			--j;
		}

		q1 = T1.query(0,K-1);

		val = T2.query_leaf(i);
		T2.update(i,1);
		p = lower_bound(cat,cat+K,make_pair(cat[i].second,-1))-cat;
		assert(p);
		q2 = T2.query(0,p-1);
		T2.update(i,val);

		T1.update(i,1);
		q3 = T1.query(0,K-1);

		tot += q1+q2-q3;
		tot %= mod;
		if(tot < 0) tot += mod;
	}

	return tot;
}

int compare(pair<int,int> a, pair<int,int> b){
	return det[a.first] < det[b.first];
}

vector<int> len[NMAX];

int A[NMAX];

void init(){
	int i,k;

	sort(det,det+N);
	for(i = 0; i < N; ++i){
		len[det[i].second].push_back(i);
	}

	for(i = 0; i < K; ++i){
		for(k = 0; k < (int)len[i].size(); ++k){
			if(det[len[i][k]].first*2 > det[len[i].back()].first){
				break;
			}
		}
		assert(k < (int)len[i].size());
		cat[i] = make_pair(len[i].back(),det[len[i][k]].first*2);
	}

	sort(cat,cat+K,compare);

	for(i = 0; i < K; ++i){
		typ_map[det[cat[i].first].second] = i;
		cat[i].first = det[cat[i].first].first;
	}

	for(i = 0; i < N; ++i){
		det[i].second = typ_map[det[i].second];
		A[det[i].second]++;
	}

	for(i = 0; i < K; ++i){
		++A[i];
	}

	T1.init(K,mod,A);
	T2.init(K,mod,A);
}

int main(){

	int i;

	scanf("%d%d%d",&N,&K,&mod);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&det[i].first,&det[i].second);
		--det[i].second;
	}

	init();
	printf("%d\n",compute());

	return 0;
}
