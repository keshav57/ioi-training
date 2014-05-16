#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>

#define NMAX 10010

#define x first
#define y second

using namespace std;
typedef pair<int,int> point;

point p0;

int equal(point a, point b){
	return 1LL*(a.y-p0.y)*(b.x-p0.x) == 1LL*(b.y-p0.y)*(a.x-p0.x);
}


double dist(point a, point b){
	return sqrt(1LL*(a.x-b.x)*(a.x-b.x)+1LL*(a.y-b.y)*(a.y-b.y));
}

int compare(point a, point b){
	long long q1,q2;
	q1 = 1LL*(a.y-p0.y)*(b.x-p0.x);
	q2 = 1LL*(b.y-p0.y)*(a.x-p0.x);
	return q1 == q2 ? dist(p0,a) < dist(p0,b) : q1 < q2;
}

long long cross(point p0, point p1, point p2){
	return (1LL*(p1.x-p0.x)*(p2.y-p0.y) - 1LL*(p2.x-p0.x)*(p1.y-p0.y));
}

point pos[NMAX];

int N;

point stack[NMAX];
int S;

void compute(int b){
	int i;

	sort(pos,pos+N,compare);

	S = 0;
	stack[S++] = p0;

	for(i = 0; i < N; ++i){
//		if(b && i < N-1 && equal(pos[i],pos[i+1])) continue;

		if(i < N-1 && pos[i] == pos[i+1]) continue;

		/*
		 If the points with equal polar angles are skipped, then the convex hull will still have colinear points because of the next line.
		 If it pop elements from the stack when the cross product was >= 0, then the convex hull will not have any colinear points beacause
	 	 If the points with same coordinates are not skipped, the top element and the element before it on the stack will be the same and any point will be colinear with them, so the convex hull no longer remains convex.
		 All the points will be sorted in counterclockwise order leaving the points which can possibly be on the last edge of the convex hull. If we need all the points on the boundary, we'll have to consider that case separately,
		*/

		while(S > 1 && cross(stack[S-2],pos[i],stack[S-1]) > 0){
			--S;
		}
		stack[S++] = pos[i];
	}

}

int main(){
	int i,k;

	scanf("%d",&N);

	k = -1;
	for(i = 0; i < N; ++i){
		scanf("%d%d",&pos[i].x,&pos[i].y);
		if(k < 0 || pos[k].x >= pos[i].x){
			if(k < 0 || pos[k].x != pos[i].x) k = i;
			else if(pos[i].y < pos[k].y) k = i;
		}
	}

	p0 = pos[k];
	swap(pos[k],pos[N-1]);
	--N;

	compute(1);

	double len,d;

	len = 0;


	for(i = 1; i < S; ++i){
		d = dist(stack[i],stack[i-1]);
		len += d;
	}
	d = dist(stack[i-1],stack[0]);
	len += d;

	printf("%d\n",(int)len);

	return 0;
}
