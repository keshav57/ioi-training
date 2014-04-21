/*
 Created By: Malvika Joshi
 Problem: Sculptor (IOITC-2010 Final-1)
*/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

#define MAXN 1510

using namespace std;

int A[MAXN];
int las[MAXN][MAXN];
int N;

vector<pair<int,int> > prev,next;

void DP(){
	int i,p1,p2,j,k;

	for(i = 0; i < N-1; ++i){
		prev.clear(),next.clear();

		for(k = 0; k < i; ++k) prev.push_back(make_pair(A[k],k));
		for(k = i+1; k < N; ++k){
			next.push_back(make_pair(A[k],k));
			las[i][k] = las[k][i] = 2;
		}

		p1 = 0;

		sort(prev.begin(),prev.end());
		sort(next.begin(),next.end());

		j = next[0].second;
		while(p1 < (int)prev.size() && prev[p1].first < next[0].first){
			k = prev[p1].second;
			las[j][i] = max(las[j][i],las[k][i]+1);
			++p1;
		}


		for(p2 = 1; p2 < (int)next.size(); ++p2){
			j = next[p2].second;
			las[j][i] = max(las[j][i],las[next[p2-1].second][i]);
			while(p1 < (int)prev.size() && prev[p1].first < next[p2].first){
				k = prev[p1].second;
				las[j][i] = max(las[j][i],las[k][i]+1);
				++p1;
			}
		}


		p1 = (int)prev.size()-1;
		p2 = (int)next.size()-1;

		j = next[p2].second;
		while(p1 >= 0 && prev[p1].first > next[p2].first){
			k = prev[p1].second;
			las[i][j] = max(las[i][j],las[i][k]+1);
			--p1;
		}

		for(--p2; p2 >= 0; --p2){
			j = next[p2].second;
			las[i][j] = max(las[i][j],las[i][next[p2+1].second]);
			while(p1 >= 0 && prev[p1].first > next[p2].first){
				k = prev[p1].second;
				las[i][j] = max(las[i][j],las[i][k]+1);
				--p1;
			}
		}
	}


}

int main(){

	int i,j,lon;

	scanf("%d",&N);

	for(i = 0; i < N; ++i) scanf("%d",&A[N-i-1]);

	DP();

	lon = 0;
	for(i = 0; i < N; ++i){
		for(j = 0; j < i; ++j){
			lon = max(lon,las[j][i]);
		}
	}

	printf("%d\n",lon);

	return 0;
}
