/*
 Created By: Malvika Joshi
 Problem: Farm Painting (March-2013 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=263
*/

#include <cstdio>
#include <set>
#include <algorithm>

#define MAXN 50010

using namespace std;

struct i_pt{ int x,y1,y2,type; };

i_pt x_range[MAXN*2];
set<pair<int,int> > y_range;
int N;

int compare(i_pt a, i_pt b){
	if(a.x == b.x){
		return a.y1 > b.y1;
	}
	return a.x < b.x;
}

int sweep(){

	int ins = 0, i;
	set<pair<int,int> >::iterator cov;

	for(i = 0; i < (N*2); ++i){
		if(x_range[i].type){
			cov = y_range.lower_bound(make_pair(x_range[i].y1,x_range[i].y2));
			if(cov != y_range.end() && cov->second <= x_range[i].y2){
				ins++;
				continue;
			}
			y_range.insert(make_pair(x_range[i].y1,x_range[i].y2));
			continue;
		}
		y_range.erase(make_pair(x_range[i].y1,x_range[i].y2));
	}


	return N-ins;
}

int main(){
	int i;
	scanf("%d",&N);

	for(i = 0; i < (N*2); i+=2){
		scanf("%d%d",&x_range[i].x,&x_range[i].y2);
		scanf("%d%d",&x_range[i+1].x,&x_range[i].y1);

		x_range[i].type = 1;
		x_range[i+1].y1 = x_range[i].y1;
		x_range[i+1].y2 = x_range[i].y2;
		x_range[i+1].type = 0;
	}

	sort(x_range,x_range+(N*2),compare);


	printf("%d\n",sweep());

	return 0;
}
