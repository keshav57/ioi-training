/*
 Created By: Malvika Joshi
 Problem: Escaping the Farm (December-2011 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=96
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 21
#define EXP_N (1<<20)
#define MAX_W 11

char weight[MAX_N][MAX_W];
char carry[EXP_N+10];
char sum[EXP_N+10][MAX_W];
int len[EXP_N+10];
int N;

inline int max(int a, int b){ return a > b ? a :b; }

int stlen(char *arr){
	int i = 0;
	while(arr[i] != '#') ++i;
	return i;
}

int max_grp(){
	int set,i,tset,j,k,mlen,n,b;
	mlen = 0;
	sum[0][0] = '#';
	for(set = 1; set < 1<<N; ++set){
		for(i = 0; i < N; i++){
			if(set & (1<<i)){
				tset = set-(1<<i);
				if(carry[tset]){
					carry[set] = 1;
					break;
				}
				j = stlen(weight[i]);
				k = stlen(sum[tset]);
				n = max(j,k);
				sum[set][n] = '#';
				b = 0;
				for(--j,--k,--n;j >= 0 && k >= 0; --j,--k,--n){
					sum[set][n] = sum[tset][k] + weight[i][j];
					if(sum[set][n] >= 10){
						carry[set] = 1;
						b = 1;
					}
				}

				if(b) 	break;

				for(; j >=0; --j,--n)	sum[set][n] = weight[i][j];

				for(; k >= 0; --k,--n)	sum[set][n] = sum[tset][k];
				n = 0;
				for(j = 0; j < N; j++) n += (set&(1<<j)) ? 1 : 0;
				mlen = max(mlen,n);

				break;
			}
		}
	}

	return mlen;
}

int main(){
	int i,j,n;
	scanf("%d",&N);

	for(i = 0; i < N; i++){
		scanf("%s",weight[i]);
		n = strlen(weight[i]);
		for(j = 0; j < n; ++j){
			weight[i][j] -= '0';
		}
		weight[i][j] = '#';
	}


	printf("%d\n",max_grp());
	return 0;
}
