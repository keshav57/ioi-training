#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

char box1[32];
char cur[32];
int N;

void Finalize();
void ResetBox();
void ToggleDeflectors();
long throwBall(int,int,int&,int&);
int Initialize(int);

void res(){
	ResetBox();
	memcpy(cur,box1,sizeof(box1));
}

void tog(){
	int i;
	ToggleDeflectors();
	for(i = 0; i < N; ++i){
		if(cur[i] == '.' || cur[i] == '?') continue;
		cur[i]^='\\'^'/';
	}
}

int top,lef;

void toggle(int j){
	if(cur[j] == '\\') return;
	int k,h,s;

	for(k = j-1; k >= 0; --k){
		if(cur[k]^'.') break;
	}

	if(k < 0){
		throwBall((lef > 2 ? 1 : N),lef,h,s);
		cur[j]^='\\'^'/';
		return;
	}

	toggle(k);
	throwBall((top < 3 ? k+1 : N-k),top,h,s);
	cur[j]^='\\'^'/';
}


void find_top(){

	int p,beep,k,h,s,i;

	p = -1;
	i = 0;
	while(i < N){

		if(p < 0){
			beep = throwBall((lef > 2 ? 1 : N),lef,h,s);
		}else{
			toggle(p);
			beep = throwBall((top < 3 ? p+1 : N-p),top,h,s);
			--beep;
		}

		if(!beep){
			for(k = p+1; k < N; ++k) box1[k] = '.';
			res();
			return;
		}

		if(beep == 1 && s == top){
			h = s < 3 ? h : N-h+1;
			for(k = p+1; k < h-1; ++k) box1[k] = '.';
			p = h-1;
			i = h;
			box1[p] = '/';
			res();
			continue;
		}


		res();
		tog();

		if(p < 0){
			beep = throwBall((lef > 2 ? 1 : N),lef,h,s);
		}else{
			toggle(p);
			beep = throwBall((top < 3 ? p+1 : N-p),top,h,s);
			--beep;
		}

		assert(beep == 1 && s == top);
		h = s < 3 ? h : N-h+1;
		for(k = p+1; k < h-1; ++k) box1[k] = '.';
		p = h-1;
		i = h;
		box1[p] = '\\';
		res();
	}
}

char sol[32][32];

int main(){

	int i;
	N = Initialize(0);

	memset(sol,'?',sizeof(sol));

	top = 1, lef = 4;
	memset(box1,'?',sizeof(box1));
	res();
	find_top();
	for(i =0; i < N; ++i) sol[0][i] = box1[i];

	top = 2, lef = 1;
	memset(box1,'?',sizeof(box1));
	res();
	find_top();
	for(i =0; i < N; ++i){
		if(box1[i]!='.') box1[i]^='\\'^'/';
		sol[i][N-1] = box1[i];
	}

	top = 3, lef = 2;
	memset(box1,'?',sizeof(box1));
	res();
	find_top();
	for(i =0; i < N; ++i) sol[N-1][N-i-1] = box1[i];


	top = 4, lef = 3;
	memset(box1,'?',sizeof(box1));
	res();
	find_top();
	for(i =0; i < N; ++i){
		if(box1[i]!='.') box1[i]^='\\'^'/';
		sol[N-i-1][0] = box1[i];
	}

	int j;
	for(i =0 ; i < N; ++i){
		for(j = 0; j < N; ++j){
			printf("%c",sol[i][j]);
		}
		printf("\n");
	}

	Finalize();

	return 0;
}
