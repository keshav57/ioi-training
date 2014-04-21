/*
 Created By: Malvika Joshi
 Problem: Fuel Economy (US Open-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=283
*/

#include <cstdio>
#include <cstdlib>
#include <set>
#include <algorithm>

#define MAXN 50010

using namespace std;
typedef long long lli;

struct station{
	lli dist,ppl;
	bool operator< (const station rhs) const {
		return dist < rhs.dist;
	}
};

station S[MAXN];
set<pair<int,int> > R;
station sel[MAXN];

int B,G,N,sN;

int init(){

	int i,j,k,t,e;

	sort(S,S+N);

	i = N-1;
	j = i;
	k = i;

	while(i){
		sel[sN++] = S[i];
		while(k && S[i].dist - S[--k].dist <= G){
			if(!k && S[i].dist > B) break;
			R.insert(make_pair(S[k].ppl,k));
		}
		k++;

		while(--j >= i) R.erase(make_pair(S[j].ppl,j));
		++j;

		if(R.empty()){
			printf("-1\n");
			exit(0);
		}

		e = R.begin()->second;
		t = i;

		while(t > e){
			if(S[t].ppl < S[i].ppl){
				i = t;
				sel[sN++] = S[i];
			}
			--t;
		}

		i = e;
	}

	for(i = 0; i < sN-1; i++)	sel[i].dist -= sel[i+1].dist;


	return sN;
}

lli compute(){

	int i;

	lli cost,fuel;

	fuel = B;
	cost = 0;

	for(i = sN-1; i ; --i){
		fuel -= sel[i].dist;

		if(sel[i-1].ppl < sel[i].ppl){
			cost +=  sel[i].ppl * (sel[i-1].dist-fuel);
			fuel = sel[i-1].dist;
		}else{
			cost += sel[i].ppl * (G-fuel);
			fuel = G;
		}
	}

	return cost;
}

int main(){

	int i;

	scanf("%d %d %d",&N,&G,&B);
	N += 2;
	scanf("%lld",&S[N-1].dist);

	S[N-1].ppl = 0;
	S[0].dist = S[0].ppl = 0;

	for(i = 1; i < N-1; i++) scanf("%lld %lld",&S[i].dist,&S[i].ppl);

	init();

	printf("%lld\n",compute());

	return 0;
}
