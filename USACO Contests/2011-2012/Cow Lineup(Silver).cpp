/*
 Created By: Malvika Joshi
 Problem: Cow Lineup (November-2011 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=89
 */

#include <cstdio>
#include <map>
#include <algorithm>

#define MAXN 50000

using namespace std;

map<int,int> C;
pair<int,int> cows[MAXN];

int N,K;

int photo(){
	int i,j,k;
	int min_cost = cows[N-1].first-cows[0].first;

	i = 0, j = -1, k = 0;

	while(i < N && j < N){
		while(k < K && ++j < N)	k += !(C[cows[j].second]++);

		while(k >= K){
			min_cost = min(min_cost,cows[j].first-cows[i].first);
			k -= !(--C[cows[i++].second]);
		}
	}

	return min_cost;
}

int main(){

	int i;

	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%d%d",&cows[i].first,&cows[i].second);
		C[cows[i].second] = 0;
	}

	K = C.size();
	sort(cows,cows+N);

	printf("%d\n",photo());
}
