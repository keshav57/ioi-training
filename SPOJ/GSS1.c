/*
 Created By: Malvika Joshi
 Problem: Can you answer these queries I
 Link: http://www.spoj.com/problems/GSS1/
*/

#include <stdio.h>

#define inf 2000000000

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int max(int a, int b){ return a > b ? a : b; }

typedef struct { int l,r,m,sum; } node;

node T[150010];
int A[50010];
node const empty = {inf,inf,inf,inf};
int N,M;

void init(int x, int s, int e){

	if(s == e){
		T[x].l = T[x].r = T[x].m = T[x].sum = A[s];
		return;
	}

	int l,r,split;

	l = left(x);
	r = right(x);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	split = T[l].r + T[r].l;

	T[x].l = max(T[l].l,T[l].sum+T[r].l);
	T[x].r = max(T[r].r,T[r].sum+T[l].r);

	T[x].m = max(split,max(T[l].m,T[r].m));
	T[x].sum = T[l].sum + T[r].sum;
}

node query(int x, int s, int e, int i, int j){
	if(i > e || j < s) return empty;

	if(s >= i && e <= j) return T[x];

	node c1,c2,temp;
	int split;

	c1 = query(left(x),s,(s+e)/2,i,j);
	c2 = query(right(x),(s+e)/2+1,e,i,j);

	if(c1.sum == inf) return c2;
	if(c2.sum == inf) return c1;

	split = c1.r + c2.l;

	temp.l = max(c1.l,c1.sum+c2.l);
	temp.r = max(c2.r,c2.sum+c1.r);
	temp.sum = c1.sum+c2.sum;
	temp.m = max(split,max(c1.m,c2.m));

	return temp;
}

int main(){
	int i,a,b;

	scanf("%d",&N);
	for(i = 0;i < N; i++) scanf("%d",&A[i]);

	init(0,0,N-1);

	node q;

	scanf("%d",&M);
	for(i = 0;i < M; i++){
		scanf("%d%d",&a,&b);
		q = query(0,0,N-1,a-1,b-1);
		printf("%d\n", q.m);
	}

	return 0;
}
