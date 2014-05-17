/*
 Created By: Malvika Joshi
 Problem: Divide and Conquer (APIO-2014 Practice)
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define NMAX 100010

using namespace std;

typedef long long lli;

lli pos[NMAX];
lli energy[NMAX];
lli gold[NMAX];

lli increase[NMAX];

pair<lli,pair<int,int> > det[NMAX*2];

int N,M;

int main(){
	int i,st;
	lli mgold;

	scanf("%d",&N);

	for(i =0 ; i < N; ++i){
		scanf("%lld%lld%lld",&pos[i],&gold[i],&energy[i]);
		increase[i] = i ? energy[i]+pos[i-1]-pos[i] : energy[i] ;
		increase[i] += i ? increase[i-1] : 0;
		gold[i] += i ? gold[i-1] : 0;
		det[M++] = make_pair(increase[i],make_pair(1,i));
		det[M++] = make_pair(increase[i]-energy[i],make_pair(0,i));
	}


	st = N;
	mgold = 0;

	sort(det,det+M);

	for(i = 0; i < M; ++i){
		if(!det[i].second.first){
			st = min(st,det[i].second.second);
			continue;
		}

		if(st > det[i].second.second) continue;
		mgold = max(mgold,gold[det[i].second.second]-(st ? gold[st-1] : 0));
	}

	printf("%lld\n",mgold);

	return 0;
}
