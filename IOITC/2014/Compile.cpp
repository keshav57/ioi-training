#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#define NMAX 100010

typedef long long lli;

using namespace std;

int speed[NMAX];
vector<int> out[NMAX];
vector<int> in[NMAX];

lli to[NMAX];
lli from[NMAX];

int N,M;

int Q[NMAX];
int deg[NMAX];
int H,T;

void topsort(){
	int i,v,u;

	while(H < T){
		v = Q[H++];

		for(i = 0; i < out[v].size(); ++i){
			u = out[v][i];
			--deg[u];
			if(!deg[u]) Q[T++] = u;
		}
	}
}

lli	init(){
	int i,v,k,u;
	lli slow;

	slow = 0LL;
	for(i = N-1; i >= 0; --i){
		v = Q[i];
		from[v] = speed[v];
		for(k = 0; k < out[v].size(); ++k){
			u = out[v][k];
			from[v] = max(from[v],from[u]+speed[v]);
		}
		slow = max(slow,from[v]);
	}

	for(i = 0; i < N; ++i){
		v = Q[i];
		to[v] = 0;
		for(k = 0; k < in[v].size(); ++k){
			u = in[v][k];
			to[v] = max(to[v],to[u]+speed[u]);
		}
	}

	return slow;
}

/*
5 4
2 9 3 5 12
2 1
3 5
3 2
4 5
3
3 10
*/

int main(){
	int i,j,q;
	lli slow,tmp;

	scanf("%d%d",&N,&M);

	for(i = 0; i < N; ++i){
		scanf("%d",&speed[i]);
	}

	while(M--){
		scanf("%d%d",&i,&j);
		--i,--j;
		out[i].push_back(j);
		in[j].push_back(i);
		++deg[j];
	}

	for(i =0 ; i < N; ++i){
		if(deg[i]) continue;
		Q[T++] = i;
	}

	topsort();
	slow = init();

	printf("%lld\n",slow);
	scanf("%d",&q);

	while(q--){
		scanf("%d%lld",&i,&tmp);
		--i;
		printf("%lld\n",max(tmp+to[i]+from[i],slow));
	}

	return 0;
}
