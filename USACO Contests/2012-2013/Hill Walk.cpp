/*
 Created By: Malvika Joshi 
 Problem: Hill Walk (March-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=266
*/

#include <cstdio>
#include <algorithm>
#include <set>

#define MAXN 100010

using namespace std;

struct seg{
	int x1,x2,y1,y2,id;

	bool operator<(seg const& lhs) const {
		if (x2 < lhs.x2) {
			return (long long) (y2 - lhs.y1) * (long long) (lhs.x2 - lhs.x1) >
			       (long long) (lhs.y2 - lhs.y1) * (long long) (x2 - lhs.x1);
		} else {
			return (long long) (lhs.y2 - y1) * (long long) (x2 - x1) <
			       (long long) (y2 - y1) * (long long) (lhs.x2 - x1);
		}
	}

};

struct i_x {
	int x,typ,id,y;

	bool operator<(i_x const& o) const {
		if (x == o.x) {
			return y < o.y;
		}
		return x < o.x;
	}
};

seg H[MAXN];
i_x intr[MAXN*2];
set<int> visited;
set<seg> Q;
int N,P;
seg cur_hill;

void init(){
	int i;

	for(i = 0; i < N; i++){
		H[i].id = i;

		intr[P].id = i;
		intr[P].typ = 0;
		intr[P].x = H[i].x1;
		intr[P++].y = H[i].y1;

		intr[P].id = i;
		intr[P].typ = 1;
		intr[P].x = H[i].x2;
		intr[P++].y = H[i].y2;
	}

	sort(intr,intr+P);
	cur_hill = H[0];
}

int sweep(){
	int i;
	seg tmp;

	for(i = 0; i < P; i++){
		tmp = H[intr[i].id];

		if(intr[i].typ){
			Q.erase(tmp);
		}else{
			if(tmp < cur_hill) continue;
			Q.insert(tmp);
		}

		if(Q.empty()) break;
		cur_hill = (*Q.begin());
		visited.insert(cur_hill.id);
	}
	return (int)visited.size();
}

int main(){

	int i;

	freopen("hillwalk.in","r",stdin);
	freopen("hillwalk.out","w",stdout);

	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%d%d%d%d",&H[i].x1,&H[i].y1,&H[i].x2,&H[i].y2);
	}

	init();
	i = sweep();

	printf("%d\n",i);

	return 0;
}

