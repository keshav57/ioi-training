#include <cassert>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>

#define NMAX 100
#define PMAX 1010
#define x first
#define y second

using namespace std;

int gcd(int a, int b){
	int t;

	while(b){
		t = b;
		b = a%b;
		a = t;
	}

	return a;
}

typedef pair<int,int> point;

point all[PMAX*NMAX];
int idx[PMAX*NMAX];
int st[PMAX];
int en[PMAX];
int N,M;

map<point,int> sum;

point poly[PMAX];

void init(){
	int i,g,k,a,b;

	for(i = 0; i < N; ++i){
		g = gcd(poly[i].x,poly[i].y);
		if(g < 0) g*=-1;
		b = poly[i].y/g;
		a = poly[i].x/g;
		st[i] = M;
		for(k = 1; k <= g; ++k){
			all[M] = make_pair(a*k,b*k);
			idx[M++] = i;
		}
		en[i] = M;
	}
}

int vert[2];

int find_2(){
	int i,k;
	pair<int,int> add;

	map<point,int>::iterator it;

	for(i = N-1; i >= 0; --i){
		for(k = st[i]; k < en[i]; ++k){
			it = sum.find(make_pair(-all[k].x,-all[k].y));
			if(it == sum.end()) continue;
			vert[0] = k;
			vert[1] = it->second;
			return 1;
		}

		for(k = st[i]; k < en[i]; ++k){
			add = make_pair(all[k].x,all[k].y);
			sum[add] = k;
		}
	}

	return 0;
}

point vertA[5];
point vertB[PMAX];
int A,B;

int sel[NMAX*PMAX];

int main(){
	int i,j;
	point prev,cur;
	point minA,minB,minP,diff;

	scanf("%d",&N);

	scanf("%d%d",&prev.x,&prev.y);
	minP = prev;
	poly[0] = prev;
	for(i = 1; i < N; ++i){
		scanf("%d%d",&poly[i].x,&poly[i].y);
		cur = poly[i];
		poly[i].x -= prev.x, poly[i].y -= prev.y;
		prev = cur;
		minP = min(minP,prev);
	}

	poly[0].x -= prev.x, poly[0].y -= prev.y;

	init();

	if(!find_2()){
		fprintf(stderr,"Failed\n");
		exit(1);
	}

	A = 2;
	minA = make_pair((1e9),(1e9));

	for(i =0 ; i < A; ++i){
		j = vert[i];
		sel[idx[j]] = j == en[idx[j]]-1 ? -1 : j;
		vertA[i] = all[j];
		if(i) vertA[i].x += vertA[i-1].x, vertA[i].y += vertA[i-1].y;
		minA = min(minA,vertA[i]);
	}

	minB = make_pair((1e9),(1e9));
	for(i =0 ; i < N; ++i){
		if(sel[i] < 0) continue;
		if(!sel[i]) vertB[B] = all[en[i]-1];
		else vertB[B] = make_pair(poly[i].x-all[sel[i]].x,poly[i].y-all[sel[i]].y);
		if(B) vertB[B].x += vertB[B-1].x, vertB[B].y += vertB[B-1].y;
		minB = min(minB,vertB[B]);
		B++;
	}

	diff = make_pair(minP.x-minA.x,minP.y-minA.y);
	diff = make_pair(diff.x-minB.x,diff.y-minB.y);

	for(i = 0; i < B; ++i){
		vertB[i].x += diff.x;
		vertB[i].y += diff.y;
	}

	printf("%d\n",A);
	for(i = 0; i < A; ++i){
		printf("%d %d\n",vertA[i].x,vertA[i].y);
	}

	printf("%d\n",B);
	for(i = 0; i < B; ++i){
		printf("%d %d\n",vertB[i].x,vertB[i].y);
	}

	return 0;
}
