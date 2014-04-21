/*
 Created By: Malvika Joshi
 Problem: Milk Scheduling (February-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=246
*/

#include <stdio.h>
#include <vector>

typedef struct {
	int marked,value,dist;
	std::vector<int> neighbours;
} cow;

cow C[10000];
int Q[10000000];
int N,M,H = 0,T = 0;

int main(void){
	int i,a,b;
	scanf("%d%d",&N,&M);

	for(i = 0;i < N;i ++){
		C[i].dist = 0;
		C[i].marked = 0;
		scanf("%d",&C[i].value);
	}

	for(i = 0;i < M; i++){
		scanf("%d%d",&a,&b);
		a--;
		b--;
		C[b].neighbours.push_back(a);
		C[a].marked = 1;
	}

	for(i = 0;i < N; i++){
		if(!C[i].marked){
			Q[T] = i;
			T++;
			C[i].dist = C[i].value;
		}
	}

	int v, u;
	while(H < T){
		v = Q[H];
		H++;

		for(i = 0;i < C[v].neighbours.size(); i++){
			u = C[v].neighbours[i];
			if(C[v].dist + C[u].value > C[u].dist){
				C[u].dist = C[v].dist + C[u].value;
				Q[T] = u;
				T++;
			}
		}
	}

	int max = 0;
	for(i = 0;i < N; i++){
		if(C[i].dist > max){
			max = C[i].dist;
		}
	}


	printf("%d",max);
	return 0;
}
