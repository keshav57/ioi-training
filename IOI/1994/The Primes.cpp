/*
 Created By: Malvika Joshi
 Problem: The Primes (IOI-1994)
 Link: http://www.ioinformatics.org/locations/ioi94/contest/day1prb3/problem.shtml
*/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>

#define DIG(d0,d1,d2,d3,d4) (d0*10000+d1*1000+d2*100+d3*10+d4)

using namespace std;

int is_prime[100010];

int mat[5][5];
int sum;

void init(){
	int i,k;

	for(i = 10000; i < 100000; ++i){
		for(k = 2; k*k <= i; ++k){
			if(i%k) continue;
			break;
		}
		if(k*k <= i) continue;
		is_prime[i] = 1;
	}
}

string sol[10000];
int S;

void print(){
	int i,j;

	for(i = 0 ; i < 5; ++i){
		for(j = 0; j < 5; ++j){
			sol[S].push_back(mat[i][j]+'0');
		}
		sol[S].push_back('\n');
	}
	++S;
}

inline void gen_col4(){
	int d0,d1,d2,d3,d4;
	int cur;

	d0 = mat[0][4];
	d2 = mat[2][4];
	d4 = mat[4][4];

	cur = d0+d2+d4+1;

	for(d1 = 1; d1 < 10 && cur < sum; ++cur, ++d1){
		mat[1][4] = d1;

		d3 = sum-cur;
		if(d3 > 9 || !(d3%2)) continue;

		if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;
		mat[3][4] = d3;

		mat[1][2] = sum-mat[1][0]-mat[1][1]-mat[1][3]-mat[1][4];
		if(mat[1][2] > 9 || mat[1][2] < 0) continue;
		if(!is_prime[DIG(mat[1][0],mat[1][1],mat[1][2],mat[1][3],mat[1][4])]) continue;

		mat[3][2] = sum-mat[3][0]-mat[3][1]-mat[3][3]-mat[3][4];
		if(mat[3][2] > 9 || mat[3][2] < 0) continue;
		if(!is_prime[DIG(mat[3][0],mat[3][1],mat[3][2],mat[3][3],mat[3][4])]) continue;

		if(mat[0][2]+mat[1][2]+mat[2][2]+mat[3][2]+mat[4][2] != sum) continue;
		if(!is_prime[DIG(mat[0][2],mat[1][2],mat[2][2],mat[3][2],mat[4][2])]) continue;

		print();
	}
}

inline void gen_col0(){
	int d0,d1,d2,d3,d4;
	int cur;

	d0 = mat[0][0];
	d2 = mat[2][0];
	d4 = mat[4][0];

	cur = d0+d2+d4+1;

	for(d1 = 1; d1 < 10 && cur < sum; ++cur,++d1){
		mat[1][0] = d1;

		d3 = sum-cur;
		if(d3 > 9) continue;

		if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;
		mat[3][0] = d3;

		gen_col4();
	}
}

inline void gen_row2(){
	int d0,d1,d2,d3,d4;
	int cur;

	d1 = mat[2][1];
	d2 = mat[2][2];
	d3 = mat[2][3];

	cur = d1+d2+d3+1;

	for(d0 = 1; d0 < 10 && cur <= sum; ++d0,++cur){

		mat[2][0] = d0;

		d4 = sum-cur;

		if(d4 > 9 || !(d4%2) ) continue;
		if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;

		mat[2][4] = d4;

		gen_col0();
	}


}

inline void gen_col3(){
	int d0,d1,d2,d3,d4;
	int cur;

	d1 = mat[1][3];
	d3 = mat[3][3];
	d4 = mat[4][3];

	cur = d1+d3+d4+1;


	for(d0 = 1; d0 < 10 && cur <= sum; ++d0,++cur){
		mat[0][3] = d0;

		d2 = sum-cur;
		if(d2 > 9) continue;

		if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;

		mat[2][3] = d2;
		mat[0][2] = sum-mat[0][0]-mat[0][1]-mat[0][3]-mat[0][4];

		if(mat[0][2] > 9 || mat[0][2] < 0) continue;
		if(!is_prime[DIG(mat[0][0],mat[0][1],mat[0][2],mat[0][3],mat[0][4])]) continue;

		gen_row2();
	}

}

inline void gen_row4(){
	int d0,d1,d2,d3,d4;
	int cur;

	d0 = mat[4][0];
	d1 = mat[4][1];
	d4 = mat[4][4];

	cur = d0+d1+d4;

	for(d2 = 0; d2 < 10 && cur <= sum; ++d2,++cur){
		mat[4][2] = d2;
		d3 = sum-cur;
		if(d3 > 9 || !(d3%2)) continue;
		if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;

		mat[4][3] = d3;

		gen_col3();
	}

}

inline void gen_col1(){
	int d0,d1,d2,d3,d4;
	int cur;

	d1 = mat[1][1];
	d3 = mat[3][1];
	cur = d1+d3+1;

	for(d0 = 1; d0 < 10 && cur <= sum; ++d0,++cur){

		mat[0][1] = d0;

		for(d2 = 0; d2 < 10 && cur <= sum; ++d2, ++cur){
			mat[2][1] = d2;

			d4 = sum-cur;
			if(d4 > 9) continue;
			if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;

			mat[4][1] = d4;
			gen_row4();
		}

		cur -= d2;
	}
}

inline void gen_sec_diag(){
	int d0,d1,d2,d3,d4;
	int cur;

	d2 = mat[2][2];
	cur= d2+1;

	for(d0 = 1; d0 < 10 && cur <= sum; ++d0,++cur){

		mat[4][0] = d0;

		for(d1 = 0; d1 < 10 && cur <= sum; ++d1,++cur){

			mat[3][1] = d1;

			for(d3 = 0; d3 < 10 && cur <= sum; ++d3, ++cur){

				mat[1][3] = d3;

				d4 = sum-cur;
				if(d4 > 9) continue;
				if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;

				mat[0][4] = d4;

				gen_col1();
			}

			cur -= d3;
		}
		cur -= d1;
	}

}

void gen_main_diag(){
	int d0,d1,d2,d3,d4;
	int cur;

	d0 = mat[0][0];
	cur= d0;

	for(d1 = 0; d1 < 10 && cur <= sum; ++d1,++cur){
		mat[1][1] = d1;

		for(d2 = 0; d2 < 10 && cur <= sum; ++d2,++cur){
			mat[2][2] = d2;

			for(d3 = 0; d3 < 10 && cur <= sum; ++d3,++cur){
				mat[3][3] = d3;

				d4 = sum-cur;
				if(d4 > 9) continue;
				if(!is_prime[DIG(d0,d1,d2,d3,d4)]) continue;

				mat[4][4] = d4;
				gen_sec_diag();
			}
			cur -= d3;
		}
		cur -= d2;
	}


}

int main(){

	int i;

	ios::sync_with_stdio(false);

	cin >> sum >> mat[0][0];

	init();
	gen_main_diag();

	sort(sol,sol+S);

	for(i = 0; i < S; ++i){
		cout << sol[i];
		if(i < S-1) cout << '\n';
	}

	return 0;
}
