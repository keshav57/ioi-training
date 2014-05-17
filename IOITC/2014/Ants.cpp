#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cassert>

#define NMAX 52
#define SMAX 110
#define LOGT 32
#define INF (1e13)

using namespace std;
typedef long long lli;

lli mat[LOGT][NMAX][NMAX];
int N;

void exp(int p){
	int i,j,k;

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			//max cost path from i to j in at most 2p seconds
			mat[p+1][i][j] = mat[p][i][j];
			for(k = 0; k < N; ++k){
				//go through k
				mat[p+1][i][j] = max(mat[p+1][i][j],mat[p][i][k]+mat[p][k][j]);
			}
		}
	}
}

lli sol[NMAX][NMAX];
lli tmp[NMAX][NMAX];

lli T;

lli mul(){

	int p,i,j,k;

	for(p = LOGT; p>= 0; --p){
		if((1LL<<p) > T) continue;
		T -= 1LL<<p;
		memcpy(sol,mat[p],sizeof(lli)*NMAX*NMAX);
		break;
	}

	for(p--; p >= 0; --p){
		if((1LL<<p) > T) continue;
		T -= 1LL<<p;

		for(i =0 ; i < N; ++i){
			for(j = 0; j < N; ++j){
				tmp[i][j] = sol[i][j];
				for(k = 0; k < N; ++k){
					tmp[i][j] = max(tmp[i][j],sol[i][k]+mat[p][k][j]);
				}
			}
		}
		memcpy(sol,tmp,sizeof(lli)*NMAX*NMAX);
	}

	return sol[0][1];
}

lli sec[SMAX][NMAX][NMAX];
lli adj[NMAX][NMAX];
int S;

void init(){
	int i,j,s,k;

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			adj[i][j] = adj[i][j] == -999 ? -INF : adj[i][j];
			sec[0][i][j] = -INF;
		}
		sec[0][i][i] = 0;
	}


	for(s = 1; s <= S; ++s){
		for(i = 0; i < N; ++i){
			for(j = 0; j < N; ++j){
				sec[s][i][j] = -INF;
				for(k = 0; k < N; ++k){
					sec[s][i][j] = max(sec[s][i][j],adj[i][k]+sec[s-1][k][j]);
				}
			}
		}
	}

	memcpy(mat[0],sec[S],sizeof(lli)*NMAX*NMAX);
}

int main(){
	int i,j;

	scanf("%d%d%lld",&N,&S,&T);

	for(i =0 ; i < N; ++i){
		for(j = 0; j < N; ++j){
			scanf("%lld",&adj[i][j]);
		}
	}

	init();

	for(i = 0; (1LL<<i) < T; ++i){
		exp(i);
	}

	lli s = mul();

	if(s > -(1e10)){
		printf("%lld\n",mul());
	}

	else printf("IMPOSSIBLE\n");

	return 0;
}


