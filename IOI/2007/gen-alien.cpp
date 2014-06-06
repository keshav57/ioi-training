#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
int mat[2000][2000];

int main(){
	int i,j,j2,j1;

	int M,col,x,y;
	N = 1509;
	M = 15;

	i = 47;
	j = 25;
	cout << N << endl;

	col = 1;
	for(x = 0; x < M*5; ++x){
		if(!(x%M)) col ^= 1;
		for(y =0 ; y < M*5; ++y){
			if(!(y%M)) col ^= 1;
			mat[i+x][j+y] = col;
		}
		col ^= 1;
	}

	col = 0;
	for(x= 0 ; x < N; ++x){
		for(y = 0; y < N; ++y){
			col += mat[x][y];
			if(col == 41) break;
		}
		if(y < N) break;
	}

	cout << x << " " << y << endl;

	for(x = N; x; --x){
		for(y = 1; y <= N; ++y){
			cout << mat[y][x] << " ";
		}
		cout << endl;
	}

	i += 2*M+(M/2);
	j += 2*M+(M/2);

	cout << i << " " << j << endl;

	return 0;
}
