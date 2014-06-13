#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

char init[32][32];
char cur[32][32];
int N;

void Finalize();
void ResetBox();
void ToggleDeflectors();
long throwBall(int,int,int&,int&);
int Initialize(int);

void res(){
	ResetBox();
	memcpy(cur,init,sizeof(init));
}

void tog(){
	int i,j;
	ToggleDeflectors();
	for(i = 0; i < N; ++i){
		for(j =0 ; j < N; ++j){
			if(cur[i][j] == '.' || cur[i][j] == '?') continue;
			cur[i][j]^='\\'^'/';
		}
	}
}

int b;

//0 down, 1 right

int h_out,s_out,bee;

void left_send(int , int , int );
void right_send(int , int , int );
void fix2(int,int);


void fix1(int x, int y){

	if(cur[x][y]^'/') return;

	int i,j;
	i = x, j = y;

	while(--j >= 0){
		fix1(i,j);
	}

	while(--i >= 0){
		for(j = y; j < N; ++j){
			fix2(i,j);
		}
		for(j = y-1; j >= 0; --j){
			fix1(i,j);
		}
	}

	i = x;
	j = y;
	while(--j >= 0){
		if(cur[i][j]^'.') break;
	}
	right_send(i,j,1);
	left_send(x,y,1);
}

void fix2(int x, int y){
	if(cur[x][y]^'\\') return;

	int i,j;

	i = x;
	j = y;

	while(++j < N){
		fix2(i,j);
	}

	while(--i >= 0){
		for(j = y; j >= 0; --j){
			fix1(i,j);
		}
		for(j = y+1; j < N; ++j){
			fix2(i,j);
		}
	}

	i = x;
	j = y;
	while(--i >= 0){
		if(cur[i][j]^'.') break;
	}

	right_send(i,j,0);
	left_send(x,y,0);
}

int ct2;

void right_send(int i, int j, int d){
	if(i < 0 || j < 0){
		if(d){
			assert(i >= 0);
			bee = throwBall((b ? i+1 : N-i),(b ? 4 : 2),h_out,s_out);
			return;
		}
		assert(j >= 0);
		bee = throwBall((b ? j+1 : N-j),(b ? 1 : 3),h_out,s_out);

		return;
	}

	int x,y;

	x = i, y = j;

	while(x >= 0 && y >= 0){
		x -= d;
		y -= (!d);
		if(cur[x][y]^'.') break;
	}

//	assert(cur[i][j] == '/');
	right_send(x,y,!d);
	cur[i][j]^='\\'^'/';
	++ct2;
}

int ct;

//0 down, 1 left
void left_send(int i, int j, int d){
	if(i < 0 || j >= N){
		if(d){
			assert(i >= 0);
			bee = ct, h_out = (b ? i+1 : N-i), s_out = (b ? 2 : 4);
			return;
		}
		assert(j <= N);
		bee = ct, h_out = (b ? j+1 : N-j), s_out = (b ? 1 : 3);
		return;
	}

	int x,y;

	x = i, y = j;

	while(x >= 0 && y < N){
		x -= d;
		y += (!d);
		if(cur[x][y]^'.') break;
	}

//	assert(cur[i][j] == '\\');

	++ct;
	left_send(x,y,!d);
	cur[i][j]^='\\'^'/';
}

void fix_all(int x, int y){
	int i,j;
	i = x, j = y;

	while(--j >= 0){
		fix1(i,j);
	}

	while(--i >= 0){
		for(j = y; j < N; ++j){
			fix2(i,j);
		}
		for(j = y-1; j >= 0; --j){
			fix1(i,j);
		}
	}
}


void find(){
	int pi,pj,beep,i,j,s,h;

	for(i = 0; i < (N+b)/2; ++i){
		pi = i;
		pj  =-1	;
		for(j = 0; j < N; ++j){
			fprintf(stderr,"%d %d\n",b ? i : N-i-1, b ? j : N-j-1);

			fix_all(i,j);

			ct = 0,ct2 = 0;
			cur[i][j] = '/';
			left_send(i,j,1);
			s = s_out;
			h = h_out;
			beep = bee;
			right_send(pi,pj,1);

			bee -= ct2;
			if(s_out == s && h_out == h && beep == bee){
				init[i][j] = '/';
				pi = i, pj = j;
				res();
				continue;
			}
			res();
			tog();

			fix_all(i,j);
			ct = 0,ct2 = 0;
			cur[i][j] = '/';
			left_send(i,j,1);
			s = s_out;
			h = h_out;
			beep = bee;
			right_send(pi,pj,1);

			bee -= ct2;
			if(s_out == s && h_out == h && beep == bee){
				init[i][j] = '\\';
				pi = i, pj = j;
				res();
				continue;
			}

			init[i][j] = '.';
			res();
		}
	}

}

char sol[32][32];

int main(){

	int i,j;
	N = Initialize(0);

	memset(init,'?',sizeof(init));
	res();

	b = 1;
	find();
	memcpy(sol,init,sizeof(init));
	memset(init,'?',sizeof(init));

	for(i =0 ; i < (N+1)/2; ++i){
		for(j = 0 ; j < N; ++j){
			printf("%c",sol[i][j]);
		}
		printf("\n");
	}

	b =  0;
	find();


	for(i = (N/2)-1; i >= 0; --i){
		for(j = N-1; j >=0 ; --j){
			printf("%c",init[i][j]);
		}
		printf("\n");
	}

	Finalize();

	return 0;
}
