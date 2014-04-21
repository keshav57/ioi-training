/*
 Created By: Malvika Joshi
 Problem: Taxi (February-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=248
*/

#include <algorithm>
#include <cstdio>
#include <utility>

#define NMAX 1000010

using namespace std;
typedef pair<int,int> point;

point pos[NMAX];
int N,M,L;

int left[NMAX];
int right[NMAX];

int main(){
	int i,s,e,len,move;
	long long dist;

	scanf("%d%d",&N,&L);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&s,&e);

		if(e < s){
			pos[M++] = make_pair(e,3);
			pos[M++] = make_pair(s,2);
			continue;
		}else{
			pos[M++] = make_pair(s,0);
			pos[M++] = make_pair(e,1);
		}
	}

	pos[M++] = make_pair(-1,4);
	pos[M++] = make_pair(L+1,4);

	sort(pos,pos+M);


	for(i = 1; i < M; ++i){
		left[i] = left[i-1];
		if(pos[i-1].second > 1)	continue;
		left[i] += pos[i-1].second == 0 ? 1 : -1;
	}

	dist = 0;
	for(i = M-1; i ;--i){
		right[i] = right[i+1];
		if(pos[i].second < 2 || pos[i].second > 3) continue;
		right[i] += pos[i].second == 2 ? 1 : -1;
	}

	for(i = 1; i < M; ++i){
		move = left[i] > right[i] ? left[i] : right[i]+1;
		len = pos[i].first-pos[i-1].first;
		dist += 1LL*len*(move*2-1);
	}

	printf("%lld\n",dist-2);

	return 0;
}
