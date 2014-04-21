/*
 Created By: Malvika Joshi
 Problem: Matrix Summation
 Link: http://www.spoj.com/problems/MATSUM/
*/

#include <stdio.h>
#include <string.h>

#define MAXN 1050

int T[MAXN][MAXN];
int M[MAXN][MAXN];
int N;

void update(int x, int y, int val){
	int y1;

	while(x <= N){
		y1 = y;
		while(y1 <= N){
			T[x][y1] += val;
			y1 += (y1 & -y1);
		}
		x += (x & -x);
	}
}

int query(int x, int y){
	int y1,sum = 0;

	while(x > 0){
		y1 = y;
		while(y1 > 0){
			sum += T[x][y1];
			y1 -= (y1 & -y1);
		}
		x -= (x & -x);
	}

	return sum;
}

int main(){

	char q[4];
	int x1,y1,x2,y2,v,t;

	scanf("%d",&t);


	while(t--){

		memset(T,0,sizeof(int)*MAXN*MAXN);
		memset(M,0,sizeof(int)*MAXN*MAXN);

		scanf("%d",&N);

		while(1){
			scanf("%s",q);
			if(q[0] == 'E') break;

			if(q[1] == 'E'){
				scanf("%d%d%d",&x1,&y1,&v);
				++x1,++y1;
				update(x1,y1,v-M[x1][y1]);
				M[x1][y1] = v;
				continue;
			}

			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			++x1,++y1,++x2,++y2;

			v = query(x2,y2) + query(x1-1,y1-1) - query(x1-1,y2) - query(x2,y1-1);
			printf("%d\n",v);
		}

		printf("\n");
	}

	return 0;
}
