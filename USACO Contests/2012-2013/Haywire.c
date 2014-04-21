/*
 Created By: Malvika Joshi
 Problem: Haywire (US Open-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=281
 */

#include <stdio.h>

#define INF 10000
#define MAXN 12
#define MAXM (1<<MAXN)

int cost[MAXM];
int fnd[MAXN][3];
int N,M;		//M is 2^N

inline int min(int a, int b){ return a < b ? a : b; }

int DP(){
	int sel,lst,tmp,i,f;
	cost[0] = 0;

	for(sel = 1; sel < M; ++sel){
		cost[sel] = INF;
		for(lst = 0; lst < N; ++lst){
			if(!(sel & (1<<lst))) continue;

			tmp = cost[(sel - (1<<lst))];		//cost of connecting friends within the selected group

			for(i = 0; i < N; i++){						//cost of connecting friends on different sides
				if(!(sel & (1<<i))) continue;
				for(f = 0; f < 3; f++) tmp += !(sel & (1<<fnd[i][f]));
			}

			cost[sel] = min(cost[sel],tmp);
		}

	}

	return cost[M-1];
}

int main(){
	int i,f;

	scanf("%d",&N);
	M = 1<<N;

	for(i = 0; i < N; ++i){
		for(f = 0; f < 3; ++f){
			scanf("%d",&fnd[i][f]);
			--fnd[i][f];
		}
	}

	printf("%d\n",DP());

	return 0;
}
