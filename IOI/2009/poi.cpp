#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 2010

using namespace std;

pair<int,pair<int,int> > ranking[NMAX];
int N,M;

int score[NMAX];
int solved[NMAX][NMAX];

int main(){
	int i,k,id;

	scanf("%d%d%d",&N,&M,&id);

	for(i =0 ; i < N; ++i){
		for(k = 0; k < M; ++k){
			scanf("%d",&solved[i][k]);
			score[k] += !solved[i][k];
		}
	}

	for(i = 0; i < N; ++i){
		ranking[i].second.second = i+1;
		ranking[i].first = 0;
		ranking[i].second.first = 0;

		for(k =0 ; k < M; ++k){
			ranking[i].first += score[k]*solved[i][k];
			ranking[i].second.first += solved[i][k];
		}
		ranking[i].second.first = -ranking[i].second.first;
		ranking[i].first = -ranking[i].first;
	}

	sort(ranking,ranking+N);

	for(i =0 ; i < N; ++i){
		if(ranking[i].second.second == id) break;
	}

	printf("%d %d\n",-ranking[i].first,i+1);

	return 0;
}
