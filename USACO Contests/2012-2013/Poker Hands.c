/*
 Created By: Malvika Joshi
 Problem: Poker Hands (March-2103 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=262
*/

#include <stdio.h>

#define MAXN 100010
#define MAXT 300010

typedef struct { int cmin,cmax,sub,typ; } t_e;
typedef struct { int s,e,m,sr; } q_e;

typedef long long lli;

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int parent(int x){ return (x+1)/2-1; }

inline int min(int a, int b){ return a < b ? a : b; }
inline int max(int a, int b){ return a > b ? a : b; }

inline q_e make_q(int s, int e, int m, int t){
	q_e r = { s,e,m,t };
	return r;
}

int A[MAXN];

t_e T[MAXT];
int N;

void init(int node, int s, int e, int t){

	if(s == e){
		T[node].cmin = T[node].cmax = A[s];
		T[node].sub = 0;
		T[node].typ = t;
		return;
	}

	int l,r;
	l = left(node);
	r = right(node);

	init(l,s,(s+e)/2,0);
	init(r,(s+e)/2+1,e,1);

	T[node].typ = t;
	T[node].sub = 0;
	T[node].cmin = min(T[l].cmin,T[r].cmin);
	T[node].cmax = max(T[l].cmax,T[r].cmax);
}

q_e query(int node, int s, int e, int sub, int sl){

	if(T[node].cmax - sub <= 0)	return make_q(-1,-1,0,0);
	if(T[node].cmin - sub > 0){
		return make_q(s,e,T[node].cmin - sub,T[node].typ);
	}

	int l,r;
	q_e m1,m2;
	 l = left(node);
	 r = right(node);

	 sub += T[node].sub;
	 m1 = query(l,s,(s+e)/2,sub,sl);

	 if(m1.m){
		if(m1.m == T[l].cmin-sub || m1.sr){
			m1.sr = 0;
			m2 = query(r,(s+e)/2+1,e,sub,1);
			if(m2.m){
				m1.e = m2.e;
				m1.m = min(m1.m,m2.m);
				m1.sr = m2.sr;
			}
		}
		 return m1;
	 }

	 if(!sl){
		 m2 = query(r,(s+e)/2+1,e,sub,sl);
		 return m2;

	 }

	 return make_q(-1,-1,0,0);
}

void update(int node, int s, int e, int i, int j, int sub){

	if(i > e || j < s) return;

	if(s >= i && e <= j){
		T[node].sub += sub;
		T[node].cmin -= sub;
		T[node].cmax -= sub;
		return;
	}

	int l,r;
	l = left(node);
	r = right(node);

	update(l,s,(s+e)/2,i,j,sub);
	update(r,(s+e)/2+1,e,i,j,sub);

	T[node].cmin = min(T[l].cmin,T[r].cmin);
	T[node].cmax = max(T[l].cmax,T[r].cmax);
	T[node].cmin -= T[node].sub;
	T[node].cmax -= T[node].sub;
}

lli play(){

	q_e q;
	lli c = 0;

	init(0,0,N-1,0);

	while(1){
		q = query(0,0,N-1,0,0);
		if(!q.m) break;
		update(0,0,N-1,q.s,q.e,q.m);
		c += (lli)q.m;
	}

	return c;
}

int main(){

	int i;

	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%d",&A[i]);
	}

	printf("%lld\n",play());

	return 0;
}
