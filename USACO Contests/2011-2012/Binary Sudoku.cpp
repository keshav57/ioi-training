/*
 Created By: Malvika Joshi
 Problem: Binary Sudoku (November-2011 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=92
*/

#include <algorithm>
#include <cstdio>
#include <iostream>

#define N 9
#define COL (1<<N)
#define INF 100

using namespace std;


int init[N+2];
int toggle[COL+2][N+2];

inline int popcount(int x){
	int pop = 0;

	while(x){
		pop+=(x&1);
		x >>= 1;
	}

	return pop;
}

int dp(){
	int i,col,cur,prev,cost,k,par;

	for(col = 0; col < COL; ++col){
		toggle[col][0] =  popcount(col)&1 ? INF : popcount(col^init[0]);
	}

	for(i = 1; i < N; ++i){
		for(col = 0; col < COL; ++col){
			toggle[col][i] = INF;

			if(!((i+1)%3)){
				for(k = 0; k < N; k+=3){
					par = !!(col&(1<<k));
					par ^= !!(col&(1<<(k+1)));
					par ^= !!(col&(1<<(k+2)));
					if(par) break;
				}

				if(k < N) continue;
			}

			for(cur = 0; cur < COL; ++cur){
				if(popcount(cur)&1) continue;
				prev = cur^col;
				cost = popcount(cur^init[i]);

				toggle[col][i] = min(toggle[col][i],toggle[prev][i-1]+cost);
			}
		}
	}

	return toggle[0][N-1];
}

int main(){

	int i,k,c;
	char ch;

	for(i = 0; i < N; ++i){
		for(k = 0; k < N; ++k){
			scanf(" %c",&ch);
			c = ch - '0';
			init[k] |= (c<<i);
		}
	}


	printf("%d\n",dp());

	return 0;
}
