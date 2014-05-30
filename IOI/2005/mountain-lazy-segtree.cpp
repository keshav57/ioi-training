#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define TMAX 4200000

using namespace std;


struct node{
	int left,right,par,size;
};

class segment_tree{
private:

	node tree[TMAX];
	int time[TMAX];
	int inc[TMAX];
	int sum[TMAX];
	int high[TMAX];
	int T,cur_time,N;

	int create_node(int s, int e, int par){
		tree[T].size = (e-s+1);
		tree[T].par = par, tree[T].left = -1, tree[T].right = -1;
		time[T] = inc[T] = sum[T] = high[T] = 0;
		return T++;
	}

	void tree_update(int s, int e, int n, int i, int j, int k){
		if(tree[n].par >= 0 && time[tree[n].par] > time[n]){
			time[n] = time[tree[n].par];
			inc[n] = inc[tree[n].par];
			sum[n] = inc[tree[n].par]*tree[n].size;
			high[n] = max(inc[n],sum[n]);
		}

		if(s > j || e < i) return;

		if(s >= i && e <= j){
			time[n] = cur_time;
			inc[n] = k;
			sum[n] = k*tree[n].size;
			high[n] = max(inc[n],sum[n]);
			return;
		}

		if(tree[n].left < 0)	tree[n].left = create_node(s,(s+e)/2,n);
		tree_update(s,(s+e)/2,tree[n].left,i,j,k);

		if(tree[n].right < 0) tree[n].right = create_node((s+e)/2+1,e,n);
		tree_update((s+e)/2+1,e,tree[n].right,i,j,k);

		sum[n] = sum[tree[n].left] + sum[tree[n].right];
		high[n] = max(high[tree[n].left],sum[tree[n].left]+high[tree[n].right]);
	}

	int search(int s, int e, int n, int k){

		if(tree[n].par >= 0 && time[tree[n].par] > time[n]){
			time[n] = time[tree[n].par];
			inc[n] = inc[tree[n].par];
			sum[n] = inc[tree[n].par]*tree[n].size;
			high[n] = max(inc[n],sum[n]);
		}

		if(high[n] <= k) return e+1;

		if(tree[n].left < 0){
			assert(tree[n].right < 0);
			return s+(k/inc[n]);
		}

		assert(tree[n].right >= 0);
		int tmp;

		tmp = search(s,(s+e)/2,tree[n].left,k);
		if(tmp <= (s+e)/2) return tmp;

		k -= sum[tree[n].left];

		return search((s+e)/2+1,e,tree[n].right,k);
	}

public:

	void init(int n){
		N = n;
		T = 1;
		cur_time = 0;
		tree[0].left = tree[0].right = tree[0].par = -1;
		time[0] = inc[0] = sum[0] = high[0] = 0;
		tree[0].size = N;
	}

	void update(int i, int j, int k){
		++cur_time;
		tree_update(0,N-1,0,i,j,k);
	}

	int query(int k){
		return search(0,N-1,0,k)-1;
	}

	void printT(){
		cout << T << endl;
	}
};

int N;
segment_tree T;

int main(){
	int i,j,k;
	char c;

	scanf("%d",&N);
	T.init(N+1);

	scanf(" %c",&c);
	while(c != 'E'){

		if(c == 'I'){
			scanf("%d%d%d",&i,&j,&k);
			scanf(" %c",&c);
			T.update(i,j,k);
			continue;
		}

		scanf("%d",&k);
		printf("%d\n",T.query(k));

		scanf(" %c",&c);
	}

	return 0;
}


