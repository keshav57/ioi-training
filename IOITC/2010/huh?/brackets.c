/*
 Created By: Malvika Joshi
 Problem: Colouring Brackets
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 3000000
#define MCOL 25

int Color[MAXN];
int Height[MAXN];
int Width[MAXN];
int colcount[MCOL] = {0};
int seq[MAXN];

int C,H,W,N,K,S;

inline int max(int a, int b){ return a > b ? a : b; }
inline int min(int a, int b){ return a < b ? a : b; }

int getcolor(void){

	int taken[MCOL] = {0};
	int i;

	while(C && Color[C-1] != -1){
		C--;
		taken[Color[C]] = 1;
	}

	for(i = 0; i < MCOL; i++){
		if(!taken[i]){
			Color[C-1] = i;
			break;
		}
	}

	return i;
}

int getwidth(void){
	int wid = 1;
	while(W && Width[W-1] != -1){
		W--;
		wid += Width[W];
	}

	Width[W-1] = wid;
	return wid;
}

int getheight(void){

	int hei = 0;

	while(H && Height[H-1] != -1){
		--H;
		hei = max(hei,Height[H]);
	}

	hei += 2;
	Height[H-1] = hei;

	return hei;
}

void init(){

	int i;
	int hei,wid,col;

	C = H = W = 0;

	for(i = 0 ;i < N; i++){
		if(seq[i]){
			Color[C++] = -1;
			Width[W++] = -1;
			Height[H++] = -1;
		}else{
			col = getcolor();
			wid = getwidth();
			hei = getheight();
			colcount[col] += (hei*2) + (wid*4) -3;
		}
	}

	i = -1;
	S = 0;
	while(++i < MCOL && colcount[i]) S += colcount[i];

	K = i;

}

int partition(){
	int sum,bits,k,mdiff = S;

	for(bits = 0; bits < (1 << K); bits++){
		sum = 0;
		for(k = 0 ;k < K; k++){
			if((1 << k) & bits) sum += colcount[k];
		}
  		mdiff = min(mdiff,abs(S-sum-sum));
	}

	return mdiff;
}

int main(){

	int i;
	char c;
	scanf("%d\n",&N);

	for(i = 0; i < N; i++){
		c = getchar();
		seq[i] = c == '(';
	}

	init();

	printf("%d\n",partition());

	return 0;
}
