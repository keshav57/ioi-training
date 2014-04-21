/*
 Created By: Malvika Joshi
 Problem: Minimal Coverage
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1303
*/

#include <stdio.h>
#include <stdlib.h>

#define inf 200000

typedef struct { int first,second; } pair;

int cover[6000];
int p[6000];
pair seg[100000];
int N,M;

inline int min(int a, int b){ return a < b ? a : b; }
inline int max(int a, int b){ return a > b ? a : b; }

int compare(const void *a, const void *b){
	const pair *p1 = (pair*) a;
	const pair *p2 = (pair*) b;
	return p1->first-p2->first;
}

void init(){
	int i,j;
	for(i = 0;i < N; i++) cover[i] = inf;

	qsort(seg,M,sizeof(pair),compare);

	for(i = 0;i < M; i++){
		for(j = min(N-1,seg[i].second); j > seg[i].first && j >= 0; j--){
			if(cover[j] != inf) break;
			cover[j] = seg[i].first;
			p[j] = i;
		}
	}

}

pair sol[100000];
int S = 0;

int get_covering(){
	int i,covering = 0;
	i = N-1;
	while(i > 0){
		if(cover[i] == inf) return inf;
		covering++;
		sol[S++] = seg[p[i]];
		i = cover[i];
	}
	return covering;
}


int main(){
	scanf("%d",&N);
	++N;
	M = 0;
	int temp;
	scanf("%d%d",&seg[M].first,&seg[M].second);

	while(seg[M].first || seg[M].second){
		++M;
		scanf("%d%d",&seg[M].first,&seg[M].second);
		if(seg[M].first > seg[M].second){
			temp = seg[M].first;
			seg[M].first = seg[M].second;
			seg[M].second = temp;
		}
	}

	init();
	int covering = get_covering();

	if(covering == inf){
		printf("No solution\n");
		return 0;
	}

	printf("%d\n",covering);

	int i;
	for(i = S-1; i >= 0; --i){
		printf("%d %d\n",sol[i].first,sol[i].second);
	}

	return 0;
}
