/*
 Created By: Malvika Joshi
 Problem: DomVar (IOITC-2011 Test-5)
*/

#include <algorithm>
#include <cassert>
#include "grader.h"

#define MAXN 100010

using namespace std;

int seq[MAXN];
int pref[MAXN];
int N;
int high,low,mid;

void dom_start(int n, const int *dom_arr){
	int i;
	N = n;
	for(i = 0; i < N; ++i){
		seq[i] = dom_arr[i];
		pref[i] = i ? pref[i-1]+seq[i] : seq[i];
	}
	high = N-1;
	low = 0;
}

void send_seq(){
	int i,extra;

	for(i = low; i <= high; ++i) add_to_message(seq[i]);

	extra = 3-(high-low+1);
	for(i = 0; i < extra; ++i) add_to_message(0);

	int prev,cur;

	prev = extra > 0 ? 0 : seq[high];
	for(i = low; i <= high; ++i){
		cur = seq[i];
		add_to_message(cur^prev);
		prev = cur;
	}

	for(i = 0; i < extra; ++i){
		cur = 0;
		add_to_message(cur^prev);
		prev = cur;
	}
}

void generate(){
	int sum,i,n;

	if(high-low+1 <= 5){
		send_seq();
		return;
	}

	mid = low+(high-low)/2;
	sum = pref[mid]-pref[low]+seq[low];

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

int recon(int size, const int *msg){
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

int find_diff(int size, const int *msg){

	int i,msg2,cur;

	msg2 = recon(size,msg);

	for(i = low; i <= high; ++i){
		cur = !!(msg2&(1<<(i-low)));
		if(seq[i]^cur){
			return i;
		}
	}

	assert(0);

	return -1;
}

int dom_turn(int size, const int *msg){
	if(!size){
		generate();
		return -1;
	}

	int sum,side;

	mid = low+(high-low)/2;
	if(size&1){
		low = mid+1;
		--size;
	}else{
		high = mid;
	}

	if(high-low+1 <= 5) return find_diff(size,msg);

	mid = low+(high-low)/2;
	sum = recon(size, msg);
	if(sum == pref[mid]-pref[low]+seq[low]){
		side = 1;
		low = mid+1;
	}else{
		side = 0;
		high = mid;
	}

	generate();
	if(side) add_to_message(1);

	return -1;
}
