/*
 Created By: Malvika Joshi
 Problem: stall4
 Link: http://cerberus.delos.com:791/usacoprob2?a=qtNs6vyloOB&S=stall4
*/

#include <stdio.h>

#define nil -1
#define inf 2000000000

int Graph[402][402] = {{0}};
int visited[402];
int flow[402];
int prevnode[402];
int N,M;

inline int min(int a ,int b){ return a < b ? a: b; }

int max_flow(int src,int sink){
	if(src == sink){
		return inf;
	}

	int totalflow = 0,i,maxflow,maxloc,pathcapacity,curnode,nextnode;

	while(1){
		for(i = 0;i < N; i++){
			prevnode[i] = nil;
			flow[i] = 0;
			visited[i] = 0;
		}

		flow[src] = inf;

		while(1){
			maxflow = 0;
			maxloc = nil;
			for(i = 0;i < N; i++){
				if(flow[i] > maxflow && !visited[i]){
					maxflow = flow[i];
					maxloc = i;
				}
			}

			if(maxloc == nil) break;
			if(maxloc == sink) break;

			visited[maxloc] = 1;

			for(i = 0;i < N; i++){
				if(!Graph[maxloc][i]) continue;
				if(flow[i] < min(maxflow,Graph[maxloc][i])){
					prevnode[i] = maxloc;
					flow[i] = min(maxflow,Graph[maxloc][i]);
				}
			}
		}
		if(maxloc == nil) break;

		pathcapacity = flow[sink];
		totalflow += pathcapacity;

		curnode = sink;
		while(curnode != src){
			nextnode = prevnode[curnode];
			Graph[nextnode][curnode] -= pathcapacity;
			Graph[curnode][nextnode] += pathcapacity;
			curnode = nextnode;
		}
	}

	return totalflow;
}

int main(){
	int i,k,n,s;

	scanf("%d%d",&N,&M);

	for(i = 1;i <= N; i++){
		scanf("%d",&n);
		for(k = 0;k < n; k++){
			scanf("%d",&s);
			Graph[i][N+s] = 1;
		}
	}

	for(i = 1; i <= N; i++){
		Graph[0][i] = 1;
	}

	for(i = 1; i <= M; i++){
		Graph[N+i][N+M+1] = 1;
	}

	N+= M+2;

	printf("%d\n",max_flow(0,N-1));

	return 0;
}
