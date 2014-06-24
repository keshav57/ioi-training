#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <map>

using namespace std;


#define NMAX 200010
#define CMAX 600010
#define TMAX ((1<<21)+10)

class segment_tree{
private:
	int tree[TMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }

	void tree_init(int node, int s, int e, int *A){
		if(s == e){
			tree[node] = A[s];
			return;
		}
		int l,r;
		l = left(node), r=  right(node);
		tree_init(l,s,(s+e)/2,A);
		tree_init(r,(s+e)/2+	1,e,A);
		tree[node] = max(tree[l],tree[r]);
	}

	int tree_query(int node, int s, int e, int i, int j){
		if(s > j || e < i) return -1;
		if(s >= i && e <= j) return tree[node];
		return max(tree_query(left(node),s,(s+e)/2,i,j),
				tree_query(right(node),(s+e)/2+1,e,i,j));
	}

public:

	void init(int n, int *A){
		N = n;
		tree_init(0,0,N-1,A);
	}

	int query(int i, int j){
		if(j < i) return -1;
		return tree_query(0,0,N-1,i,j);
	}
};

class BIT{
private:
	int tree[NMAX];
	int N;

	int read(int x){
		if(x < 0) return 0;
		int sum = tree[0];

		while(x){
			sum += tree[x];
			x -= (x&-x);
		}

		return sum;
	}

public:

	void init(int n){
		memset(tree,0,sizeof(tree));
		N = n;
	}

	void update(int x, int val){
		if(!x){
			tree[x] += val;
			return;
		}

		while(x < N){
			tree[x] += val;
			x += (x&-x);
		}
	}

	int query(int i, int j){
		if(j < i) return 0;
		return read(j)-read(i-1);
	}
};

segment_tree T;

pair<int,int> card[NMAX];
int A[NMAX];
int C,N,K;

int idx[CMAX];

int fix[NMAX];
int flip[NMAX];

pair<int,int> oper[NMAX+NMAX];

BIT bit;

void init(){
	int i;

	memset(idx,-1,sizeof(idx));
	for(i = 0; i < K; ++i){
		idx[A[i]] = i;
	}

	T.init(C,idx);

	for(i = 0; i < N; ++i){
		fix[i] = T.query(card[i].first,card[i].second-1);
	}

	for(i = 0; i < N; ++i){
		oper[i] = make_pair(card[i].first,i);
	}

	for(i = 0; i < K; ++i){
		oper[N+i] = make_pair(A[i],i+N);
	}

	sort(oper,oper+K+N);

	bit.init(K);

	int j;

	for(i = N+K-1; i >=0 ; --i){
		if(oper[i].second >= N){
			bit.update(oper[i].second-N,1);
			continue;
		}
		j = oper[i].second;
		flip[j] = bit.query(fix[j]+1,K-1);
	}

}

map<int,int> compr;
int lookup[CMAX];

int st[NMAX];

int main(){
	int i;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&card[i].first,&card[i].second);
		if(card[i].first > card[i].second) swap(card[i].first,card[i].second), st[i] = 1;
		compr[card[i].first] = 0;
		compr[card[i].second] = 0;
	}

	for(i =0 ; i < K; ++i){
		scanf("%d",&A[i]);
		compr[A[i]];
	}

	for(map<int,int>::iterator it = compr.begin(); it != compr.end(); ++it){
		it->second = C++;
		lookup[it->second] = it->first;
	}

	for(i = 0; i < N; ++i){
		card[i] = make_pair(compr[card[i].first],compr[card[i].second]);
//		cout << card[i].first << " " << card[i].second << endl;
	}

	for(i =0 ; i < K; ++i){
		A[i] = compr[A[i]];
//		cout << A[i] << endl;
	}


	init();

//	for(i = 0; i < N; ++i){
//		cout << flip[i] << " " << fix[i] << endl;
//	}

	long long sum = 0,add;
	for(i = 0; i < N; ++i){
		add = flip[i]&1 ? lookup[card[i].first] : lookup[card[i].second];
		if(fix[i] < 0 && !st[i]){
			add ^= lookup[card[i].first]^lookup[card[i].second];
		}
//		cout << add << endl;
		sum += add;
	}

	printf("%lld\n",sum);

	return 0;
}
