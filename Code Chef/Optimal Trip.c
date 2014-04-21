/*
 Created By: Malvika Joshi
 Problem: TRIPCOST
 Link: http://www.codechef.com/problems/TRIPCOST
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100010
#define INF 100010

int dist[MAXN];
int cost[MAXN];
int bound[MAXN];
int N,D,L;

int compare(const void *a, const void *b){
	return *(int*)a-*(int*)b;
}

int days(int c){

	int i,d,k,v;

	k = 0;
	d = 0;
	v = 0;
	for(i = 1; i <= N; i++){
		v += dist[i];
		if(v > D) return INF;
		if(i < N && cost[i] > c) continue;
		if(d + v > D){
			++k;
			d = 0;
		}
		d += v;
		v = 0;
	}

	return ++k;
}

int search(){

	L = days(INF);
	printf("%d ",L	);

	qsort(bound,N+1,sizeof(int),compare);

	int h,t,mid,l;

	h = 0;
	t = N+1;

	while(h <= t){
		mid = (h+t)/2;
		l = days(bound[mid]);
		if(l > L){
			h = mid+1;
		}else{
			t = mid-1;
		}
	}

	printf("%d\n",bound[h]);
	return h;
}

int main(){

	int i,t;

	scanf("%d",&t);

	while(t--){
		scanf("%d%d",&N,&D);
		bound[0] = cost[0] = dist[0] = 0;
		for(i = 1; i <= N; i++){
			scanf("%d%d",&dist[i],&cost[i]);
			bound[i] = cost[i];
		}
		search();
	}

	return 0;
}
