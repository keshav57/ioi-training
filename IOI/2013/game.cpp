#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>

#define NMAX 2010
#define TMAX ((1<<12)+10)

#define NODEMAX 2000000
#define OUTMAX  2000000

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
	int left,right,s,e;
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

	int create_node2d(int s, int e){
		node2d tmp = {-1,-1,s,e,0};
		intree[innodes] = tmp;
		return innodes++;
	}

	int outnodes;
	int create_node(){
		node tmp = {-1,-1,-1};
		outtree[outnodes] = tmp;
		return outnodes++;
	}


	lli query_in(int node, int k){
		if(node < 0) return 0;
		int s,e;
		s = intree[node].s;
		e = intree[node].e;

		if(s > k || e < k) return 0;
		if(s == e){
			return intree[node].val;
		}
		return gcd( query_in(intree[node].left,k), query_in(intree[node].right,k) );
	}


	int split(int s, int e, int node1, int node2){
		//ASSUMES node1 comes before node 2 AND they are in the range

		//check if they spilt at this node

		int node;
		if(intree[node1].e <= (s+e)/2 && intree[node2].s > (s+e)/2){
			node = create_node2d(s,e);
			intree[node].left = node1;
			intree[node].right = node2;
			intree[node].val = gcd(intree[node1].val,intree[node2].val);
			return node;
		}

		if(intree[node1].e <= (s+e)/2){
			return split(s,(s+e)/2,node1,node2);
		}
		return split((s+e)/2+1,e,node1,node2);
	}


	void updatey(int xnode, int node, int j, int leaf, lli val){
		int s, e;
		s = intree[node].s;
		e = intree[node].e;

		if(s == e){
			//node already exisits
			if(leaf){
				intree[node].val = val;
//				cout << "added" << endl;
				return;
			}

			lli q1,q2;
			int leftx,rightx;
			leftx = outtree[xnode].left;
			rightx = outtree[xnode].right;
			q1 = leftx < 0 ? 0 : query_in(outtree[leftx].treepos,s);
			q2 = rightx < 0 ? 0 : query_in(outtree[rightx].treepos,s);
			intree[node].val = gcd(q1,q2);
			return;
		}

		if(j <= (s+e)/2){
			if(intree[node].left < 0){
				intree[node].left = create_node2d(j,j);
			}
			int node1 = intree[node].left,node2;

			if(intree[node1].s <= j && j <= intree[node1].e){
				updatey(xnode,intree[node].left,j,leaf,val);
			}else{
				node2 = create_node2d(j,j);
				intree[node2].val = val;
				if(intree[node1].s > intree[node2].s) swap(node1,node2);
				intree[node].left = split(s,(s+e)/2,node1,node2);
			}

		}else{
			if(intree[node].right < 0){
				intree[node].right = create_node2d(j,j);
			}
			int node1,node2;
			node1 = intree[node].right;

			if(intree[node1].s <= j && j <= intree[node1].e){
				updatey(xnode,intree[node].right,j,leaf,val);
			}else{
				node2 = create_node2d(j,j);
				intree[node2].val = val;
				if(intree[node1].s > intree[node2].s)swap(node1,node2);
				intree[node].right = split((s+e)/2+1,e,node1,node2);
			}
		}

		lli l,r;

		l = intree[node].left < 0 ? 0 : intree[intree[node].left].val;
		r = intree[node].right < 0 ? 0 : intree[intree[node].right].val;

		intree[node].val = gcd(l,r);
	}

	void updatex(int node, int s, int e, int i, int j, lli val){
		if(s > i || e < i || node < 0) return;


		if(s == e){
			if(outtree[node].treepos < 0){
				outtree[node].treepos = create_node2d(0,N-1);
			}
//			cout << s << " " << e << endl;
			updatey(node,outtree[node].treepos,j,1,val);
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
			outtree[node].treepos = create_node2d(0,N-1);
		}
		updatey(node,outtree[node].treepos,j,0,val);
	}

	lli queryy(int node,  int i, int j){
//		if(!tree[nodex][node]) return 0;
		if(node < 0) return 0;

		int s,e;
		s = intree[node].s;
		e = intree[node].e;

		if(s > j || e < i) return 0;

		if(s >= i && e <= j){
			return intree[node].val;
		}

		lli l,r;

		l = queryy(intree[node].left,i,j);
		r = queryy(intree[node].right,i,j);

		return gcd(l,r);
	}

	lli queryx(int node, int s, int e, int xi, int xj, int yi, int yj){
		if(s > xj || e < xi) return 0;
		if(node < 0) return 0;

		if(s >= xi && e <= xj){
			return queryy(outtree[node].treepos,yi,yj);
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
