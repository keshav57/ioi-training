/*
 Created By: Malvika Joshi
 Problem: Network (IOITC-2012 Final-2)
*/

#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#define N_MAX 1010
#define RAD_MAX 5000
#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

double radius[N_MAX];
point centre[N_MAX];

int power[N_MAX];
int drop_rate[N_MAX];
int N;

char visited[N_MAX];
int Q[N_MAX];
int H,T;

inline double get_dist(point a, point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int bfs(point src, point tar){

	int i,v;
	double dist;

	memset(visited,0,N_MAX);
	H = T = 0;

	for(i = 0; i < N; ++i){
		dist = get_dist(src,centre[i]);
		if(dist > radius[i]) continue;
		Q[T++] = i;
		visited[i] = 1;
	}

	while(H < T){
		v = Q[H++];
		if(get_dist(tar,centre[v]) <= radius[v]) return 1;

		for(i = 0; i < N; ++i){
			if(visited[i]) continue;
			dist = get_dist(centre[v],centre[i]);
			if(dist > radius[v]+radius[i]) continue;
			Q[T++] = i;
			visited[i] = 1;
		}
	}

	return 0;
}

void compute_radii(int sig_lim){
	int i,dropped;

	for(i = 0; i < N; ++i){
		dropped = power[i]-sig_lim;
		radius[i] = (dropped*1.0)/drop_rate[i];
	}
}

int search(point src, point tar){

	int high,low,mid;

	low = 1;
	high = RAD_MAX;

	while(low < high){
		mid = low+(high-low)/2;
		compute_radii(mid);
		if(bfs(src,tar)){
			low = mid+1;
		}else{
			high = mid;
		}
	}

	return low-1;
}

int main(){
	int i;
	point src,tar;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d%d%d",&power[i],&drop_rate[i],&centre[i].x,&centre[i].y);
	}

	scanf("%d%d%d%d",&src.x,&src.y,&tar.x,&tar.y);

	printf("%d\n",search(src,tar));

	return 0;
}
