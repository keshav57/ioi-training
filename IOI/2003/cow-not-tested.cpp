#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int ct[8][3];
vector<int> rem[52];
int N,P;

pair<int,int> best_question(){
	int i,k,tmp,best;
	pair<int,int> q;

	best = N;

	for(i = 0; i < P; ++i){
		for(k = 0; k < 3; ++k){
			tmp = max(ct[i][k],N-ct[i][k]);

			if(tmp < best){
				best = tmp;
				q = make_pair(i,k);
			}
		}
	}

	return q;
}

int main(){
	int i,k;
	pair<int,int> q;

	scanf("%d%d",&N,&P);

	for(i = 0; i < N; ++i){
		for(k = 0; k < P; ++k){
			rem[i].push_back(0);
			scanf(" %c",&rem[i][k]);
			rem[i][k] -= 'X';
			ct[k][rem[i][k]]++;
		}
		rem[i].push_back(i+1);
	}

	while(N > 1){
		q = best_question();
		printf("Q %d %c\n",q.first+1,q.second+'X');
		fflush(stdout);
		scanf("%d",&k);

		for(i = 0; i < N; ++i){
			if((rem[i][q.first] == q.second) == k) continue;
			swap(rem[i],rem[N-1]);
			--N;
			--i;
		}
	}

	printf("C %d\n",rem[0].back());
	fflush(stdout);

	return 0;
}
