/*
 Created By: Malvika Joshi
 Problem: Above the Median (November-2011 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=91
*/

#include <cstdio>
#include <vector>
#include <algorithm>

#define MAXN 100010
#define MAXT 300000

using namespace std;
typedef long long lli;

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }

vector<int> T[MAXT];
int P[MAXN];
int N,X;

void init(int node, int s, int e){

	if(s == e){
		T[node].push_back(P[s]);
		return;
	}

	int i0,i1,n0,n1,l,r;

	l = left(node);
	r = right(node);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	n0 = T[l].size();
	n1 = T[r].size();

	i0 = i1 = 0;

	while(i0 < n0 && i1 < n1){
		if(T[l][i0] < T[r][i1])
			T[node].push_back(T[l][i0++]);
		else
			T[node].push_back(T[r][i1++]);
	}

	while(i0 < n0)	T[node].push_back(T[l][i0++]);
	while(i1 < n1)	T[node].push_back(T[r][i1++]);
}

int query(int node, int s, int e, int i, int j, int k){

	if(j < s || i > e) return 0;

	if(s >= i && e <= j){
		int n = upper_bound(T[node].begin(),T[node].end(),k) - T[node].begin();
		return n;
	}

	int r0,r1;
	r0 = query(left(node),s,(s+e)/2,i,j,k);
	r1 = query(right(node),(s+e)/2+1,e,i,j,k);

	return r0+r1;
}

lli above_X(){
	int i;
	lli sc;

	for(i = 1; i < N; i++){
		P[i] = P[i] >= X ? 1 : -1;
		P[i] += P[i-1];
	}

	init(0,0,N-1);

	sc = 0LL;
	for(i = 1; i < N; i++){
		sc += (lli)query(0,0,N-1,0,i-1,P[i]);
	}

	return sc;
}

int main(){

	int i;

	scanf("%d%d",&N,&X);
	++N;

	for(i = 1; i < N; i++) scanf("%d",&P[i]);

	printf("%lld\n",above_X());

	return 0;
}

