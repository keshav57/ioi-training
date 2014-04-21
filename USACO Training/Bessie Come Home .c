/*
 Created By: Malvika Joshi
 Problem: comehome
 Link: http://cerberus.delos.com:791/usacoprob2?S=comehome&a=bIreaa8mLtH
*/

#include <stdio.h>

#define inf 60000
#define N 52

int Graph[60][60];
int visited[60] = {0};
int dist[60];


int min_dist(){
	int i,min = inf,j;
	for(i = 0;i < N; i++){
		if(!visited[i] && dist[i] < min){
			min = dist[i];
			j = i;
		}
	}
	return j;
}

int dijkstra(){
	int i,k,vis = 0,temp;

	for(i = 0;i < N; i++){
		dist[i] = inf;
	}
	dist[N-1] = 0;

	while(vis < N){
		k = min_dist();
		visited[k] = 1;
		vis++;
		for(i = 0; i < N; i++){
			temp = dist[k] + Graph[i][k];
			if(!visited[i] && temp < dist[i]){
				dist[i] = temp;
			}
		}
	}


	int min = 26;
	for(i = 27;i < N-1; i++){
		if(dist[i] < dist[min]){
			min = i;
		}
	}
	return min;
}

int main(){

	int M,i,p1,p2,d;
	char a,b;

	for(p1 = 0; p1 < N; p1++){
		for(p2 = 0; p2 < N; p2++){
			Graph[p1][p2] = inf;
		}
	}

	scanf("%d",&M);

	for(i = 0;i < M; i++){
		scanf("\n%c %c %d",&a,&b,&d);
		p1 = a > 90 ? a - 'a' : 26 + a - 'A';
		p2 = b > 90 ? b - 'a' : 26 + b - 'A';
		Graph[p1][p2] = Graph[p1][p2] > d ? d : Graph[p1][p2];
		Graph[p2][p1] = Graph[p1][p2];
	}

	d = dijkstra();

	printf("%c %d\n",(d+'A'-26),dist[d]);

	return 0;
}
// Z = 90, a = 97
