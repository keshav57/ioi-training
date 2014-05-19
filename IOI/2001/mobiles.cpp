#include <algorithm>
#include <cstdio>
#include <iostream>

#define NMAX 1030

int bit[NMAX][NMAX];
int N;

void updatey(int x, int y, int val){
	if(!y){
		bit[x][y] += val;
		return;
	}

	while(y < N){
		bit[x][y] += val;
		y += (y&-y);
	}
}

void update(int x, int y, int val){

	if(!x){
		updatey(x,y,val);
		return;
	}

	while(x < N){
		updatey(x,y,val);
		x += (x&-x);
	}
}

int queryy(int x, int y){
	if(y < 0) return 0;

	int sum;

	sum = bit[x][0];

	while(y){
		sum += bit[x][y];
		y -= (y&-y);
	}

	return sum;
}

int query(int x, int y1, int y2){
	if(x < 0) return 0;

	int sum;

	sum = queryy(0,y2)-queryy(0,y1-1);

	while(x){
		sum += queryy(x,y2)-queryy(x,y1-1);
		x -= (x&-x);
	}

	return sum;
}

int main(){
	int typ,x1,x2,y1,y2,val;

	scanf("%d%d",&typ,&N);
	scanf("%d",&typ);

	while(typ < 3){
		if(typ == 1){
			scanf("%d%d%d",&x1,&y1,&val);
			update(x1,y1,val);
		}else{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			printf("%d\n",query(x2,y1,y2)-query(x1-1,y1,y2));
		}

		scanf("%d",&typ);
	}

	return 0;
}
