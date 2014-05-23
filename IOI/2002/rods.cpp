#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

int gridsize();
int rect(int , int , int ,int);
void report(int , int , int , int , int , int , int , int );

int N;

int search_row(int r1, int r2, int c1, int c2){
	assert(rect(min(r1,r2),max(r1,r2),min(c1,c2),max(c1,c2)));

	int len,row,row2,dir;

	row = r1;
	len = r2-r1;

	dir = len < 0 ? -1 : 1;

	for(; len ; len /= 2){
		row2 = row+len/2;
		if(!rect( min(row,row2), max(row,row2),c1,c2)){									//row2 need not be greater than row
			row = row2+dir;
		}
	}

	return row;
}

int rr1,rr2,cc1,cc2,pp1,pp2,qq1,qq2;

int search_col(int r1, int r2, int c1, int c2){
	assert(rect(min(r1,r2),max(r1,r2),min(c1,c2),max(c1,c2)));

	int len,col,col2,dir;

	col = c1;
	len = c2-c1;
	dir = len < 0 ? -1 : 1;

	for(; len ; len /= 2){
		col2 = col+len/2;
		if(!rect(r1,r2,min(col,col2),max(col,col2))){
			col = col2+dir;
		}
	}

	return col;
}

void found_intersection(int r1, int c1){

	pp2 = r1;
	qq2 = search_col(r1,r1,N,c1);

	cc2 = c1;
	rr2 = search_row(N,r1,c1,c1);
}

int main(){
	N = gridsize();

	int i,j,b,r,t,l;

	i = search_row(1,N,1,N);
	j = search_col(i,i,1,N);

	//nothing on top, nothing to the left

	b = r = 0;
	if(i < N) b = rect(i+1,i+1,j,j);
	if(j < N) r = rect(i,i,j+1,j+1);

	assert(b || r);

	if(b && r){
		rr1 = i,cc1 = j,pp1 = i,qq1 = j;
		found_intersection(i,j);
		report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);
	}
	else if(b){
		rr1 = i, cc1 = j;

		if(j > 1 && rect(1,N,1,j-1)){
			pp1 = search_row(i+1,N,1,j-1);
			qq1 = search_col(pp1,pp1,1,j-1);
		}else{
			assert(j < N);
			pp1 = search_row(i,N,j+1,N);
			qq1 = search_col(pp1,pp1,j+1,N);
		}

		t = l = 0;
		if(pp1 > 1) t = rect(pp1-1,pp1-1,j,j);

		if(qq1 > 1 && rect(pp1,pp1,qq1-1,qq1-1)){
			--qq1;
			if(t){
				found_intersection(pp1,qq1);
				report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);
			}else{
				cc2 = cc1;
				pp2 = pp1;
				qq2 = search_col(pp1,pp2,N,qq1);
				rr2 = search_row(pp1-1,rr1,cc1,cc2);
				report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);
			}
		}


		if(j > 1) l = rect(pp1,pp1,j-1,j-1);

		if(t && l){
			found_intersection(pp1,j);
			report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);
		}

		cc2 = cc1;
		pp2 = pp1;

		if(t && cc1 > qq1){
			qq2 = search_col(pp1,pp2,cc1-1,qq1);
		}else{
			qq2 = search_col(pp1,pp2,N,qq1);
		}

		if(l && pp1 > rr1){
			rr2 = search_row(pp1-1,rr1,cc1,cc2);
		}else{
			rr2 = search_row(N,rr1,cc1,cc2);
		}

//		i /= 0;

		report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);

	}
	else{

		pp1= i,qq1 = j;

		assert(i < N);

		rr1 = search_row(i+1,N,1,N);
		cc1 = search_col(rr1,rr1,1,N);

		if(rect(rr1-1,rr1-1,cc1,cc1)){
			--rr1;

			assert(rr1 == pp1);
			assert(cc1);
			if(rect(rr1,rr1,cc1-1,cc1-1)){
				found_intersection(rr1,cc1);
				report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);

			}else{
				cc2 = cc1;
				rr2 = search_row(N,rr1,cc1,cc2);

				pp2 = pp1;
				qq2 = search_col(pp1,pp2,cc1-1,qq1);
				report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);
			}
		}

//		i /= 0;
		cc2 = cc1;
		rr2 = search_row(N,rr1,cc1,cc2);

		pp2 = pp1;
		qq2 = search_col(pp1,pp2,N,qq1);
		report(rr1,cc1,rr2,cc2,pp1,qq1,pp2,qq2);
	}

	return 0;
}
