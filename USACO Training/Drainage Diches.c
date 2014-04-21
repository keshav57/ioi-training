/*
 Created By: Malvika Joshi
 Problem: ditch
 Link: http://cerberus.delos.com:791/usacoprob2?a=qtNs6vyloOB&S=ditch
*/
#include <stdio.h>

#define nil -1
#define inf 2000000000

int Graph[201][201] = {{0}};
int visited[200];
int flow[200];
int prevnode[200];
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
	int i,a,b,d;

	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	scanf("%d%d",&M,&N);

	for(i = 0;i < M; i++){
		scanf("%d%d%d",&a,&b,&d);
		Graph[a-1][b-1] += d;
	}

	printf("%d\n",max_flow(0,N-1));

	return 0;
}
