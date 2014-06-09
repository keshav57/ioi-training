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
	q = make_pair(-1,-1);

	for(i = 0; i < P; ++i){
		for(k = 0; k < 3; ++k){
			tmp = max(ct[i][k],N-ct[i][k]);
			if(tmp < best){
				best = tmp;
				q = make_pair(i,k);
			}
		}
	}

	assert(q.first >= 0);

	return q;
}

int sol,asked;

int cow[60][10];

int ask(int p, int v){
	++asked;
	return cow[sol][p] == v;
}

int main(int argc, char **argv){
	int i,k;
	pair<int,int> q;
	char c;

	assert(argc == 2);

	FILE *out = fopen(argv[1],"r");
	fscanf(out,"%d",&sol);
	--sol;

	scanf("%d%d",&N,&P);

	for(i = 0; i < N; ++i){
		for(k = 0; k < P; ++k){
			rem[i].push_back(0);
			scanf(" %c",&c);
			cow[i][k] = c-'X';
			rem[i][k] = cow[i][k];
			ct[k][rem[i][k]]++;
		}
		rem[i].push_back(i+1);
	}

	pair<int,int> prev = make_pair(-1,-1);

	while(N > 1){
		q = best_question();
		k = ask(q.first,q.second);
		assert(q != prev);
		prev = q;

		for(i = 0; i < N; ++i){
			if((rem[i][q.first] == q.second) == k) continue;
			for(int j = 0; j < P; ++j)	--ct[j][rem[i][j]];
			swap(rem[i],rem[N-1]);
			--N;
			--i;
		}
	}

	assert(sol == rem[0].back()-1);
	cout << asked << endl;

	return 0;
}
