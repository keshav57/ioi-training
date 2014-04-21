/*
 Created By: Malvika Joshi
 Problem: Cows Crossing (February-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=242
*/

#include <stdio.h>
#include <algorithm>

typedef struct { int x1,x2; } point;

int X2[100000];
point Cows[100000];
int N;

int compare(point a, point b){ return a.x1 < b.x1; }

int main(){
	int i,sm,gre,safe = 0;

	scanf("%d",&N);

	for(i = 0;i < N;i ++){
		scanf("%d%d",&Cows[i].x1,&Cows[i].x2);
		X2[i] = Cows[i].x2;
	}

	std::sort(Cows,Cows+N,compare);
	std::sort(X2,X2+N);

	sm = Cows[0].x2;
	gre = Cows[0].x2;

	for(i = 0;i < N; i++){
		if(Cows[i].x2 >= gre && Cows[i].x2 == X2[i]){
			safe++;
		}
		if(Cows[i].x2 > gre){ gre = Cows[i].x2; }
	}

	printf("%d\n",safe);

	return 0;
}
