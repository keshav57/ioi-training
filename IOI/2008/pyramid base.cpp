#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>

#define NMAX 1000010
#define PMAX 400010
#define TMAX ((1<<21)+10)
#define x first
#define y second

typedef long long lli;
using namespace std;

class segment_tree1{
private:

	int tree[TMAX];
	int max_left[TMAX];
	int max_right[TMAX];
	int inc[TMAX];
	int N;

	inline int left(int p){ return (p+1)*2-1; }
	inline int right(int p){ return (p+1)*2; }

	void tree_init(int node, int s, int e){
		max_left[node] = max_right[node] = tree[node] = (e-s)+1;
		inc[node] = 0;

		if(s == e){
			return;
		}

		tree_init(left(node),s,(s+e)/2);
		tree_init(right(node),(s+e)/2+1,e);
	}

	void tree_update(int node, int s, int e, int i, int j, int k){
		if(s > j || e < i) return;

		if(s >= i && e <= j){
			inc[node] += k;
			assert(inc[node] >= 0);
			return;
		}

		int l,r,nl,nr;

		l = left(node);
		r = right(node);

		tree_update(l,s,(s+e)/2,i,j,k);
		tree_update(r,(s+e)/2+1,e,i,j,k);

		if(inc[r] && inc[l]){						//decrement will be after incrementing it and on the same range so inc[i] is always >= 0
			tree[node] = max_left[node] = max_right[node] = 0;
			return;
		}

		if(inc[l]){
			tree[node] = tree[r], max_left[node] =0, max_right[node] = max_right[r];
			return;
		}

		if(inc[r]){
			tree[node] = tree[l], max_left[node] = max_left[l], max_right[node] = 0;
			return;
		}

		nl = ((s+e)/2-s)+1;
		nr = e-((s+e)/2+1)+1;

		tree[node] = max(max_right[l]+max_left[r],max(tree[l],tree[r]));
		max_left[node] = max_left[l] == nl ? max_left[l]+max_left[r] : max_left[l];
		max_right[node] = max_right[r] == nr ? max_right[r]+max_right[l] : max_right[r];
	}

public:

	void init(int n){
		N = n;
		tree_init(0,0,N-1);
	}

	int query(){
		return inc[0] ? 0 : tree[0];
	}

	void update(int i, int j, int k){
		tree_update(0,0,N-1,i,j,k);
	}
};

struct seg1{
	int x,y0,y1;
	bool operator<(const seg1& rhs)const{
		return (x < rhs.x);
	}
};

seg1 start[PMAX];
seg1 end[PMAX];

int N,M,B,P;

segment_tree1 tree;

int sweep(){
	int g,len,i,st,en;

	len = 0;
	g = -1;
	st = 0;
	en = 0;

	for(i = 0; i < M; ++i){

		while(g < i || (g < M && tree.query() >= g-i+1)){
			++g;
			while(st < P && start[st].x <= g){
				tree.update(start[st].y0,start[st].y1,1);
				++st;
			}
		}

		--g;
		len = max(len,g-i+1);

		while(en < P && end[en].x <= i){
			tree.update(end[en].y0,end[en].y1,-1);
			++en;
		}
	}

	return len;
}


class segment_tree{
private:
	lli tree[TMAX];
	lli inc[TMAX];
	int N;

	inline int left(int p){ return (p+1)*2-1; }
	inline int right(int p){ return (p+1)*2; }

	void tree_update(int node, int s, int e, int i, int j, int k){
		if(s > j || e < i) return;

		if(s >= i && e <= j){
			tree[node] += k;
			inc[node] += k;
			return;
		}

		int l,r;

		l = left(node);
		r = right(node);

		tree_update(l,s,(s+e)/2,i,j,k);
		tree_update(r,(s+e)/2+1,e,i,j,k);

		tree[node] = min(tree[l],tree[r])+inc[node];
	}

public:

	void init(int n){
		memset(tree,0,sizeof(tree));
		memset(inc,0,sizeof(inc));
		N = n;
	}

	lli query(){
		return tree[0];
	}

	void update(int i, int j, int k){
		tree_update(0,0,N-1,i,j,k);
	}
};

struct vertical_seg{
	int x,y0,y1,inc;

	bool operator<(const vertical_seg &rhs) const{
		return (x < rhs.x);
	}
};

vertical_seg seg[PMAX*2];
int S;

pair<pair<int,int> , pair<int,int> > rect[PMAX];
int cost[PMAX];

segment_tree T;

void create_seg(int k){
	int i;

	S = 0;
	for(i = 0; i < P; ++i){
		seg[S].x = max(0,rect[i].first.x-k);
		seg[S].y0 = max(0,rect[i].first.y-k);
		seg[S].y1 = rect[i].second.y;
		seg[S++].inc = cost[i];

		seg[S] = seg[S-1];
		seg[S].x = rect[i].second.x+1;
		seg[S++].inc = -cost[i];
	}

	sort(seg,seg+S);
}

int is_pos(int k){
	int i;
	lli cost;

	create_seg(k);

	if(k) T.update(N-k,N-1,B+1);

	cost = B+1;
	for(i = 0; i < S; ++i){
		T.update(seg[i].y0,seg[i].y1,seg[i].inc);
		if(i < S-1 && seg[i].x == seg[i+1].x) continue;
		if(seg[i].x+k >= M) continue;
		cost = min(cost,T.query());
	}

	if(k) T.update(N-k,N-1,-(B+1));
	assert(T.query() == 0);
	return cost <= B;
}


int search(){
	int low,high,mid;

	low = 1;
	high = min(M,N)+1;

	while(low < high){
		mid = (low+high)/2;
		if(is_pos(mid-1)){
			low = mid+1;
		}else{
			high = mid;
		}
	}

	return low-1;
}


int main(){
	int i,c;

	scanf("%d%d%d%d",&M,&N,&B,&P);

	if(!B){
		for(i = 0; i < P; ++i){
			scanf("%d%d%d%d%d",&start[i].x,&start[i].y0,&end[i].x,&start[i].y1,&c);
			--start[i].x, --end[i].x, --start[i].y0, --start[i].y1;
			end[i].y0 = start[i].y0, end[i].y1 = start[i].y1;
		}

		tree.init(N);

		sort(start,start+P);
		sort(end,end+P);

		printf("%d\n",sweep());
		return 0;
	}

	T.init(N);

	for(i = 0; i < P; ++i){
		scanf("%d%d%d%d%d",&rect[i].first.x,&rect[i].first.y,&rect[i].second.x,&rect[i].second.y,&cost[i]);
		--rect[i].first.x, --rect[i].first.y, --rect[i].second.x, --rect[i].second.y;
	}

	printf("%d\n",search());

	return 0;
}
