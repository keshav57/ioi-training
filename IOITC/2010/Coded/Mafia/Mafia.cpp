/*
 Created By: Malvika Joshi
 Problem: Mafia (IOITC-2010 Final-3)
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>

#define MAXN 100010

using namespace std;

int rem[MAXN];
vector<int> par[MAXN];
int N,M;

int main(){
	int i,k,p,set;

	scanf("%d%d",&N,&M);

	while(M--){
		scanf("%d%d",&i,&k);
		--i,--k;
		par[k].push_back(i);
	}

	for(i = 0; i < N; ++i) sort(par[i].begin(),par[i].end());

	for(i = 0; i < N; ++i){
		if(par[i].empty()) continue;
		p = par[i].back();
		for(k = 0; k+1 < par[i].size(); ++k){
			if(binary_search(par[p].begin(),par[p].end(),par[i][k])) continue;
			printf("NO\n%d\n",i+1);
			exit(0);
		}
	}

	set = 0;
	for(i = N-1; i >= 0; --i){
		if(rem[i]) continue;
		++set;
		for(k = 0; k < par[i].size(); ++k) rem[par[i][k]] = 1;
	}

	printf("YES\n%d\n",set);

	return 0;
}
