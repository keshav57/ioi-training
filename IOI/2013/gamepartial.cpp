#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>

#define NMAX 2010
#define TMAX ((1<<12)+10)

#define NODEMAX 20000000
#define OUTMAX 700000

using namespace std;

typedef long long lli;

lli gcd(lli a, lli b){
	if(!a || !b) return a^b;


	lli t;

	while(b){
		t = b;
		b = a%b;
		a = t;
	}

	return a;
}

struct node2d{
	int left,right;
	lli val;
};

struct node{
	int left,right,treepos;
};

class segtree_2d{
private:

//	lli tree[TMAX][TMAX];

	node2d intree[NODEMAX];
	node outtree[OUTMAX];

	int M,N;

//	inline int left(int x){ return (x+1)*2-1; }
//	inline int right(int x){ return (x+1)*2; }
//	inline int parent(int x){ return (x+1)/2-1; }

	int innodes;

	int create_node2d(){
		node2d tmp = {-1,-1,0};
		intree[innodes] = tmp;
		return innodes++;
	}

	int outnodes;
	int create_node(){
		node tmp = {-1,-1,-1};
		outtree[outnodes] = tmp;
		return outnodes++;
	}

	lli query_in(int node, int s, int e, int k){
		if(s > k || e < k) return 0;
		if(node < 0) return 0;
		if(s == e){
			return intree[node].val;
		}
		return gcd( query_in(intree[node].left,s,(s+e)/2,k), query_in(intree[node].right, (s+e)/2+1,e,k) );
	}


	void updatey(int xnode, int node, int s, int e, int j, int leaf, lli val){
		if(s > j || e < j || node < 0) return;

		if(s == e){
			if(leaf){
				intree[node].val = val;
				return;
			}

			lli q1,q2;
			int leftx,rightx;


			leftx = outtree[xnode].left;
			rightx = outtree[xnode].right;

			q1 = leftx < 0 ? 0 : query_in(outtree[leftx].treepos,0,N-1,s);
			q2 = rightx < 0 ? 0 : query_in(outtree[rightx].treepos,0,N-1,s);

			intree[node].val = gcd(q1,q2);
			return;
		}

		int l,r;


		if(intree[node].left < 0 && (j <= (s+e)/2)){
			l = create_node2d();
			intree[node].left = l;
		}

		if(intree[node].right < 0 && (j > (s+e)/2)){
			r = create_node2d();
			intree[node].right = r;
		}

		l = intree[node].left;
		r = intree[node].right;

		updatey(xnode,l,s,(s+e)/2,j,leaf,val);
		updatey(xnode,r,(s+e)/2+1,e,j,leaf,val);

		intree[node].val = gcd(intree[l].val,intree[r].val);
	}

	void updatex(int node, int s, int e, int i, int j, lli val){
		if(s > i || e < i || node < 0) return;


		if(s == e){
			if(outtree[node].treepos < 0){
				outtree[node].treepos = create_node2d();
			}
//			cout << s << " " << e << endl;
			updatey(node,outtree[node].treepos,0,N-1,j,1,val);
			return;
		}

		int l,r;

		if(outtree[node].left < 0 && i <= (s+e)/2){
			l = create_node();
			outtree[node].left = l;
		}
		if(outtree[node].right < 0 && i > (s+e)/2){
			r = create_node();
			outtree[node].right = r;
		}

		l = outtree[node].left;
		r = outtree[node].right;

		updatex(l,s,(s+e)/2,i,j,val);
		updatex(r,(s+e)/2+1,e,i,j,val);

		if(outtree[node].treepos < 0){
			outtree[node].treepos = create_node2d();
		}
		updatey(node,outtree[node].treepos,0,N-1,j,0,val);
	}

	lli queryy(int node, int s, int e, int i, int j){
		if(s > j || e < i) return 0;
//		if(!tree[nodex][node]) return 0;
		if(node < 0) return 0;

		if(s >= i && e <= j){
			return intree[node].val;
		}

		lli l,r;

		l = queryy(intree[node].left,s,(s+e)/2,i,j);
		r = queryy(intree[node].right,(s+e)/2+1,e,i,j);

		return gcd(l,r);
	}

	lli queryx(int node, int s, int e, int xi, int xj, int yi, int yj){
		if(s > xj || e < xi) return 0;
		if(node < 0) return 0;

		if(s >= xi && e <= xj){
			return queryy(outtree[node].treepos,0,N-1,yi,yj);
		}

		lli l,r;

		l = queryx(outtree[node].left,s,(s+e)/2,xi,xj,yi,yj);
		r = queryx(outtree[node].right,(s+e)/2+1,e,xi,xj,yi,yj);

		return gcd(l,r);
	}

	int root;
public:

	void init(int n, int m){
		N = n;
		M = m;
		innodes = outnodes = 0;
		root = create_node();
	}

	void update(int i, int j, lli val){
		updatex(root,0,M-1,i,j,val);
	}

	lli query(int xi, int xj, int yi, int yj){
		return queryx(root,0,M-1,xi,xj,yi,yj);
	}
};

segtree_2d T;
int M,N;
int A[NMAX][NMAX];

int Q;

int main(){
	int i,j,i1,j1;

	scanf("%d%d%d",&M,&N,&Q);

	int typ;
	lli val;
	
	cout << sizeof(node2d) << endl;

	T.init(N,M);
	while(Q--){
		scanf("%d",&typ);

		if(typ == 1){
			scanf("%d%d%lld",&i,&j,&val);
			T.update(i,j,val);
			continue;
		}

		if(typ == 2){
			scanf("%d%d%d%d",&i,&j,&i1,&j1);
			printf("%lld\n",T.query(i,i1,j,j1));
		}
	}

	return 0;
}
