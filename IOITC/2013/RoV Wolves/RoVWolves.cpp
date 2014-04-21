/*
 Created By: Malvika Joshi
 Problem: RoVWolves (IOITC-2013 Test-1)
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <cassert>
#include <iostream>

#define x first
#define y second
#define SQRT_MAX (int)(1e9)

using namespace std;

typedef pair<int,int> point;
typedef long long lli;

inline point corner_pos(int x){
	if(x&1)	return make_pair(x/2+1,-x/2);
	return make_pair(-x/2,x/2);
}

int corner_time(lli time){
	int high,low,mid;

	high = SQRT_MAX+1;
	low = 0;

	while(low < high){
		mid = low+(high-low+1)/2;
		if(1LL*mid*mid <= time){
			low = mid;
		}else{
			high = mid-1;
		}
	}

	return low;
}

point find_pos(lli time){
	int sqrt_cor,sign;
	point prev,next;
	lli turn,corner,end;

	sqrt_cor = corner_time(time);

	prev = corner_pos(sqrt_cor);
	next = corner_pos(sqrt_cor+1);

	corner = 1LL*sqrt_cor*sqrt_cor;
	end = 1LL*(sqrt_cor+1)*(sqrt_cor+1);
	turn = corner+sqrt_cor;

	assert(time >= corner && time < end);

	sign = -1+2*(corner&1);

	if(time <= turn){
		return make_pair(prev.x,prev.y+sign*(time-corner));
	}

	return make_pair(next.x+sign*(end-time),next.y);
}

lli find_time(point pt){
	point corner;
	int side;

	corner = make_pair(pt.x,-(pt.x-1));
	side = (corner.x*2-1);

	if(pt.x >= 0 && pt.y >= corner.y && pt.y-corner.y <= side){
		return 1LL*side*side+(pt.y-corner.y);
	}


	corner = make_pair((-pt.y)+1,pt.y);
	side = (corner.x*2-1);

	if(pt.x <= corner.x && pt.y <= 0 && corner.x-pt.x <= side){
		return 1LL*side*side-(corner.x-pt.x);
	}

	corner = make_pair(pt.x,-pt.x);
	side = (corner.y*2);

	if(pt.x <= 0 && pt.y <= corner.y && corner.y-pt.y <= side){
		return 1LL*side*side+(corner.y-pt.y);
	}

	corner = make_pair(-pt.y,pt.y);
	side = (corner.y*2);

	if(pt.x >= corner.x && pt.y >= 0 && pt.x-corner.x <= side){
		return 1LL*side*side-(pt.x-corner.x);
	}

	assert(0);
	return -1;
}



int main(){

	int query,typ;
	lli time;
	point pos;


	scanf("%d",&query);

	while(query--){
		scanf("%d",&typ);

		if(typ){
			scanf("%d %d",&pos.x,&pos.y);
			time = find_time(pos);
			printf("%lld\n",time);
			continue;
		}

		scanf("%lld",&time);
		pos = find_pos(time);
		printf("%d %d\n",pos.x,pos.y);
	}


	return 0;
}
