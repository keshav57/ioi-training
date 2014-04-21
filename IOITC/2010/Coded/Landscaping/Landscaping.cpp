/*
 Created By: Malvika Joshi
 Problem: Landscaping (IOITC-2010 Test-2)
*/

#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>

#define N_MAX 1010
#define INF (int)(1e9)

using namespace std;

int elevation[N_MAX];
int N,K,peaks;

pair<int,int> find_range(int peak){

	int st,en,i;

	for(i = peak; i; --i){
		if(elevation[i-1] > elevation[i]) break;
	}

	st = i;

	for(i = peak; i < N-1; ++i){
		if(elevation[i+1] > elevation[i]) break;
	}

	en = i;

	return make_pair(st,en);
}

int reduction_cost(int st, int en){
	int i,cost,height;

	height = max(elevation[st],elevation[en]);
	cost = 0;

	for(i = st; i <= en; ++i){
		cost += max(0,elevation[i]-height);
	}

	return cost;
}

void delete_peak(int st, int en){
	int i,height;

	height = max(elevation[st],elevation[en]);

	for(i = st; i <= en; ++i){
		elevation[i] = min(elevation[i],height);
	}
}

int compute(){

	int tot_cost,best_cost,i,tmp_cost,j;
	pair<int,int> best_range,tmp_range;

	tot_cost = 0;

	while(peaks-- > K){

		best_cost = INF;

		for(i = 1; i < N-1; ++i){
			if(elevation[i] <= elevation[i-1]) continue;
			j = i;
			while(elevation[++j] == elevation[i]);
			if(elevation[j] > elevation[i]) continue;

			tmp_range = find_range(i);
			tmp_cost = reduction_cost(tmp_range.first,tmp_range.second);
			if(tmp_cost <= best_cost) best_range= tmp_range, best_cost = tmp_cost;
		}

		delete_peak(best_range.first,best_range.second);
		tot_cost += best_cost;
	}

	return tot_cost;
}

int main(){

	int i,j;

	scanf("%d%d",&N,&K);

	N+=2;
	for(i = 1; i < N-1; i++) scanf("%d",&elevation[i]);

	for(i = 1; i < N-1; ++i){
		if(elevation[i] <= elevation[i-1]) continue;
		j = i;
		while(elevation[++j] == elevation[i]);
		peaks += (elevation[j] < elevation[i]);
	}

	printf("%d\n",compute());

	return 0;
}
