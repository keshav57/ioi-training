/*
 Created By: Malvika Joshi
 Problem: Binary Search Heap Construction
 Link: http://www.spoj.com/problems/HEAPULM/
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }

std::pair<std::string, int> A[50010];
int T[150000];
int N;

void init(int node, int s, int e){

	if(s == e){
		T[node] = s;
		return;
	}

	int l,r;

	l = left(node);
	r = right(node);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	if(A[T[l]].second > A[T[r]].second){
		T[node] = T[l];
	}else{
		T[node] = T[r];
	}

}

int query(int node, int s, int e, int i, int j){

	if(i > e || j < s) return -1;

	if(s >= i && e <= j) return T[node];

	int p1,p2;

	p1 = query(left(node),s,(s+e)/2,i,j);
	p2 = query(right(node),(s+e)/2+1,e,i,j);

	if(p1 == -1) return p2;
	if(p2 == -1) return p1;

	return A[p1].second > A[p2].second ? p1 : p2;
}

void build_treap(int i, int j){

	if(j < i) return;

	int root;
	root = query(0,0,N-1,i,j);

	printf("(");
	build_treap(i,root-1);
	std::cout << A[root].first;
	printf("/%d",A[root].second);
	build_treap(root+1,j);
	printf(")");

}

int main(){

	int i;
	char c;
	scanf("%d",&N);
	while(N){

		for(i = 0;i < N; i++){
			c = getchar();
			c = getchar();
			A[i].first.clear();
			while(c != '/'){
				A[i].first.push_back(c);
				c = getchar();
			}
			scanf("%d",&A[i].second);
		}

		std::sort(A,A+N);
		init(0,0,N-1);
		build_treap(0,N-1);
		printf("\n");

		scanf("%d",&N);
	}

}
