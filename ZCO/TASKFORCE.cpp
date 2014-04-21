/*
 Created By: Malvika Joshi
 Problem: TASKFORCE
 Link: http://opc.iarcs.org.in/index.php/problems/TASKFORCE
*/

#include <stdio.h>

int Graph[3000][3000];
int Deg[3000];
int Q[3000];
bool inQ[3000];
bool deleted[3000];

int N,M,K;


int force(){

	int i,v,c;
	int H = 0;
	int T = -1;

	for(i = 0;i < N;i ++){
		if(Deg[i] < K){
			T = T+1;
			Q[T] = i;
			inQ[i] = true;
		}
	}

	while(H <= T){
		v = Q[H];
		H = H+1;

		inQ[v] = false;
		deleted[v]  = true;

		for(i = 0;i < N; i++){
			if(Graph[v][i] == 1){
				if((!inQ[i]) && (!deleted[i])){
					Deg[i] = Deg[i] - 1;
					if(Deg[i] < K){
						T = T+1;
						Q[T] = i;
						inQ[i] = true;
					}
				}
			}
		}
	}

	c = 0;
	for(i = 0;i < N;i ++){
		if(!deleted[i]){
			c++;
		}
	}

	return c;

}

int main(){

	int a,b,i,j,f;
	scanf("%d%d%d",&N, &M, &K);

	for(i = 0;i < N; i++){
		inQ[i] = false;
		deleted[i] = false;
		Deg[i] = 0;
	}

	for(i = 0;i < N;i ++){
		for(j = 0;j < N;j ++){
			Graph[i][j] = 0;
		}
	}

	for(i = 0;i < M;i ++){
		scanf("%d%d",&a,&b);
		a--;
		b--;
		Deg[a]++;
		Deg[b]++;
		Graph[a][b] = 1;
		Graph[b][a] = 1;
	}

	 f = force();

	if(f == 0){
		printf("NO");
	}else {
		printf("YES\n%d", f);
	}

	return 0;
}
