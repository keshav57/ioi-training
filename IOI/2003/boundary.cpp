#include <algorithm>
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>

#define NMAX 2000010
#define MMAX 30010

using namespace std;

struct point{
	int x,y,quad;
	bool operator< (const point &rhs)const{
		return (quad != rhs.quad ? (quad < rhs.quad) : (1LL*y*rhs.x < 1LL*x*rhs.y) );
	}
	bool operator> (const point &rhs)const{
		return (rhs < *this);
	}
};

// x < 0  , y < 0
const int quads[2][2] = { {0,3} , {1,2} };

inline int get_quad(point &p){
	return quads[p.x < 0][p.y < 0];
}

pair<point,int> block[MMAX*2];
point boundary[NMAX];

point st[MMAX];
point en[MMAX];
int M,N,N1,N2;

long long cross(point &p1, point &p2){
	return (1LL*p1.x*p2.y - 1LL*p1.y*p2.x);
}

point origin;

int init(){
	int i,inc;

	inc = 0;
	for(i = 0; i < M; ++i){
		inc += st[i].quad > en[i].quad;
		block[N1++] = make_pair(st[i],-1);
		block[N1++] = make_pair(en[i],1);
	}

	sort(block,block+N1);

	for(i = origin.y; i <= N; ++i){
		boundary[N2].x = N-origin.x , boundary[N2].y = i-origin.y;
		boundary[N2].quad = get_quad(boundary[N2]);
		++N2;
	}

	//^

	// <-----
	for(i = N-1; i >= 0; --i){
		boundary[N2].x = i-origin.x, boundary[N2].y = N-origin.y;
		boundary[N2].quad = get_quad(boundary[N2]);
		++N2;
	}

	//|
	for(i = N-1; i >= 0; --i){
		boundary[N2].x = 0-origin.x, boundary[N2].y = i-origin.y;
		boundary[N2].quad = get_quad(boundary[N2]);
		++N2;
	}

	//----->
	for(i = 1; i < N; ++i){
		boundary[N2].x = i-origin.x, boundary[N2].y = 0-origin.y;
		boundary[N2].quad = get_quad(boundary[N2]);
		++N2;
	}

	//^
	for(i = 0; i < origin.y; ++i){
		boundary[N2].x = N-origin.x, boundary[N2].y = i-origin.y;
		boundary[N2].quad = get_quad(boundary[N2]);
		++N2;
	}

	return inc;
}

int sweep(int start){
	int bl,ct,i,k;

	bl = -start;
	ct = 0;
	k = 0;

	for(i = 0; i < N2; ++i){
		while(k < N1 && block[k] <= make_pair(boundary[i],0)){
			bl += block[k].second;
			++k;
		}
		assert(bl <= 0);
		ct += !bl;
	}

	return ct;
}

int main(){
	int i,n;
	point tmp;

	scanf("%d%d",&N,&M);
	scanf("%d%d",&origin.x,&origin.y);
	origin.quad = -1;

	for(i = 0; i < M; ++i){
		scanf("%d",&n);
		scanf("%d%d",&tmp.x,&tmp.y);

		tmp.x -= origin.x, tmp.y -= origin.y;
		tmp.quad = get_quad(tmp);

		st[i] = en[i] = tmp;

		while(--n){
			scanf("%d%d",&tmp.x,&tmp.y);

			tmp.x -= origin.x, tmp.y -= origin.y;
			tmp.quad = get_quad(tmp);

			if(cross(tmp,st[i]) > 0){
				st[i] = tmp;
			}

			if(cross(tmp,en[i]) < 0){
				en[i] = tmp;
			}
		}
	}

	printf("%d\n",sweep(init()));

	return 0;
}
