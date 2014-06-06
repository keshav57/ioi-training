#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>

#define B3 80
#define B2 75000
#define NMAX 100010
typedef long long lli;

using namespace std;

int A[NMAX];
int N,D,M;

lli compute1(){
	int i,k;
	lli tot;

	tot = 0;

	sort(A,A+N);

	k = 0;
	for(i = 1; i < N ;++i){
		while(k < i && A[i]-A[k] > D) ++k;
		tot += i-k;
	}

	return tot;
}

class bit{
private:
	int tree[2*B2];
	int N;
	int read(int x){
		if(x < 0) return 0;
		int sum;
		sum = tree[0];

		while(x){
			sum += tree[x];
			x -= (x&-x);
		}

		return sum;
	}

public:

	void init(int n){
		memset(tree,0,sizeof(tree));
		N = n;
	}

	int query(int i, int j){
		return read(j)-read(i-1);
	}

	void update(int x, int inc){
		if(!x){
			tree[x] += inc;
			return;
		}

		while(x < N){
			tree[x] += inc;
			x += (x&-x);
		}
	}
};

bit tr;

pair<int,int> pos[NMAX];

lli compute2(){
	int i,k;
	lli tot;

	tot = 0;

	sort(pos,pos+N);
	tr.init(M*2);

	k = 0;
	for(i = 0; i < N; ++i){
		while(k < i && pos[i].first-pos[k].first > D){
			tr.update(pos[k].second,-1);
			++k;
		}
		tot += tr.query(max(0,pos[i].second-D),min(M*2-1,pos[i].second+D));
		tr.update(pos[i].second,1);
	}

	return tot;
}

class bit3d{
private:

	int tree[B3*3][B3*3][B3*3];
	int N;

	int read3(int x, int y, int z){
		int sum;
		if(z < 0) return 0;
		sum = tree[x][y][0];

		while(z){
			sum += tree[x][y][z];
			z -= (z&-z);
		}

		return sum;
	}

	int read2(int x, int y, int z1, int z2){
		if(y < 0) return 0;
		int sum;
		sum = read3(x,0,z2)-read3(x,0,z1-1);

		while(y){
			sum += read3(x,y,z2)-read3(x,y,z1-1);
			y -= (y&-y);
		}

		return sum;
	}

	int read1(int x, int y1, int y2, int z1, int z2){
		if(x < 0) return 0;
		int sum;
		sum = read2(0,y2,z1,z2)-read2(0,y1-1,z1,z2);

		while(x){
			sum += read2(x,y2,z1,z2)-read2(x,y1-1,z1,z2);
			x -= (x&-x);
		}

		return sum;
	}


public:

	void init(int n){
		memset(tree,0,sizeof(tree));
		N = n;
	}

	int query(int x1, int x2, int y1, int y2, int z1, int z2){
		return read1(x2,y1,y2,z1,z2)-read1(x1-1,y1,y2,z1,z2);
	}

	void update3(int x, int y, int z, int val){
		if(!z){
			tree[x][y][z] += val;
			return;
		}

		while(z < N){
			tree[x][y][z] += val;
			z += (z&-z);
		}
	}

	void update2(int x, int y, int z, int val){
		if(!y){
			update3(x,y,z,val);
			return;
		}

		while(y < N){
			update3(x,y,z,val);
			y += (y&-y);
		}
	}

	void update(int x, int y, int z, int val){
		if(!x){
			update2(x,y,z,val);
			return;
		}

		while(x < N){
			update2(x,y,z,val);
			x += (x&-x);
		}
	}

};

bit3d tr3;

pair<pair<int,int>, pair<int,int> > pos3d[NMAX];

lli compute3(){
	int i,k;
	lli tot;

	tot = 0;
	sort(pos3d,pos3d+N);
	tr3.init(M*3);

	k =0;
	for(i = 0; i < N; ++i){
		pos3d[i].second.first += M,pos3d[i].second.second += M;
		while(k < i && pos3d[i].first.first-pos3d[k].first.first > D){
			tr3.update(pos3d[k].first.second,pos3d[k].second.first,pos3d[k].second.second,-1);
			++k;
		}

		tot += tr3.query(max(0,pos3d[i].first.second-D), min(M*3-1,pos3d[i].first.second+D),\
				max(0,pos3d[i].second.first-D), min(M*3-1,pos3d[i].second.first+D),
				max(0,pos3d[i].second.second-D), min(M*3-1, pos3d[i].second.second+D)
		);
		tr3.update(pos3d[i].first.second,pos3d[i].second.first,pos3d[i].second.second,1);
	}

	return tot;
}


int main(){
	int i,typ,x,y,z;

	scanf("%d",&typ);
	scanf("%d%d%d",&N,&D,&M);

	if(typ == 1){
		for(i = 0; i < N; ++i){
			scanf("%d",&A[i]);
		}
		printf("%lld\n",compute1());
		return 0;
	}

	if(typ == 2){
		for(i =0 ; i < N; ++i){
			scanf("%d%d",&x,&y);
			--x,--y;
			pos[i] = make_pair((x-y),(x+y));
		}
		printf("%lld\n",compute2());
		return 0;
	}

	for(i = 0; i < N; ++i){
		scanf("%d%d%d",&x,&y,&z);
		--x,--y,--z;
		pos3d[i] = make_pair (make_pair(x-y-z,x+y+z),\
				make_pair(x-y+z,x+y-z) );
	}

	printf("%lld\n",compute3());

	return 0;
}
