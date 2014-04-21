/*
 Created By: Malvika Joshi
 Problem: Radio Telescope
*/

#include <stdio.h>

inline int left(int p){ return ((p+1)*2)-1; }
inline int right(int p){ return ((p+1)*2); }
inline int parent(int x){ return ((x+1)/2)-1; }

unsigned short A[6000010];
int freq[40010] = {0};
int lookup[40010];
int heap[40010];
int heapsize = 0;
int N,R,K;

inline int top(){ return heap[0]; }

void heaplify(int x){
	int l,r,max,temp;

	l = left(x);
	r = right(x);
	max = x;

	if(l < heapsize && freq[heap[l]] > freq[heap[max]]){ max = l; }
	if(r < heapsize && freq[heap[r]] > freq[heap[max]]){ max = r; }

	if(max != x){
		temp = heap[max];
		heap[max] = heap[x];
		lookup[heap[max]] = max;
		heap[x] = temp;
		lookup[heap[x]] = x;
		heaplify(max);
	}
}

void increase_key(int x){
	int temp,p = parent(x);
	if(x && freq[heap[x]] > freq[heap[p]]){
		temp = heap[x];
		heap[x] = heap[p];
		heap[p] = temp;
		lookup[heap[p]] = p;
		lookup[heap[x]] = x;
		increase_key(p);
	}
}

void slide(){
	int i,k,m;
	k = K;

	for(i = 0; i < k; i++){
		freq[A[i]]++;
		increase_key(lookup[A[i]]);
	}

	m = top();
	printf("%d %d\n",m,freq[m]);
	i = 0;
	while(k < N){
		freq[A[i]]--;
		heaplify(lookup[A[i]]);
		++i;
		freq[A[k]]++;
		increase_key(lookup[A[k]]);
		++k;
		m = top();
		printf("%d %d\n",m,freq[m]);
	}
}

int main(){
	int i;
	scanf("%d%d%d",&N,&K,&R);

	for(i = 0;i < N; i++){
		scanf("%d",&A[i]);
	}

	for(i = 0;i < R; i++){
		heap[i] = i;
		lookup[i] = i;
	}

	heapsize = R;
	slide();

	return 0;
}
