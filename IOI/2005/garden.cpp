#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>

#define NMAX 3000

using namespace std;


int up[NMAX];
int below[NMAX];
int left1[NMAX];
int right1[NMAX];

int roses[NMAX][NMAX];

int sum[NMAX];
int pref[NMAX];

int N,M,K;

void init(){
	int i,j,k,p,s;

	for(i = 0; i <= max(N,M); ++i){
		up[i] = below[i] = left1[i] = right1[i] = (1e8);
	}


	for(i = 0; i < M; ++i){
		for(k = 0; k < N; ++k) sum[k] = 0;

		for(j = i; j >= 0 ; --j){
			p = 0;
			s = 0;
			for(k = 0; k < N; ++k){
				sum[k] += roses[j][k];
			}

			for(k = 0; k < N; ++k){
				s += sum[k];
				while(s >= K && p <= k){
					s -= sum[p];
					++p;
				}

				if(p){
					--p;
					s += sum[p];
				}

				if(s == K){
					up[i] = min(up[i],2*(i-j+1)+2*(k-p+1));
				}
			}
		}

		for(k = 0; k < N; ++k) sum[k] = 0;
		for(j = i; j < M; ++j){
			p = 0;
			s = 0;

			for(k = 0; k < N; ++k){
				sum[k] += roses[j][k];
			}

			for(k = 0; k < N; ++k){
				s += sum[k];
				while(s >= K && p <= k){
					s -= sum[p];
					++p;
				}

				if(p){
					--p;
					s += sum[p];
				}

				if(s == K){
					below[i] = min(below[i],2*(j-i+1)+2*(k-p+1));
				}
			}
		}
	}
}

void init2(){
	int i,j,k,p,s;

	init();

	for(i = 0; i < N; ++i){
		for(k = 0; k < M; ++k) sum[k] = 0;

		for(j = i; j >= 0 ; --j){
			p = 0;
			s = 0;

			for(k = 0; k < M; ++k){
				sum[k] += roses[k][j];
			}

			for(k = 0; k < M; ++k){
				s += sum[k];
				while(s >= K && p <= k){
					s -= sum[p];
					++p;
				}

				if(p){
					--p;
					s += sum[p];
				}

				if(s == K){
					left1[i] = min(left1[i],2*(i-j+1)+2*(k-p+1));
				}
			}
		}

		for(k = 0; k < M; ++k) sum[k] = 0;
		for(j = i; j < N; ++j){
			p = 0;
			s = 0;

			for(k = 0; k < N; ++k){
				sum[k] += roses[k][j];
			}

			for(k = 0; k < M; ++k){
				s += sum[k];

				while(s >= K && p <= k){
					s -= sum[p];
					++p;
				}

				if(p){
					--p;
					s += sum[p];
				}

				if(s == K){
					right1[i] = min(right1[i],2*(j-i+1)+2*(k-p+1));
				}
			}
		}
	}
}

int R;

int main(){
	int i,j;

	scanf("%d%d%d%d",&M,&N,&R,&K);

	while(R--){
		scanf("%d%d",&i,&j);
		--i,--j;
		++roses[i][j];
	}

	init2();

	int minp = 1e9;

	for(i = 0; i < N; ++i){
		for(j = i+1; j < N; ++j){
			minp = min(minp,left1[i]+right1[j]);
		}
	}

	for(i = 0; i < M; ++i){
		for(j = i+1; j < M; ++j){
			minp = min(minp,up[i]+below[j]);
		}
	}

	if(minp >= (1e9)){
		printf("NO\n");
		return 0;
	}

	printf("%d\n",minp);

	return 0;
}
