/*
 Created By: Malvika Joshi
 Problem: Bovine Ballet (US Open -2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=278
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_F 4

int posx[MAX_F]= {0,1,0,1},posy[MAX_F]= {0,0,-1,-1};
int side = 0,inc= 1,maxx,maxy,minx,miny;
int N;

inline int max(int a, int b){
	return a > b? a: b;
}

inline int min(int a, int b){
	return a < b? a : b;
}

void make_move(int foot,int mside, int minc){

	if(side == mside){
		if(side) minc*= -1;
		posy[foot] += (minc*inc);
	}else {
		posx[foot] += (minc*inc);
	}
}

void make_pivot(int foot){

	int i,x,y;

	for(i = 0;i < MAX_F; ++i){
		if(i == foot) continue;
		y = posx[i]-posx[foot];
		x = posy[i]-posy[foot];
		posx[i] = posx[foot]+x;
		posy[i] = posy[foot]-y;
	}

	if(side) inc *= -1;
	side ^= 1;
}

void update(){
	int i;

	for(i= 0; i < MAX_F; i++){
		maxx= max(maxx,posx[i]);
		maxy= max(maxy,posy[i]);
		minx= min(minx,posx[i]);
		miny= min(miny,posy[i]);
	}
}

int main(){
	int i;
	char ins[4];

	int foot,mside,minc;

	freopen("ballet.in","r",stdin);
	freopen("ballet.out","w",stdout);
	scanf("%d",&N);

	maxx = 1;
	minx = 0;
	maxy = 0;
	miny = -1;

	for(i = 0 ; i < N; i++){
		scanf("%s",ins);

		if(ins[0] == 'F'){
			if(ins[1] == 'L')foot = 0;
			else foot = 1;
		}else{
			if(ins[1] == 'L')foot = 2;
			else foot = 3;
		}

		if(ins[2] == 'P'){
			make_pivot(foot);
			update();
			continue;
		}

		if(ins[2] == 'R' || ins[2] == 'L'){
			mside = 1;
			minc = ins[2] == 'R' ? 1 : -1;
		}else{
			mside = 0;
			minc = ins[2] == 'F' ? 1 : -1;
		}

		make_move(foot,mside,minc);
		update();
	}

	printf("%d\n",(maxx-minx+1)*(maxy-miny+1));

	return 0;
}
