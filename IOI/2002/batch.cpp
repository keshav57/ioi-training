#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <utility>

using namespace std;

#define NMAX 10010
#define m first
#define c second

typedef pair<int,int> point;

class convex_hull{
private:

	point stack[NMAX];
	double change[NMAX];
	int S,ptr;

	double intersect_x(point a, point b){
		assert(a.m^b.m);
		double x;
		x = (double)(b.c-a.c)/(a.m-b.m);
		return x;
	}

public:

	convex_hull(){
		S = 0;
		ptr = 0;
	}

	int query(double x){
		assert(S);
		while(ptr < S-1 && change[ptr] < x) ++ptr;
		return (x*stack[ptr].m + stack[ptr].c);				//the value of y
	}

	void insert(point p){
		double x1,x2;
		while(S > 1){
			x1 = intersect_x(p,stack[S-2]);
			x2 = intersect_x(stack[S-1],stack[S-2]);
			if(x1 > x2) break;
			--S;
		}

		stack[S] = p;
		if(S) change[S-1] = intersect_x(stack[S-1],p);
		ptr = min(ptr,S);
		++S;
	}
};

convex_hull C;
int N,S;

int dp[NMAX];
int pref_time[NMAX];
int suff_cost[NMAX];
int pref_cost[NMAX];

int compute(){
	int i;

	C.insert(make_pair(0,S*suff_cost[0]));
	dp[0] = C.query(pref_time[0])+pref_time[0]*pref_cost[0];

	for(i = 1; i < N; ++i){
		C.insert(make_pair(-pref_cost[i-1],dp[i-1]+S*suff_cost[i]));
		dp[i] = C.query(pref_time[i]) + pref_time[i]*pref_cost[i];
	}

	return dp[N-1];
}

int main(){
	int i;

	scanf("%d%d",&N,&S);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&pref_time[i],&pref_cost[i]);
		suff_cost[i] = pref_cost[i];
		pref_time[i] += i ? pref_time[i-1] : 0;
		pref_cost[i] += i ? pref_cost[i-1] : 0;
	}
	for(i = N-2; i >= 0; --i) suff_cost[i] += suff_cost[i+1];
	
	printf("%d\n",compute());

	return 0;
}
