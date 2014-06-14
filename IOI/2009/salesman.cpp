#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 500010
#define POSMAX 500005

#define UP(i) ((i)*U)
#define DN(i) (-(i)*D)
#define TMAX ((1<<20)+10)

#define time(i) (det[(i)].first)
#define pos(i) (det[(i)].second.first)
#define cost(i) (det[(i)].second.second)

using namespace std;
typedef pair<int, pair<int,int> > pi3;

class segment_tree{
private:

	int tree[TMAX];
	int lookup[NMAX];
	int N;

	inline int left(int x){ return (x+1)*2-1; }
	inline int right(int x){ return (x+1)*2; }
	inline int parent(int x){ return (x+1)/2-1; }

	void init(int node, int s, int e){
		tree[node] = -(1e9);
		if(s == e){
			lookup[s] = node;
			return;
		}
		init(left(node),s,(s+e)/2);
		init(right(node),(s+e)/2+1,e);
	}

	int tree_query(int node, int s, int e, int i, int j){
		if(s > j || e < i) return -(1e9);
		if(s >= i && e <= j) return tree[node];

		int l,r;

		l = tree_query(left(node),s,(s+e)/2,i,j);
		r = tree_query(right(node),(s+e)/2+1,e,i,j);

		return max(l,r);
	}

public:

	segment_tree(){
		N = POSMAX;
		init(0,0,N-1);
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

pi3 det[NMAX];			// time pos cost

int dp[NMAX];
int up[NMAX];
int dn[NMAX];

int go_up[NMAX];
int go_dn[NMAX];

int N,D,U,S;

segment_tree upstream,downstream;

inline int dist(int a, int b){
	return a < b ? DN(a)-DN(b) : UP(a)-UP(b);
}

int compute(){

	int i,k,st;

	st = 0;
	for(i = 0; i <= N; ++i){
		dp[i] = -dist(pos(i),S);
		dp[i] = max(dp[i], max(upstream.query(0,pos(i))-UP(pos(i)), downstream.query(pos(i),POSMAX-2)-DN(pos(i))) ) + cost(i);


		if(i < N && time(i) == time(i+1)) continue;

		go_up[st] = 0;
		up[st] = dp[st];

		for(k = st+1; k <= i; ++k){
			go_up[k] = max(0,go_up[k-1]-dist(pos(k),pos(k-1))-dist(pos(k-1),pos(k))+cost(k-1));
			up[k] = max(dp[k],up[k-1]-dist(pos(k),pos(k-1))+cost(k));
		}

		go_dn[i] = 0;
		dn[i] = dp[i];
		for(k = i-1; k >= st; --k){
			go_dn[k] = max(0,go_dn[k+1]-dist(pos(k),pos(k+1))-dist(pos(k+1),pos(k))+cost(k+1));
			dn[k] = max(dp[k],dn[k+1]-dist(pos(k),pos(k+1))+cost(k));
		}

		for(k = st; k <= i; ++k){
			dp[k] = max(up[k]+go_dn[k],dn[k]+go_up[k]);
			upstream.update(pos(k),dp[k]+UP(pos(k)));
			downstream.update(pos(k),dp[k]+DN(pos(k)));
		}


		st = i+1;
	}

	return dp[N];
}

int compare(pi3 a, pi3 b){
	return (a.first == b.first ? a.second < b.second : a.first > b.first);
}
//sort order : decreasing order of time, increasing order of downstream distance


int main(){
	int i;

	scanf("%d%d%d%d",&N,&U,&D,&S);

	pos(0) = S;
	for(i = 1; i <= N; ++i){
		scanf("%d%d%d",&time(i),&pos(i),&cost(i));
	}

	sort(det,det+N+1,compare);

	printf("%d\n",compute());

	return 0;
}
