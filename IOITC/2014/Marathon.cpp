#include <algorithm>
#include <iostream>
#include <cstdio>
#include <set>
#include <vector>

#define NMAX 100010
#define MOD 1000000007

using namespace std;

pair<pair<int,int>, int> events[NMAX*2];
int N,E;
int cur[NMAX];

pair<int,int> inv[NMAX];
set<pair<int,int> > chains;

int compute(){
	int i,j;
	int ct = 0;

	for(i = 1; i < N; ++i){
		events[E++] = make_pair(make_pair(inv[i].first,0),i);
		events[E++] = make_pair(make_pair(inv[i].second,1),i);
	}

	sort(events,events+E);

	ct = 1;
	chains.insert(make_pair(-1,0));
	cur[0] = 1;

	int k;
	for(i = 0; i < E; ++i){
		if(!events[i].first.second){
			j = events[i].second;
			cur[j] = ct;
			continue;
		}

		j = events[i].second;

		while(!chains.empty()){
			k = (chains.begin())->second;
			if(inv[k].second >= inv[j].first) break;
			chains.erase(chains.begin());
			ct -= cur[k];
			if(ct < 0) ct += MOD;
			ct %= MOD;
		}

		chains.insert(make_pair(inv[j].second,j));
		ct += cur[j];
		ct %= MOD;
		if(ct < 0) ct += MOD;
	}

	return ct;
}

int main(){
	int i;

	scanf("%d",&N);

	inv[0] = make_pair(-1,-1);
	++N;
	for(i = 1; i < N; ++i){
		scanf("%d%d",&inv[i].first,&inv[i].second);
	}

	printf("%d\n",compute());

	return 0;
}
