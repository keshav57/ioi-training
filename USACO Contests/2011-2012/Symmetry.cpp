/*
 Created By: Malvika Joshi
 Problem Symmetry (February-2012 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=119
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <utility>
#include <iostream>

#define PI 3.14159265
#define x first
#define y second
#define NMAX 1010
#define LIM 0.0000001

using namespace std;

typedef pair<double,double> point;

point hull[NMAX];
point pts[NMAX];
int N,H;

//p2 from p1
double cross_product(point p0, point p1, point p2){
	return ((p2.x-p0.x)*(p1.y-p0.y)-(p1.x-p0.x)*(p2.y-p0.y));
}

double dot_product(point p0, point p1, point p2){
	return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y));
}

point midpt(point p1, point p2){
	return make_pair((p1.x+p2.x)/2,(p1.y+p2.y)/2);
}

int used[NMAX];

int convex_hull(){
	int i,n,p,start,cross,dist,d;

	p = 0;
	for(i = 1; i < N; ++i) p = pts[i] < pts[p] ? i : p;

	start = p;
	hull[H++] = pts[p];
	do{
		n = -1;
		dist = 0;
		for(i = 0; i < N; ++i){
			if(p == i || used[i]) continue;
			if(n == -1) n = i;

			cross = (int)cross_product(pts[p],pts[n],pts[i]);
            d = (int)dot_product(pts[p],pts[i],pts[i]);

			if(cross < 0){
				n = i;
				dist = d;
			}else if(!cross && d > dist){
				n = i;
				dist = d;
			}
		}

		p = n;
		used[p] = 1;
		hull[H++] = pts[p];
	}while(start != p);

	return --H;
}

pair<double,double> clw[NMAX];
pair<double,double> anticw[NMAX];
int C,A;

int collinear_test(point p){

	int i;
	double dist[NMAX];

	C = 0;
	for(i = 0; i < N; ++i){
		dist[i] = dot_product(p,pts[i],pts[i]);
	}

	sort(dist,dist+N);

	for(i = 0; i < N; i+=2){
		if(!dist[i]){
			--i;
			continue;
		}
		if(dist[i+1]-dist[i] < LIM) continue;
		return 0;
	}

	return 1;
}

int line_symm(point p1, point p2){
	int i;
	double angle,cross,dist;

	if(p1 == p2){
		return collinear_test(p1);
	}

	C = A = 0;
	for(i = 0; i < N; ++i){
		cross = cross_product(p1,p2,pts[i]);
		dist = dot_product(p1,pts[i],pts[i]);
		angle = atan2(cross,dot_product(p1,p2,pts[i]))*180.0/PI;
		if(abs(cross) < LIM) continue;
		if(cross < 0 && angle < 0) anticw[A++] = make_pair(angle,-dist);
		else clw[C++] = make_pair(angle,dist);
	}

	if(A^C) return 0;

	sort(clw,clw+C);
	sort(anticw,anticw+A);

	for(i = 0; i < C; ++i){
		if(abs(clw[i].first+anticw[C-i-1].first) < LIM && abs(clw[i].second+anticw[C-i-1].second) < LIM){
			continue;
		}
		return 0;
	}
	return 1;
}

int generate(){

	int valid,i,k;
	point p1,p2;

	valid = 0;
	for(i = 0, k = (H+1)/2; i < (H+1)/2; ++i,++k){
		p1 = hull[i];
		p2 = (H%2) ? midpt(hull[k],hull[k-1]) : hull[k];

		valid += line_symm(p1,p2);

		if(i == H/2) break;

		p1 = midpt(hull[i],hull[i+1]);
		p2 = (H%2) ? hull[k] : midpt(hull[k],hull[k+1]);

		valid += line_symm(p1,p2);
	}

	return valid;
}

int main(){

	int i;

	scanf("%d",&N);

	for(i = 0; i < N; ++i) scanf("%lf%lf",&pts[i].x,&pts[i].y);

	convex_hull();
	printf("%d\n",generate());

	return 0;
}
