#include <algorithm>
#include <set>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>

#define NMAX 10010
#define TMAX (1<<16)+10
#define KMAX 1000

#define LOGN 15

using namespace std;

int bit[TMAX][KMAX+10];
int lookup[NMAX];

inline int left(int x){ return (x+1)*2-1; }
inline int right(int x){ return (x+1)*2; }
inline int parent(int x){ return (x+1)/2-1; }

void update(int x, int val, int node){
	while(x <= KMAX){
		bit[node][x]+=val;
		x += (x&-x);
	}
}

int query(int x, int node){
	if(x <= 0) return 0;
	int sol = 0;

	while(x){
		sol += bit[node][x];
		x -= (x&-x);
	}

	return sol;
}

int A[NMAX];

void tree_init(int node, int s, int e){
	int i;

	for(i = s; i <= e; ++i){
		update(A[i],1,node);
	}

	if(s == e){
		lookup[s] = node;
		return;
	}
	tree_init(left(node),s,(s+e)/2);
	tree_init(right(node),(s+e)/2+1,e);
}

void tree_clear(int node, int s, int e){
	int i;

	for(i = s; i <= e; ++i){
		update(A[i],-1,node);
	}

	if(s == e){
		lookup[s] = node;
		return;
	}
	tree_clear(left(node),s,(s+e)/2);
	tree_clear(right(node),(s+e)/2+1,e);
}

int tree_query(int node, int s, int e, int i, int j, int k){

	if(s > j || e < i) return 0;

	int rank;
	if(s >= i && e <= j){
		rank = query(k-1,node);
		return rank;
	}

	int l,r;

	l = tree_query(left(node),s,(s+e)/2,i,j,k);
	r = tree_query(right(node),(s+e)/2+1,e,i,j,k);

	return l+r;
}

void tree_update(int i, int k){
	int x;
	x = lookup[i];
	update(A[i],-1,x);
	update(k,1,x);

	while(x){
		x = parent(x);
		update(A[i],-1,x);
		update(k,1,x);
	}
	A[i] = k;
}

int N;

int search(int k, int i, int j){
	int high,low,mid,less;

	low = 1;
	high = KMAX+1;

	while(low < high){
		mid = (low+high)/2;
		less = tree_query(0,0,N-1,i,j,mid);

		if(less >= k){
			high = mid;
		}else{
			low = mid+1;
		}
	}

	return low-1;
}


int main(){
	int i,j,k,q,t,test;

	scanf("%d",&test);


	while(test--){
		scanf("%d",&N);

		for(i = 0; i < N; ++i){
			scanf("%d",&A[i]);
		}


		tree_init(0,0,N-1);

		scanf("%d",&q);


		while(q--){
			scanf("%d",&t);
			if(t){
				scanf("%d%d",&i,&k);
				tree_update(i-1,k);
				continue;
			}
			scanf("%d%d%d",&i,&j,&k);
			printf("%d\n",search(k,i-1,j-1));
		}

		tree_clear(0,0,N-1);
	}

	return 0;
}


/*
 * 2
2
1 2
2
0 1 2 1
0 1 2 2
4
4 3 2 1
4
0 1 1 1
1 1 1
0 1 1 1
0 1 4 3
*/
