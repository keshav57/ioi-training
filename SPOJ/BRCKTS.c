/*
 Created By: Malvika Joshi
 Problem: Brackets
 Link: http://www.spoj.com/problems/BRCKTS/
*/

#include <stdio.h>
#include <stdlib.h>

inline int parent(int x){ return (x+1)/2-1; }
inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int min(int a, int b){ return a < b ? a : b; }

typedef struct { int opened, closed; } node;

node T[80010];
int seq[30010];
int leaf[30010];
int N,M;

void init(int x, int s, int e){

	if(s == e){
		T[x].opened = T[x].closed = 0;
		if(seq[s]) T[x].opened = 1 ;
		else T[x].closed = 1;
		leaf[s] = x;
		return;
	}

	int bal,r,l;

	l = left(x);
	r = right(x);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	bal = min(T[l].opened,T[r].closed);

	T[x].opened = T[l].opened+T[r].opened-bal;
	T[x].closed = T[l].closed+T[r].closed-bal;
}

void update(int x, int v){
	int bal,p,r,l;

	seq[v] ^= 1;
	T[x].opened = T[x].closed = 0;
	if(seq[v]) T[x].opened = 1 ;
	else T[x].closed = 1;

	p = parent(x);

	while(p >= 0){
		l = left(p);
		r = right(p);

		bal = min(T[l].opened,T[r].closed);

		T[p].opened = T[l].opened+T[r].opened-bal;
		T[p].closed = T[l].closed+T[r].closed-bal;

		p = parent(p);
	}
}

int main(){
	int i,k,t;
	char c;

	for(t = 1; t <= 10; t++){
		scanf("%d\n",&N);

		for(i = 0;i < N; i++){
			c = getchar();
			seq[i] = c == '(';
		}

		init(0,0,N-1);

		scanf("%d",&M);

		printf("Test %d:\n",t);


		for(i = 0; i < M; i++){
			scanf("%d",&k);
			if(!k){
				if(!T[0].opened && !T[0].closed) printf("YES\n");
				else printf("NO\n");
				continue;
			}
			k--;
			update(leaf[k],k);
		}
	}

	return 0;
}
