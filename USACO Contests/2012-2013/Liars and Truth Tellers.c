/*
 Created By: Malvika Joshi
 Problem: Liars and Truth Tellers (January-2013 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=225
*/

#include <stdio.h>

typedef struct { int parent,rel,rank; } vertex;

vertex V[1000];
int M,N;

void make_set(int x){
	V[x].parent = x;
	V[x].rel = 1;
	V[x].rank = 0;
}

int pval(int x, int rel){
	if(V[x].parent == x){
		return rel;
	}
	if(!V[x].rel) { rel = !rel; }
	return pval(V[x].parent,rel);
}

int find(int x){
	if(V[x].parent != x){
		V[x].rel = pval(x,1);
		V[x].parent =  find(V[x].parent);
	}
	return V[x].parent;
}

void s_union(int x, int y,int rel){
	int xroot = find(x);
	int yroot = find(y);
	int xrel,yrel;

	if(rel){
		xrel = pval(x,1);
		yrel = pval(y,1);
	}else {
		xrel = pval(x,1);
		yrel = pval(y,0);
	}

	if(V[xroot].rank < V[yroot].rank){
		V[xroot].parent = yroot;
		V[xroot].rel = xrel == yrel;
	}else if(V[xroot].parent > V[yroot].parent){
		V[yroot].parent = xroot;
		V[yroot].rel = xrel == yrel;
	}else {
		V[xroot].parent = yroot;
		V[xroot].rel = xrel == yrel;
		V[xroot].rank += 1;
	}
}

int main(){

	int i,a,b,rel,ar,br;
	char c;

	scanf("%d%d",&N,&M);

	for(i = 0;i < N; i++){
		make_set(i);
	}

	for(i = 0;i < M; i++){
		scanf("\n%d %d %c",&a,&b,&c);
		rel = c == 'T';

		if(find(a) == find(b)){
			ar = pval(a,1);
			br = pval(b,1);
			if((ar == br) != rel){
				printf("%d",i);
				return 0;
			}
		}else {
			s_union(a,b,rel);
		}
	}

	printf("%d",M);
	return 0;
}
