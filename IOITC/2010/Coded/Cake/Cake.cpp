/*
 Created By: Malvika Joshi
 Problem: Cake (IOITC-2010 TEst-6)
*/

#include <algorithm>
#include <utility>
#include <cstdio>
#include <iostream>
#include <cmath>

#define x first
#define y second
#define N_MAX 1010

using namespace std;

typedef pair<double,double> point;
typedef pair<point,point> line;

point intersection(line l1, line l2){
	double a1,b1,a2,b2,c1,c2,det;

	a1 = l1.second.y-l1.first.y;
	b1 = l1.first.x-l1.second.x;
	c1 = a1*l1.first.x+b1*l1.first.y;

	a2 = l2.second.y-l2.first.y;
	b2 = l2.first.x-l2.second.x;
	c2 = a2*l2.first.x+b2*l2.first.y;

	det = a1*b2-a2*b1;

	if(det == 0){
		return make_pair(1e5,1e5);
	}

	return make_pair((b2*c1-b1*c2)/det,(a1*c2-a2*c1)/det);
}

inline double sq_distance(point b){
	return (b.x*b.x+b.y*b.y);
}

point intr[N_MAX][N_MAX];
int n[N_MAX];

line cuts[N_MAX];
int N;

void init(){
	int i,j;

	for(i = 0; i < N; ++i){
		for(j = i+1; j < N; ++j){
			intr[i][n[i]++] = (intersection(cuts[i],cuts[j]));
		}
	}
}

int count(int radius){

	int c =0,i,k;

	for(i = 0; i < N; ++i){
		sort(intr[i],intr[i]+n[i]);
		for(k = 0; k < n[i]; ++k){
			if(k && (intr[i][k].x-intr[i][k-1].x < 0.000000001) && (intr[i][k].y-intr[i][k-1].y < 0.000000001)) continue;
			c += (sq_distance(intr[i][k]) < radius*radius);
		}
	}

	return c;
}

int main(){

	int i,rad;

	scanf("%d%d",&rad,&N);

	for(i = 0; i < N; ++i){
		scanf("%lf%lf%lf%lf",&cuts[i].first.x,&cuts[i].first.y,&cuts[i].second.x,&cuts[i].second.y);
	}

	init();
	i = count(rad);

	printf("%d\n",N+i+1);
}
