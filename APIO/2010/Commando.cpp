#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 1000010
#define m first
#define c second

#define SLOPE(i) (-2*a*pref[(i)])
#define YINT(i) (effect[(i)]+a*pref[(i)]*pref[(i)]-b*pref[(i)])
#define INC(i) (a*pref[i]*pref[i]+b*pref[i]+c)

using namespace std;

typedef long long lli;
typedef pair<lli,lli> point;

class convex_hull{
private:

	point stack[NMAX];
	double change[NMAX];
	int S,ptr;

	inline double intersect_x(point &p1, point &p2){
		return ((double)p2.c-p1.c)/(p1.m-p2.m);
	}

public:

	convex_hull(){
		S = 0;
		ptr = 0;
	}

	void insert(point p){
		while(S > 1){
			if(intersect_x(p,stack[S-2]) > intersect_x(stack[S-1],stack[S-2])) break;
			--S;
		}

		stack[S] = p;
		ptr = min(ptr,S);
		if(S) change[S-1] = intersect_x(stack[S],stack[S-1]);
		++S;
	}

	lli query(int x){

		while(ptr < S-1 && change[ptr] <= x){
			++ptr;
		}

		return 1LL*stack[ptr].m*x+stack[ptr].c;
	}
};

lli effect[NMAX];
lli pref[NMAX];
int a,b,c;

int N;

convex_hull T;

lli dp(){
	int i;

	effect[0] = INC(0);
	T.insert(make_pair(SLOPE(0),YINT(0)));

	for(i = 1; i < N; ++i){
		effect[i] = T.query(pref[i]) + INC(i);
		effect[i] = max(effect[i],INC(i));								//slope = 0
		T.insert(make_pair(SLOPE(i),YINT(i)));
	}

	return effect[N-1];
}

int main(){
	int i;

	scanf("%d",&N);
	scanf("%d%d%d",&a,&b,&c);

	for(i =0 ; i < N ; ++i){
		scanf("%lld",&pref[i]);
		pref[i] += i ? pref[i-1] : 0;
	}

	printf("%lld\n",dp());

	return 0;
}
