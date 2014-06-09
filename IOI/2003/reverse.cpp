#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;

#define R 9

int limit[8]= {8,44,80,116,152,188,224,260};

int reg[R+1];

int empty[R];
int E;

int gen[260];

void solve(int n, int op){

	int i,diff,print,k;

	reg[R-1] = n;

	diff = op+1;
	gen[reg[R-1]] = 1;
	for(i = R-2; i >= 0; --i){
		reg[i] = reg[i+1]-diff;
		if(reg[i] <= 0){
			reg[i] = 0;
			gen[0] = 1;
			break;
		}
		gen[reg[i]] = 1;
		diff += op;
	}

	//empty initially
	for(--i; i >=0 ; --i){
		empty[E++] = i;
		reg[i] = 1000;
	}

	for(i = 0; i < R; ++i){
		printf("%d ",reg[i]);
	}
	printf("\n");

	print = n+1;

	while(print--){

		if(!E){

			for(i = 0; i < R; ++i){
				if(reg[i] == print) break;
			}

			assert(i < R);
			printf("P %d\n",i+1);
			empty[E++] = i;
			reg[i] = 1000;
			continue;
		}

		for(i = print; i >= 0; --i){
			if(gen[i]) continue;
			for(k = 0; k < R; ++k){
				if(reg[k] < i && reg[k]+op >= i) break;
			}
			if(k < R) break;
		}

		if(i >= 0){
			--E;
			gen[i] = 1;
			reg[empty[E]] = reg[k]+1;
			printf("S %d %d\n",k+1,empty[E]+1);

			while(reg[empty[E]] < i){
				reg[empty[E]]++;
				printf("S %d %d\n",empty[E]+1,empty[E]+1);
			}
		}//else all are generated

		for(i = 0; i < R; ++i){
			if(reg[i] == print) break;
		}

		assert(i < R);
		printf("P %d\n",i+1);
		empty[E++] = i;
		reg[i] = 10000;
		continue;
	}

}

int main(){
	int i,k,n;

	scanf("%d%d",&k,&n);

	printf("%d\n",k);
	i = lower_bound(limit,limit+8,n)-limit;

	solve(n,i);

	return 0;
}

