/*
 Created By: Malvika Joshi
 Problem: Under The Microscope (IOITC-2012 Test 1)
*/

#include <stdio.h>

typedef struct {long long x,y; } point;

long long N,K;
point upper,lower;


int main(){

	int i;
	long long rows,cols,d,moves= 0;
	point p;

	scanf("%lld%lld",&rows,&cols);
	scanf("%lld%lld",&lower.x,&lower.y);
	lower.x --;
	lower.y --;
	upper.x = 0;
	upper.y = 0;

	scanf("%lld",&N);

	for(i = 0;i < N; i++){
		scanf("%lld%lld",&p.x,&p.y);
		if(p.x > lower.x){
			d = p.x-lower.x;
			lower.x += d;
			upper.x += d;
			moves += d;
		}else if(p.x < upper.x){
			d = upper.x - p.x;
			upper.x -= d;
			lower.x -= d;
			moves += d;
		}

		if(p.y > lower.y){
			d = p.y-lower.y;
			lower.y += d;
			upper.y += d;
			moves += d;
		}else if(p.y < upper.y){
			d = upper.y - p.y;
			upper.y -= d;
			lower.y -= d;
			moves += d;
		}
	}

	printf("%lld",moves);

	return 0;
}
