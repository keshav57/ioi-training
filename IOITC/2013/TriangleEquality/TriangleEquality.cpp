/*
 Created By: Malvika Joshi
 Problem: Triangle Inequality (IOITC-2013 Test-3)
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <iostream>
#include <cstring>

#define MAXN 100010

#define x first
#define y second

using namespace std;

typedef pair<int,int> point;
typedef long long lli;

class fenwick_tree {
private:
	int tree[MAXN];
	int N;

	int read(int p){
		int sum = tree[0];

		while(p){
			sum += tree[p];
			p -= (p&-p);
		}

		return sum;
	}

public:

	void res(int n){
		memset(tree,0,sizeof(int)*MAXN);
		N = n;
	}

	int query(int i, int j){
		int q0,q1;
		q0 = q1 = 0;

		if(i) q0 = read(i-1);
		q1 = read(j);

		return q1-q0;
	}

	void update(int x, int val){

		if(!x){
			tree[x] += val;
			return;
		}

		while(x <= N){
			tree[x] += val;
			x += (x&-x);
		}
	}
};

int data[MAXN][8];
fenwick_tree bit;

point pts[MAXN];
int N;

void init(){
	int i,prev,c;

	sort(pts,pts+N);

	prev = pts[0].first;
	c = 0;
	for(i = 0; i < N; ++i){
		if(pts[i].first != prev) ++c;
		prev = pts[i].first;
		pts[i].first = c;
		swap(pts[i].first,pts[i].second);
	}

	sort(pts,pts+N);
}


/*
 0 : x1 < x, y1 > y
 3 : x1 < x, y1 < y
 6 : x1 = x, y1 < y
 7 : x1 < x, y1 = y

 1 : x1 > x, y1 > y
 2 : x1 > x, y1 < y
 4 : x1 = x, y1 > y
 5 : x1 > x, y1 = y
*/

void create_data(){
	int i,less,gre;

	less = 0;

	bit.res(N);

	for(i = 1; i < N; ++i){
		while(pts[less].x < pts[i].x){
			bit.update(pts[less].y,1);
			++less;
		}
		data[i][0] = bit.query(pts[i].y+1,N);
		if(pts[i].y) data[i][3] = bit.query(0,pts[i].y-1);
		data[i][7] = bit.query(pts[i].y,pts[i].y);
		data[i][6] = i-less;
	}

	bit.res(N);

	gre = N-1;

	for(i = N-2; i >= 0; --i){
		while(pts[gre].x > pts[i].x){
			bit.update(pts[gre].y,1);
			--gre;
		}
		data[i][1] = bit.query(pts[i].y+1,N);
		if(pts[i].y) data[i][2] = bit.query(0,pts[i].y-1);
		data[i][5] = bit.query(pts[i].y,pts[i].y);
		data[i][4] = gre-i;
	}
}

/*

 0 x 2
 1 x 3

 4 x 3,2,5,6,7
 5 x 0,3,6,7
 6 x 0,1,7
 7 x 1,2
*/

lli compute(){
	int i;
	lli sum;

	sum = 0LL;
	lli tmp;

	for(i = 0; i < N; ++i){
		tmp = 0;
		tmp += (1LL*data[i][0]*data[i][2]);
		tmp += (1LL*data[i][1]*data[i][3]);

		tmp += (1LL*data[i][4]*(data[i][3]+data[i][2]+data[i][5]+data[i][6]+data[i][7]));
		tmp += (1LL*data[i][5]*(data[i][0]+data[i][3]+data[i][6]+data[i][7]));
		tmp += (1LL*data[i][6]*(data[i][0]+data[i][1]+data[i][7]));
		tmp += (1LL*data[i][7]*(data[i][1]+data[i][2]));

		sum += tmp;
	}

	return sum<<1;
}

int main(){

	int i;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&pts[i].second,&pts[i].first);
	}

	init();
	create_data();
	printf("%lld\n",compute());

	return 0;
}
