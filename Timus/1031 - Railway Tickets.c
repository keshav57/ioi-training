/*
 Created By: Malvika Joshi
 Problem: Railway Tickets
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1031
*/

#include <stdio.h>
#define inf 10000000000000001

int dist[10010];
int P1[10010];
int P2[10010];
int P3[10010];
long long cost[10010];

long long C1,C2,C3;
int N,L1,L2,L3,S,E;

inline int distance(int a, int b){ return dist[b] - dist[a]; }
inline long long min(long long  a, long long b){ return a < b ? a : b; }

void init(){
	int i,p1 = S,p2 = S,p3 = S;

	for(i = S;i <= E; i++){
		while(distance(p1,i) > L1){ ++p1; }
		while(distance(p2,i) > L2){ ++p2; }
		while(distance(p3,i) > L3){ ++p3; }
		P1[i] = p1;
		P2[i] = p2;
		P3[i] = p3;
	}
}

long long DP(){
	cost[S] = 0;
	int i;
	long long c1,c2,c3;

	for(i = S+1;i <= E; i++){
		c1 = P1[i] == i ? inf : C1 + cost[P1[i]];
		c2 = P2[i] == i ? inf : C2 + cost[P2[i]];
		c3 = P3[i] == i ? inf : C3 + cost[P3[i]];
		cost[i] = min(c1,min(c2,c3));
	}

	return cost[E];
}

int main(){
	int i;
	scanf("%d%d%d%lld%lld%lld",&L1,&L2,&L3,&C1,&C2,&C3);
	scanf("%d%d%d",&N,&S,&E);
	S--;
	E--;
	if(S > E){
		i = S;
		S = E;
		E = i;
	}
	dist[0] = 0;
	for(i = 1;i < N; i++){
		scanf("%d",&dist[i]);
	}

	init();
	printf("%lld\n",DP());
	return 0;
}
