#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstring>

#define NMAX 500010

using namespace std;

int order_t[NMAX];
int order_q[NMAX];
double T[NMAX];
int Q[NMAX];

int sel[NMAX];
int rem[NMAX];
int N;
long long W;

double min_cost(int K){
	memset(sel,0,sizeof(sel));
	memset(rem,0,sizeof(rem));

	if(!K) return 0;
	int k,i,ptr,idx;
	double best,cur;
	long long tot;

	ptr = 0;
	tot = 0;
	k = 0;
	best = W+1;

	for(idx = 0; idx+K <= N; ++idx){
		i = order_t[idx];
		if(!sel[i]){
			sel[i] = 1;
			tot += Q[i];
			++k;
		}

		while(k < K){
			assert(ptr < N);
			while(sel[order_q[ptr]] || rem[order_q[ptr]]) ++ptr;
			sel[order_q[ptr]] = 1;
			tot += Q[order_q[ptr]];
			++ptr;
			++k;
		}

		cur = tot*T[i];
		best = min(best,cur);

		tot -= Q[i];
		rem[i] = 1;
		sel[i] = 0;
		--k;
	}

	return best;
}

int search(){
	int low,high,mid;

	low = 0;
	high = N+1;

	while(low < high){
		mid = low + (high-low)/2;
		if(min_cost(mid) <= W){
			low = mid+1;
		}else{
			high = mid;
		}
	}

	return low;
}

void get_selection(double cost, int K){
	memset(sel,0,sizeof(sel));
	memset(rem,0,sizeof(rem));

	if(!K) return;
	int k,i,ptr,idx;
	double cur;
	long long tot;

	ptr = 0;
	tot = 0;
	k = 0;

	for(idx = 0; idx+K <= N; ++idx){
		i = order_t[idx];
		if(!sel[i]){
			sel[i] = 1;
			tot += Q[i];
			++k;
		}

		while(k < K){
			while(sel[order_q[ptr]] || rem[order_q[ptr]]) ++ptr;
			assert(ptr < N);
			sel[order_q[ptr]] = 1;
			tot += Q[order_q[ptr]];
			++ptr;
			++k;
		}

		cur = tot*T[i];
		if(fabs(cur-cost) <= (1e-5)) return;

		tot -= Q[i];
		rem[i] = 1;
		sel[i] = 0;
		--k;
	}

	assert(0);
}

int compare_t(int a, int b){
	return T[a] > T[b];
}

int compare_q(int a, int b){
	return Q[a] < Q[b];
}

int main(){
	int i,k;

	scanf("%d%lld",&N,&W);

	for(i =0 ; i < N; ++i){
		scanf("%lf%d",&T[i],&Q[i]);
		T[i] /= Q[i];
		order_q[i] = i;
		order_t[i] = i;
	}

	sort(order_q,order_q+N,compare_q);
	sort(order_t,order_t+N,compare_t);

	k = search();

	printf("%d\n",k-1);

	get_selection(min_cost(k-1),k-1);

	for(i = 0; i < N; ++i){
		if(!sel[i]) continue;
		printf("%d\n",i+1);
	}

	return 0;
}
