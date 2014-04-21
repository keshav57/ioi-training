/*
 Created By: Malvika Joshi
 Problem: Cow Photography (December-2011 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=97
*/

#include <cstdio>
#include <algorithm>
#include <map>

#define MAXN 200010

using namespace std;

struct cow{
	int pos[5];
	int id;

	bool operator<(const cow &c) const{
		int i,cmp[2] = {0,0};
		for(i = 0; i < 5; ++i) cmp[(pos[i]<c.pos[i])]++;
		return cmp[0] < cmp[1];
	}

};

cow photos[MAXN];
map<int,int> ids;
int N;

int main(){
	int i,k,c,p;

	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%d",&c);
		ids[c] = i;
		photos[i].pos[0] = i;
		photos[i].id = c;
	}

	for(k = 1; k < 5; k++){
		for(i = 0; i < N; i++){
			scanf("%d",&c);
			p = ids[c];
			photos[p].pos[k] = i;
		}
	}

	sort(photos,photos+N);
	for(i = 0 ;i  <N; i++) printf("%d\n",photos[i].id);

	return 0;
}
