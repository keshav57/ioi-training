/*
 Created By: Malvika Joshi
 Problem: CHFQUEUE
 Link: http://www.codechef.com/problems/CHFQUEUE
*/

#include <stdio.h>

#define MAXN 1000010
#define MAXL 1000000
#define MAXT (1048576*2)

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int parent(int x){ return (x+1)/2-1; }

inline int min(int a, int b){ return a < b ? a : b; }

int next[MAXN];
int lev[MAXN];
int leaf[MAXN];
int cur[MAXN];
int N;

int T[MAXT];


void init(int s, int e, int node){
	if(s == e){
		T[node] = cur[s];
		leaf[s] = node;
		return;
	}

	int l,r;

	l = left(node);
	r = right(node);

	init(s,(s+e)/2,l);
	init((s+e)/2+1,e,r);

	T[node] = min(T[l],T[r]);
}

int query(int s, int e, int i, int j, int node){
	if(j < s || i > e) return MAXN;
	if(s >= i && e <= j) return T[node];
	int l,r;
	l = query(s,(s+e)/2,i,j,left(node));
	r = query((s+e)/2+1,e,i,j,right(node));
	return min(l,r);
}

void update(int x, int val){
	int p;
	T[x] = val;

	p = x;
	while(p){
		p = parent(p);
		T[p] = min(T[left(p)],T[right(p)]);
	}
}

int compute(){

	int i,j;
	long long total;

	for(i = 0; i < MAXN; i++) cur[i] = MAXN;

	total = 1;
	for(i = N-1; i >= 0; --i){
		next[i] = cur[lev[i]];
		cur[lev[i]] = i;
	}

	init(0,MAXL,0);

	for(i = 0; i < N; i++){
		j = query(0,MAXL,0,lev[i]-1,0);
		update(leaf[lev[i]],next[i]);
		if(j >= MAXN) continue;
		total *= (j-i+1);
		total %= 1000000007LL;
	}

	return (int)total;
}

int main(){
	int i;
	scanf("%d %d",&N,&i);

	for(i = 0; i< N ;i ++) scanf("%d",&lev[i]);

	printf("%d\n", compute());

	return 0;
}
