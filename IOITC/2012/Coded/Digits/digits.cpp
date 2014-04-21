/*
 Created By: Malvika Joshi
 Problem: Digits (IOITC-2012 Final-2)
*/

#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long lli;

bool pixel(lli, lli);

int digits[16] = { 31599, 18724, 29671, 31207, 18925, 31183, 31695,
		18727, 31727, 18927, 23535, 31689, 29263, 31716, 29647, 5071 };


lli R,C;
lli c_row,c_col;

lli col_search(lli low, lli high, lli row, int tar){
	lli mid;

	while(low < high){
		mid = low+(high-low+1)/2;

		if(pixel(row,mid) == tar){
			low = mid;
		}else{
			high = mid-1;
		}
	}

	if(pixel(row,low) != tar) return -1;
	return low;
}

lli row_search(lli low, lli high, lli col, int tar){
	lli mid;

	while(low < high){
		mid = low+(high-low+1)/2;

		if(pixel(mid,col) == tar){
			low = mid;
		}else{
			high = mid-1;
		}
	}

	if(pixel(low,col) != tar) return -1;
	return low;

}

lli range_test(lli st_row, lli st_col, int m, int n, lli inc){
	lli row,col;
	int t;

	t = n;

	row = st_row;

	while(m-- && row >= 0 && row < R){
		n = t;
		col = st_col;
		while(n-- && col >= 0 && col < C){
			if(pixel(row,col)) return 1;
			col += inc;
		}
		row += inc;
	}
	return 0;
}


lli font_multiple(){
	lli row1,row2,col;

	row1 = row_search(c_row,R-1,c_col,1);
	assert(row1 >= 0);
	row2 = row_search(0,c_row,c_col,0);

	c_row= row2+1;
	col = col_search(0,c_col,c_row,0);
	c_col = col+1;

	return row1-row2;
}

lli font(){
	lli mul,fsize;
	int fac,rem,sel;

	mul = font_multiple();
	for(fac = 5; fac; --fac){
		if(mul%fac) continue;
		fsize = mul/fac;

		sel = 0;

		while(range_test(c_row-(sel*fsize),max(0LL,c_col-(fsize*15)),1,30,fsize)){
			++sel;
			if(sel > 5) break;
		}

		if(sel > 5) continue;
		rem = 5-sel;
		sel = 0;

		while(range_test(c_row+(sel*fsize+fsize),max(0LL,c_col-(fsize*15)),1,30,fsize)){
			++sel;
			if(sel > rem) break;
		}

		if(sel > rem) continue;
		assert(sel == rem);

		rem = 5-sel-1;
		c_row -= (rem*fsize);
		return fsize;
	}

	assert(0);
	return -1;
}

void go_to_integer(lli font_size){

	int sel,rem;

	sel = 0;

	while(range_test(c_row,c_col+(font_size*sel),5,1,font_size)){
		++sel;
		assert(sel <= 5);
	}

	rem = 3-sel;


	c_col -= font_size*rem;
}

void go_to_top_left(lli fsize){

	while(range_test(c_row,c_col-(6*fsize),1,3,fsize)){
		c_col -= 6*fsize;
	}
}


int get_pattern(lli row, lli col, lli fsize){
	int pattern,i,j,b;

	pattern = 0;
	for(i = 0; i < 5; ++i){
		for(j = 0; j < 3; ++j){
			if(row+(fsize*i) >= R ||col+(fsize*j) >= C) return 0;
			b = pixel(row+(fsize*i),col+(fsize*j));
			pattern |= (b<<(3*i+j));
		}
	}

	return pattern;
}

int search(int pattern){
	int i;

	for(i = 0; i < 16; ++i) if(digits[i] == pattern) return i;

	assert(0);
	return -1;
}

void solve(lli r, lli c, lli br, lli bc,
				int &ans_N, char *ans_digits, lli &ans_r, lli &ans_c){

	R = r, C = c;
	c_col = bc, c_row = br;

	lli fsize = font();

	go_to_integer(fsize);
	go_to_top_left(fsize);

	int pattern;

	pattern = get_pattern(c_row,c_col,fsize);
	ans_N = 0;
	ans_r = c_row;
	ans_c = c_col;

	while(pattern){
		ans_digits[ans_N] = search(pattern);
		ans_digits[ans_N] += ans_digits[ans_N] < 10 ? '0' : 'a'-10;
		ans_N++;
		c_col += 6*fsize;
		pattern = get_pattern(c_row,c_col,fsize);
	}

}
