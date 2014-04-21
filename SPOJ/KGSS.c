/*
 Created By: Malvika Joshi
 Problem: Maximum Sum
 Link: http://www.spoj.com/problems/KGSS/
*/

#include <stdio.h>

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int parent(int x){ return (x+1)/2-1; }

inline int max(int a, int b){ return a > b ? a : b; }

typedef struct { int m1,m2; } m_pair;

m_pair T[300000];
int A[100000];
int leaf[100000];
m_pair const empty = {-1,-1};
int N,M;

void init(int node, int s, int e){

	if(s == e){
		T[node].m1 = A[s];
		T[node].m2 = 0;
		leaf[s] = node;
		return;
	}

	int l,r;

	l = left(node);
	r = right(node);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	if(T[l].m1 > T[r].m1){
		T[node].m1 = T[l].m1;
		T[node].m2 = max(T[l].m2,T[r].m1);
	}else{
		T[node].m1 = T[r].m1;
		T[node].m2 = max(T[l].m1,T[r].m2);
	}

}

void update(int node, int i, int v){
	A[i] = v;
	T[node].m1 = A[i];

	int k,l,r;

	k = parent(node);

	while(k >= 0){
		l = left(k);
		r = right(k);

		if(T[l].m1 > T[r].m1){
			T[k].m1 = T[l].m1;
			T[k].m2 = max(T[l].m2,T[r].m1);
		}else{
			T[k].m1 = T[r].m1;
			T[k].m2 = max(T[l].m1,T[r].m2);
		}

		k = parent(k);
	}
}

m_pair query(int node, int s, int e, int i, int j){

	if(i > e || j < s) return empty;

	if(s >= i && e <= j) return T[node];

	m_pair p1,p2,temp;

	p1 = query(left(node),s,(s+e)/2,i,j);
	p2 = query(right(node),(s+e)/2+1,e,i,j);

	if(p1.m1 == -1) return p2;
	if(p2.m1 == -1) return p1;

	if(p1.m1 > p2.m1){
		temp.m1 = p1.m1;
		temp.m2 = max(p2.m1,p1.m2);
	}else{
		temp.m1 = p2.m1;
		temp.m2 = max(p2.m2,p1.m1);
	}

	return temp;
}


int main(){

	int i,x,y;
	m_pair q;
	char c;

	scanf("%d",&N);

	for(i = 0;i < N; i++) scanf("%d",&A[i]);

	init(0,0,N-1);


	scanf("%d",&M);

	for(i = 0;i < M; i++){
		scanf("\n%c %d %d",&c,&x,&y);
		if(c == 'Q'){
			q = query(0,0,N-1,x-1,y-1);
			printf("%d\n",q.m1+q.m2);
		}else{
			--x;
			update(leaf[x],x,y);
		}
	}
	return 0;
}
