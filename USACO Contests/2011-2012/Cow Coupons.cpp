/*
 Created By: Malvika Joshi
 Problem: Cow Coupons (February-2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=118
*/

#include <algorithm>
#include <set>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <cassert>

#define N_MAX 50010

using namespace std;
typedef long long lli;

pair<int,int> cost[N_MAX];

pair<int,int> sel[N_MAX];
int apply[N_MAX];
int repl[N_MAX];

int N;

int compare(pair<int,int> a, pair<int,int> b){
	return a.first-a.second > b.first-b.second;
}

lli min_cost(int k, int coupons){
	int i,n;
	lli tot;
	tot = 0;

	for(i = 0; i < k; ++i){
		sel[i] = cost[i];
		tot += cost[i].first;
	}

	n = 0;
	for(; i < N; ++i) repl[n++] = cost[i].second;

	sort(sel,sel+k,compare);
	sort(repl,repl+n);

	coupons = min(coupons,k);

	int app;
	app = 0;
	for(i = 0; i < coupons; ++i){
		apply[i] = sel[i].second;
		tot = tot-sel[i].first+sel[i].second;
		++app;
	}

	sort(apply,apply+coupons);

	i = 0;
	while(i < n && coupons){
		if(repl[i] > apply[coupons-1]) break;
		tot = tot-apply[--coupons]+repl[i++];
	}

	return tot;
}

int search(int coup, lli budget){
	int high,low,mid;

	low = 0;
	high = N;

	while(low < high){
		mid = low+(high-low+1)/2;

		if(min_cost(mid,coup) > budget){
			high = mid-1;
		}else{
			low = mid;
		}

	}

	return low;
}


int main(){
	int i,coup;
	lli budget;

	scanf("%d%d%lld",&N,&coup,&budget);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&cost[i].first,&cost[i].second);
	}

	sort(cost,cost+N);
	printf("%d\n",search(coup,budget));

	return 0;
}
