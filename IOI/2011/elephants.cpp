#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 150010
#define SQRTN 390

using namespace std;

int pos[SQRTN][SQRTN*2];
int cam[SQRTN][SQRTN*2];
int end[SQRTN][SQRTN*2];
int n[SQRTN];

int A[NMAX];
int ele[NMAX];
int N,G,L;

void ins(int grp, int val){
	int i;

	assert(n[grp] < SQRTN*2);
	pos[grp][n[grp]++] = val;

	for(i = n[grp]-1; i; --i){
		if(pos[grp][i-1] <= pos[grp][i]) break;
		swap(pos[grp][i-1],pos[grp][i]);
	}
}

void del(int grp, int val){
	int i,f;

	f = 0;
	for(i =0 ; i < n[grp]-1; ++i){
		if(pos[grp][i] == val){
			f = 1;
			swap(pos[grp][i],pos[grp][i+1]);
		}
	}

	if(pos[grp][i] == val) f = 1;
//	cout << val << " " << pos[grp][n[grp]-1];
//	assert(pos[grp][n[grp]-1] == val);
//	assert(f);
	if(!f) n[grp]/=0;
	--n[grp];
}

void rec(int grp){
	int i,ptr,len;

	ptr = n[grp];
	for(i = ptr-1; i >= 0; --i){
		len = pos[grp][i] + L;

		while(pos[grp][ptr-1] > len){
			assert(ptr);
			--ptr;
		}

		cam[grp][i] = 1 + (ptr < n[grp] ? cam[grp][ptr] : 0);
		end[grp][i] = ptr < n[grp] ? end[grp][ptr] : len;
	}
}

void init(){
	int i;

	for(i = 0; i < N; ++i) ele[i] = A[i];
	sort(ele,ele+N);
	G = 0;

	for(i = 0; i < N; G++){
		n[G] = 0;
		while(i < N && n[G]*n[G] < N){
			pos[G][n[G]++] = ele[i++];
		}
	}

	for(i = 0; i < G; ++i){
		rec(i);
	}
}

void update(int k, int move){
	int i;
	for(i = 0; i < G; ++i){
		if(!n[i]) continue;
		if(pos[i][0] <= A[k] && A[k] <= pos[i][n[i]-1]) break;
	}

	assert(i < G);
	del(i,A[k]);
	rec(i);

	while(G && !n[G-1]) --G;

	//last group is never empty
	for(i = 0; i < G; ++i){
		if(n[i] && move <= pos[i][n[i]-1]) break;
	}
	i = min(i,G-1);
	ins(i,move);
	rec(i);

	A[k] = move;
}

int query(){
	int i,prev,k,tot;

	prev = -1;
	tot = 0;

	for(i = 0; i < G; ++i){
		if(!n[i]) continue;
		k = upper_bound(pos[i],pos[i]+n[i],prev)-pos[i];
		if(k >= n[i]) continue;
		tot += cam[i][k];
		prev = end[i][k];
	}

	return tot;
}

int Q;

int main(){
	int i,move,res;
	scanf("%d%d%d",&N,&L,&Q);

	for(i =0 ; i < N; ++i) {
		scanf("%d",&A[i]);
	}

	init();
	res = 0;

	for(int q = 0; q < Q; ++q){
		scanf("%d%d",&i,&move);
		update(i,move);
		printf("%d\n",query());
		++res;
		if(res*res >= Q){
			res = 0;
			init();
		}
	}

	return 0;
}
