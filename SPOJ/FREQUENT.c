/*
 Created By: Malvika Joshi
 Problem: Frequent Values
 Link: http://www.spoj.com/problems/FREQUENT/
*/

#include <stdio.h>

inline int left(int p){ return (p+1)*2 -1; }
inline int right(int p){ return (p+1)*2 ;  }
inline int parent(int x){ return (x+1)/2-1; }
inline int max(int a, int b){ return a > b ? a : b; }

typedef struct { int lc,rc,lv,rv,max; } node;

node const empty = {0,0,-1,-1,0};
node T[300000];
int A[100000];
int N,M;

void init(int x, int s, int e){

	if(s == e){
		T[x].lc = T[x].rc = T[x].max = 1;
		T[x].lv  = T[x].rv = A[s];
		return;
	}

	int l,r,split;

	l = left(x);
	r = right(x);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	split = T[l].rv == T[r].lv ? T[l].rc + T[r].lc : 0;

	T[x].lc = T[l].lv == T[r].lv ? split : T[l].lc;
	T[x].lv = T[l].lv;
	T[x].rc = T[r].rv == T[l].rv ? split : T[r].rc;
	T[x].rv = T[r].rv;

	T[x].max = max(split,max(T[l].max,T[r].max));
}

node query(int x, int s, int e, int i, int j){

	node lval,rval;

	if(i > e || j < s) return empty;

	if(s >= i && e <= j) return T[x];

	lval = query(left(x),s,(s+e)/2,i,j);
	rval = query(right(x),(s+e)/2+1,e,i,j);

	if(lval.lv == -1)	return rval;
	if(rval.lv == -1)	return lval;


	node temp;
	int split;

	split = lval.rv == rval.lv ? lval.rc + rval.lc : 0;

	temp.lc = lval.lv == rval.lv ? split : lval.lc;
	temp.lv = lval.lv;
	temp.rc = rval.rv == lval.rv ? split : rval.rc;
	temp.rv = rval.rv;

	temp.max = max(split,max(lval.max,rval.max));

	return temp;
}

int main(){
	int i,a,b;
	node q;

	while(1){
		scanf("%d",&N);
		if(!N) break;
		scanf("%d",&M);

		for(i = 0;i < N; i++){
			scanf("%d",&A[i]);
		}

		init(0,0,N-1);
		for(i = 0;i < M; i++){
			scanf("%d%d",&a,&b);
			q = query(0,0,N-1,a-1,b-1);
			printf("%d\n",q.max);
		}
	}


	return 0;
}
