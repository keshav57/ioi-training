#include <algorithm>
#include <iostream>
#include <cassert>
#include <set>

#define NMAX 150010
#define CMAX 300010

using namespace std;

class bit{
private:
	int tree[CMAX];
	int N;

	void inc(int x, int val){
		if(!x){
			tree[x] += val;
			return;
		}
		while(x < N){
			val += 1;
			x += (x&-x);
		}
	}

public:

	void init(int n){
		N = n;
		memset(tree,0,sizeof(tree));
	}

	void update(int i, int j, int val){
		inc(i,val);
		inc(j+1,-val);
	}

	int query(int x){
		int sum = tree[0];
		while(x){
			sum += tree[x];
			x -= (x&-x);
		}

		return sum;
	}

};

bit T;
int pos[CMAX];
int C,N;

int ele[NMAX];
multiset<int> stage;

int upper_bound(int tar){
	int high,low,mid,cur;

	low = 0;
	high = C-1;

	while(low < high){
		mid = (low+high)/2;
		cur = T.query(mid)+pos[mid];

		if(cur <= tar){
			low = mid+1;
		}else{
			high = mid;
		}
	}

	return low;
}

void del(int idx){
	int prev,cam,shift;
	multiset<int>::iterator it;

	prev = ele[idx];
	it = stage.find(prev);
	cam = upper_bound(prev);

	if(pos[cam]+T.query(cam) != prev || ++it == stage.end()){
		ele[idx] = -1;
		stage.erase(--it);
		return;
	}

	shift = *it-prev;
	T.update(cam,C-1,shift);

	stage.erase(it);
	ele[idx] = -1;
}


