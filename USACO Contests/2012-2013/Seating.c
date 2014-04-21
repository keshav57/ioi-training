/*
 Created By: Malvika Joshi
 Problem: Seating (January-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=231
*/

#include <stdio.h>

#define MAXN 500010
#define MAXM 300010

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int max(int a, int b){ return a > b ? a : b; }

typedef struct { int lft,rht,ovr; } t_i;

t_i T[MAXN*3];
int N,M;

void init(int node, int s, int e){
	if(s == e){
		T[node].lft = T[node].ovr = T[node].rht = 1;
		return;
	}
	init(left(node),s,(s+e)/2);
	init(right(node),(s+e)/2+1,e);
	T[node].lft = T[node].ovr = T[node].rht = e-s+1;
}

int query(int node, int s, int e, int k){

	if(T[node].ovr < k)	return -1;


	if(T[node].lft >= k) return s;

	int l,r,e0,s0;

	l = left(node);
	r = right(node);

	s0 = query(l,s,(s+e)/2,k);
	if(s0 > 0) return s0;

	//split
	if(T[l].rht + T[r].lft >= k){
		e0 = (s+e)/2;
		s0 = e0-T[l].rht+1;
		return s0;
	}

	return query(r,(s+e)/2+1,e,k);
}

void update(int node, int s, int e, int i, int j, int state, int mstate){

	if(mstate < 0){
		if(T[node].ovr == 0) mstate = 0;
		if(T[node].ovr == e-s+1) mstate = 1;
	}

	if(j < s || i > e){
		if(mstate >= 0)	T[node].lft = T[node].ovr = T[node].rht = mstate*(e-s+1);
		return;
	}

	if(s >= i && e <= j){
		T[node].lft = T[node].ovr = T[node].rht = state*(e-s+1);
		return;
	}

	int l,r,n0,n1;

	l = left(node);
	r = right(node);

	update(l,s,(s+e)/2,i,j,state,mstate);
	update(r,(s+e)/2+1,e,i,j,state,mstate);

	n0 = ((s+e)/2)-s+1;
	n1 = e-((s+e)/2);

	T[node].lft = T[l].lft == n0 ? T[l].lft+T[r].lft : T[l].lft;
	T[node].rht = T[r].rht == n1 ? T[l].rht + T[r].rht : T[r].rht;

	T[node].ovr = max( max(T[l].ovr,T[r].ovr) ,T[l].rht+T[r].lft );
}

int main(){

	int k,i,j,st,t;
	char c;

	scanf("%d%d",&N,&M);

	init(0,0,N-1);

	t = 0;
	while(M--){
		scanf(" %c",&c);
		st = c == 'L';
		if(st){
			scanf("%d %d",&i,&j);
			update(0,0,N-1,i-1,j-1,st,-1);
		}else {
			scanf("%d",&k);
			i = query(0,0,N-1,k);
			if(i < 0){
				++t;
				continue;
			}
			update(0,0,N-1,i,(i+k-1),st,-1);
		}
	}

	printf("%d\n",t);

	return 0;
}
