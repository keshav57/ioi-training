#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>

using namespace std;
typedef long long lli;

int bits[(1<<17)+2];

int cow[50][8];

lli subset[25];
int other[25];
int mem[(1<<24)];

int P,N,V;

void init(){
	int i,k,j,pos;

	memset(mem,-1,sizeof(mem));

	for(i = 0; i < P; ++i){
		for(k = 0; k < 3; ++k){
			pos = i*3+k;
			for(j = 0; j < N; ++j){
				subset[pos] |= ((lli)(cow[j][i]==k)<<j);
			}

			for(j = 0; j < 3; ++j){
				if(j == k) continue;
				other[pos] |= (1<<(i*3+j));
			}
		}
	}

	for(i = 0; i < (1<<17); ++i){
		bits[i] = __builtin_popcount(i);
	}
}

inline int popcount(lli mask){
	return bits[mask&((1<<17)-1)]+bits[(mask>>17)&((1<<17)-1)]+bits[mask>>34];
}


int min_ques(int sel, lli cows){
	int &val = mem[sel];
	if(val >= 0) return val;
	if(popcount(cows) < 2){
		val = 0;
		return val;
	}

	val = 25;

	int i,tmp;

	for(i = 0; i < V; ++i){
		if(!(sel&(1<<i))) continue;
		if(!(sel&other[i])) continue;				//property i is found

		tmp = min_ques(sel^(1<<i),cows&(~subset[i]));
		if(tmp >= val) continue;
		tmp = max(tmp,min_ques(sel&(~other[i]),cows&subset[i]));						//other two are not there
		val = min(val,tmp);
	}
	++val;

	return val;
}

int sol,asked;

int ask(int p, int v){
	++asked;
	return cow[sol][p] == v;
}

int main(int argc, char **argv){
	int sel,i,k,ques,tmp;
	char c;
	lli cows;

	assert(argc == 2);

	FILE *out = fopen(argv[1],"r");
	fscanf(out,"%d",&sol);
	--sol;

	scanf("%d%d",&N,&P);
	V = P*3;

	for(i = 0; i < N; ++i){
		for(k = 0; k < P; ++k){
			scanf(" %c",&c);
			cow[i][k] = c-'X';
		}
	}

	init();

	sel = (1<<V)-1;
	cows = (1LL<<N)-1;

	while(popcount(cows) >= 2){
		ques = 25;
		k = -1;
		for(i = 0; i < V; ++i){
			if(!(sel&(1<<i))) continue;
			if(!(sel&other[i])) continue;

			tmp = min_ques(sel^(1<<i),cows&(~subset[i]));
			if(tmp >= ques) continue;
			tmp = max(tmp,min_ques(sel&(~other[i]),cows&subset[i]));
			if(tmp >= ques) continue;
			ques = tmp;
			k = i;
		}
		assert(k >= 0);

		i = ask(k/3,k%3);

		if(i){
			sel &= ~other[k];
			cows &= subset[k];
		}else{
			sel ^= (1<<k);
			cows &= ~subset[k];
		}
	}

	for(i = 0; i < N; ++i){
		if(cows&(1LL<<i)){
			break;
		}
	}

	assert(i < N);

	if(sol^i){
		printf("WRONG\n");
	}
	else printf("CORRECT %d\n",asked);



	return 0;
}
