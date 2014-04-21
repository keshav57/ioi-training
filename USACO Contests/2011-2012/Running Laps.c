/*
 Created By: Malvika Joshi
 Problem: Running Laps (US Open-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=136
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXN 100010
#define EPS 0.0000001


typedef long long lli;

int compare(const void *a, const void *b){ return *(int*)a-*(int*)b; }

int laps[MAXN];
lli prefix_sum[MAXN];	//of laps
double dist[MAXN];			//distance from start
int speed[MAXN];
int N,C,L;

double tmp[MAXN];
lli split_inversions(int l, int mid, int r){
	int i,j,k;
	lli inv = 0;
	double diff;

	i = l;
	j = mid;
	k = 0;
	while(i < mid && j <= r){
		if(dist[i] > dist[j]){
			diff = dist[i] - dist[j];
			if((diff < EPS)){
				tmp[k++] = dist[j++];
				inv += mid-i;
				continue;
			}
			tmp[k++] = dist[i++];
			continue;
		}
		tmp[k++] = dist[j++];
		inv += mid-i;
	}

	while(i < mid) tmp[k++] = dist[i++];
	while(j <= r) tmp[k++] = dist[j++];

	while(k--) dist[l+k] = tmp[k];

	return inv;
}


lli inversions(int l,int r){
	int mid;
	lli inv;

	if(l >= r) return 0;
	inv = 0;
	mid = (l+r)/2;
	inv += inversions(l,mid);
	inv += inversions(mid+1,r);
	inv += split_inversions(l,mid+1,r);

	return inv;
}


void init(){

	int i;
	double race_end,total_dist;

	qsort(speed,N,sizeof(int),compare);
	race_end = (L*C)/(double)speed[N-1];

	for(i = 0; i < N; i++){
		total_dist = speed[i]*race_end;
		laps[i] = (int)(total_dist/C);
		dist[i] = total_dist - (laps[i]*C);
		prefix_sum[i] = laps[i] + (i ? prefix_sum[i-1] : 0);
	}
}

lli crossings(){
	int i;
	lli cross,tmp;

	cross = 0LL;
	for(i = 1; i < N; i++){
		tmp = (laps[i]*(lli)(i)) - i - prefix_sum[i-1];
		cross += tmp;
	}

	cross += inversions(0,N-1);

	return cross;
}

int main(){
	int i;

	scanf("%d%d%d",&N,&L,&C);

	for(i = 0; i < N; i++){
		scanf("%d",&speed[i]);
	}

	init();
	printf("%lld\n",crossings());
	return 0;
}
