/*
 Created By: Malvika Joshi
 Problem: Party Invitations (January-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=228
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

std::vector<int> G[250000];
std::vector<int> C[1000000];
int Q[250000],H = 0,T = 0;
int cv[1000000] = {0};
int gi[250000] = {0};
int N,M;

int getunvis(int g){
	unsigned i;
	for(i = 0;i < G[g].size(); i++){
		if(!cv[G[g][i]]){
			return G[g][i];
		}
	}
	return -1;
}

int bfs(){

	int i,vis,v,g,n,temp;

	vis = 0;
	Q[T] = 0;
	T++;
	cv[0] = 1;

	while(H < T){
		v = Q[H];
		H++;
		vis++;
		n = C[v].size();
		for(i = 0;i < n; i++){
			g = C[v][i];
			gi[g]++;
			if(G[g].size() == gi[g]+1){
				temp = getunvis(g);
				if(temp != -1){
				cv[temp] = 1;
				Q[T] = temp;
				T++;
				}
			}
		}
	}

	return vis;
}

int main(void){

	int i,j,n,temp;
	scanf("%d%d",&N,&M);

	for(i = 0;i < M; i++){
		scanf("%d",&n);
		for(j = 0;j < n; j++){
			scanf("%d",&temp);
			temp--;
			C[temp].push_back(i);
			G[i].push_back(temp);
		}
	}

	printf("%d\n", bfs());

	return 0;
}
