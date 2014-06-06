#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>

#define NMAX 100010

using namespace std;

int mines[4][4][4][4][2];
int typ[NMAX];

int N;

const int popcount[8] = {0,1,1,2,1,2,2,3};

inline int diff(int t1, int t2, int t3){
	int s;
	s = (1<<t1)|(1<<t2)|(1<<t3);
	return popcount[s&7];
}

int dp(){
	int t1,t2,t3,t4,i;

	for(i = N-1; i >= 0; --i){
		for(t1 = 0; t1 < 4; ++t1){
			for(t2 = 0; t2 < 4; ++t2){
				for(t3 = 0; t3 < 4; ++t3){
					for(t4 = 0; t4 < 4; ++t4){
						mines[t1][t2][t3][t4][i&1] = max(mines[t2][typ[i]][t3][t4][1^(i&1)]+diff(t1,t2,typ[i]),\
								mines[t1][t2][t4][typ[i]][1^(i&1)] + diff(t3,t4,typ[i]));
					}
				}
			}
		}
	}

	return mines[3][3][3][3][0];
}

int main(){
	int i;
	char c;
	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf(" %c",&c);
		typ[i] = (c == 'F' ? 2 : (c == 'B'));
	}

	printf("%d\n",dp());

	return 0;
}
