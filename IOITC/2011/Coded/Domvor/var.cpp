/*
 Created By: Malvika Joshi
 Problem: DomVar (IOITC-2011 Test-5)
*/

#include <algorithm>
#include <cassert>
#include "grader.h"

#define MAXN 100010

using namespace std;

int seq1[MAXN];
int pref1[MAXN];
int N1;

int high1,low1,mid1;

void var_start(int n, const int *var_arr){
	int i;
	N1 = n;
	for(i = 0; i < N1; ++i){
		seq1[i] = var_arr[i];
		pref1[i] = i ? pref1[i-1]+seq1[i] : seq1[i];
	}
	high1 = N1-1;
	low1 = 0;
}


void send_seq1(){
	int i,extra;

	for(i = low1; i <= high1; ++i) add_to_message(seq1[i]);

	extra = 3-(high1-low1+1);
	for(i = 0; i < extra; ++i) add_to_message(0);

	int prev,cur;

	prev = extra > 0 ? 0 : seq1[high1];
	for(i = low1; i <= high1; ++i){
		cur = seq1[i];
		add_to_message(cur^prev);
		prev = cur;
	}

	for(i = 0; i < extra; ++i){
		cur = 0;
		add_to_message(cur^prev);
		prev = cur;
	}
}

void generate1(){
	int sum,i,n;

	if(high1-low1+1 <= 5){
		send_seq1();
		return;
	}

	mid1 = low1+(high1-low1)/2;
	sum = pref1[mid1]-pref1[low1]+seq1[low1];

	n = sum ? 32-__builtin_clz(sum) : 0;
	n = max(n,3);

	for(i = 0; i < n; ++i){
		add_to_message(!!(sum&(1<<i)));
	}

	int prev,cur;

	prev = !!(sum&(1<<(n-1)));

	for(i = 0; i < n; ++i){
		cur = !!(sum&(1<<i));
		add_to_message(cur^prev);
		prev = cur;
	}
}


int recon1(int size, const int *msg){
	int i,k,sum,incos,pos1,pos2,prev,flp;

	prev = msg[size/2-1];
	incos = 0;
	pos1 = pos2 = -1;

	for(i = 0, k = size/2; i < size/2; ++i,++k){
		if((prev^msg[i]) != msg[k]){
			if(incos) pos2 = i;
			else pos1 = i;
			++incos;
		}
		prev = msg[i];
	}

	assert(incos<=2);

	flp = -1;
	if(incos == 2){
		flp = pos1;
		if(!pos1 && pos2 == size/2-1) flp = pos2;
	}

	sum = 0;
	for(i = 0; i < size/2; ++i){
		if(i == flp){
			sum |= ((msg[i]^1)<<i);
			continue;
		}
		sum |= (msg[i]<<i);
	}

	return sum;
}

int find_diff1(int size, const int *msg){
	int i,msg2,cur;

	msg2 = recon1(size,msg);

	for(i = low1; i <= high1; ++i){
		cur = !!(msg2&(1<<(i-low1)));
		if(seq1[i]^cur)	return i;
	}

	assert(0);

	return -1;
}

int time1;

int var_turn(int size, const int *msg){

	int sum,side;

	if(time1){
		mid1 = low1+(high1-low1)/2;
		if(size&1){
			low1 = mid1+1;
			--size;
		}else{
			high1 = mid1;
		}
	}

	if(high1-low1+1 <= 5) return find_diff1(size,msg);

	mid1 = low1+(high1-low1)/2;
	sum = recon1(size, msg);
	if(sum == pref1[mid1]-pref1[low1]+seq1[low1]){
		side = 1;
		low1 = mid1+1;
	}else{
		side = 0;
		high1 = mid1;
	}

	generate1();
	if(side) add_to_message(1);

	++time1;

	return -1;
}
