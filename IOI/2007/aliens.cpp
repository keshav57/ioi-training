#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;

char out[7];
int N,ct,l,M;
int mat[2000][2000];

#define IN 1

int sent;

int is_col(int i, int j){
	int x,y;

	if(i < 1 || i > N || j < 1 || j > N) return 0;

	assert(++sent <= 300);
//	assert(i >= 1 && i <= N);
//	assert(j >= 1 && j <= N);

#ifndef IN
	x = (i-1)/M +1;
	y = (j-1)/M +1;
	return !((x+y)%2);
#endif

	return mat[i][j];
//	return out[0] == 't';
}


int verify_m(int i, int j, int m){
	assert(j <= N);
 	int r,b;
	l = i-m;

	ct = 1;
	b = 0;
	while(is_col(l,j) == b){
		ct += b;
		if(ct > 3) return 0;
		l -= m;
		b ^= 1;
	}

	r = i+m;
	b = 0;
	while(is_col(r,j) == b){
		ct += b;
		if(ct > 3) return 0;
		r += m;
		b ^= 1;
	}

	return (ct == 2 || ct == 3);
}

int search(int s, int e, int k, int b){
	int dir,mid,high,low;

	dir = s >= e ? -1 : 1;

	low = s;
	high = e;

	while(low*dir < dir*high){
		mid = (low+high+(dir < 0))/2;
		if((b && is_col(k,mid)) || (!b && is_col(mid,k))){
			low = mid+dir;
		}else{
			high = mid;
		}
	}

	if(low < 1 || low > N) return low/0;
	mid = low;
	if((b && is_col(k,mid)) || (!b && is_col(mid,k))) low += dir;


	if(low < 1 || low > N) return low/0;

	return low;
}

int main(){
	int i,j,j2,j1,d,k,m;

#ifdef IN
	scanf("%d %d %d",&N,&i,&j);

	for(int x = N; x ; --x){
		for(int y =1; y <= N; ++y){
			scanf("%d",&mat[y][x]);
		}
	}

#else

	N = (1e9)-5;
	M = (2*(1e8))-1;

//	i = 1,j = 1;
i = (N-1)/2, j = (N-1)/2;

#endif

	i = search(i,1,j,0);

	j1 = search(j,1,i+1,1);
	j2 = search(j,N,i+1,1);


	d = j2-j1-1;

	for(k = 1; k <= 5; k+=2){
		if(d%k) continue;
		if(verify_m(i+1,j1+1,d/k)) break;
	}

	assert(k <= 5);

	m = d/k;

	i = ct == 3 ? l+2*m : l+m;

	j = j1+1;

	while(j > 0 && is_col(i,j)){
		j -= 2*m;
	}
	j += 2*m;


	j += 2*m;
	i += 2*m;
	i += (m)/2;
	j += (m)/2;

//	printf("%d %d\n",i,j);


	j1 = (N+1)/2;
	j2 = j1;

	scanf("%d%d",&j1,&j2);
//	cout << j1 << " " << j2 << endl;
//	cout << i << " " << j << endl;
	assert(i == j1 && j == j2);
	cout << sent << endl;

	return 0;
}
