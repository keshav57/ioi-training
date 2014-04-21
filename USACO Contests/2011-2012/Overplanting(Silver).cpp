/*
 Created By: Malvika Joshi
 Problem: Overplanting (February-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=115
*/

#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

#define MAXN 2010

typedef long long lli;

struct y_range{
	int y1,y2;
	bool operator< (const y_range &rhs) const {
		return y1 < rhs.y1;
	}
};

struct point {
	int x,y1,y2,type;
	bool operator< (const point &rhs) const {
		return x < rhs.x;
	}
};

y_range make_range(int y1, int y2){
	y_range r = {y1,y2};
	return r;
}

point intr[MAXN];
set<y_range> stack;
set<y_range> curr;
int N;

lli get_area(){
	lli area;
	set<y_range>::iterator i,it;
	y_range tmp;

	curr = stack;

	area = 0;
	for(i = stack.begin(); i !=stack.end(); i++){
		while(!curr.empty()){

			it = curr.lower_bound((*i));
			if(it == curr.end() || it == curr.begin()) break;

			--it;

			if(it->y2 < i->y1){
				area += it->y2-it->y1;
				curr.erase(it);
				continue;
			}

			tmp = (*it);
			tmp.y2 = max(it->y2,i->y2);
			curr.erase(it);
			curr.erase((*i));
			curr.insert(tmp);
			break;
		}
	}

	while(!curr.empty()){
		tmp = (*curr.begin());
		curr.erase(curr.begin());
		area += tmp.y2-tmp.y1;
	}

	return area;
}

lli sweep(){
	int i,px;
	lli total,tmp;
	sort(intr,intr+N);

	tmp = 0;
	px = 0;
	total = 0;

	for(i = 0; i < N; i++){
		if(intr[i].type){
			stack.erase(make_range(intr[i].y1,intr[i].y2));
		}else{
			stack.insert(make_range(intr[i].y1,intr[i].y2));
		}

		if(i < N-1 && intr[i].x == intr[i+1].x) continue;

		total += tmp*(intr[i].x-px);
		tmp = get_area();
		px = intr[i].x;
	}

	return total;
}

int main(){

	int i;

	scanf("%d",&N);
	N *= 2;

	for(i = 0; i < N; i+=2){
		scanf("%d%d%d%d",&intr[i].x,&intr[i].y2,&intr[i+1].x,&intr[i].y1);
		intr[i+1].y1 = intr[i].y1;
		intr[i+1].y2 = intr[i].y2;
		intr[i+1].type = 1;
		intr[i].type = 0;
	}


	printf("%lld\n",sweep());

	return 0;
}
