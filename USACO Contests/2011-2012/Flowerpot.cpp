/*
 Created By: Malvika Joshi
 Problem: Flowerpot (March-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=125
*/

#include <cstdio>
#include <set>
#include <algorithm>

#define MAXN 100010
#define INF 10000000

using namespace std;

typedef pair<int,int> point;

set<point> X;
point Y[MAXN];
int N,D;

int compare(point a, point b){
	return a.second < b.second;
}

int width(){

	int mwid = INF,i;
	set<point>::iterator it;

	sort(Y,Y+N,compare);

	for(i = 0; i < N; i++){
		if(X.empty()) break;
		while(1){
			it = X.upper_bound(Y[i]);
			if(it == X.end()) break;
			if(it->second-Y[i].second < D){
				X.erase(it);
				continue;
			}
			mwid = min(mwid,it->first-Y[i].first);
			break;
		}
		while(1){
			it = X.lower_bound(Y[i]);
			if(it == X.begin() || it == X.end()) break;
			--it;
			if(it->second-Y[i].second < D){
				X.erase(it);
				continue;
			}
			mwid = min(mwid,Y[i].first-it->first);
			break;
		}
	}

	return mwid >= INF ? -1 : mwid;
}

int main(){
	int i;

	scanf("%d%d",&N,&D);
	for(i = 0; i < N; i++){
		scanf("%d%d",&Y[i].first,&Y[i].second);
		X.insert(Y[i]);
	}

	i = width();
	printf("%d\n",i);

	return 0;
}
