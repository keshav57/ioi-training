/*
 Created By: Malvika Joshi
 Problem: Cows in a Skyscraper (March-2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=129
*/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <iostream>

#define NMAX 18
#define SMAX (1<<18)

//To print one valid ordering\
#define PRINT_SOL

using namespace std;

int valid[SMAX+10];
int min_rides[SMAX+10];
int prev[SMAX+10];

int test[SMAX+10];
int T;

int weight[NMAX+2];
int N,W,cur;


//n = (n - d) & d;


int dp(){
	int sel,i,n,last,tmp;

	for(sel = 1; sel < (1<<N); ++sel){

		if(valid[sel]){
			prev[sel]  = sel;
			min_rides[sel] = 1;
			continue;
		}

		n = __builtin_popcount(sel);
		min_rides[sel] = N;
		prev[sel] = sel&-sel;

		if((1<<(n-1)) < T){
			last = sel&-sel;
			tmp = sel^last;
			i = 0;

			do{
				if(valid[(i|last)] && min_rides[tmp^i]+1 < min_rides[sel]){
					min_rides[sel] = min_rides[tmp^i]+1;
					prev[sel] = (i+last);
				}
				i = (i-tmp)&tmp;
			}while(i);

			continue;
		}


		i = T-1;
		while(i--){
			n = test[i]&sel;
			if(min_rides[sel^n]+1 >= min_rides[sel]) continue;
			min_rides[sel] = min_rides[sel^n]+1;
			prev[sel] = n;
		}
	}

	return min_rides[(1<<N)-1];
}


int main(){
	int i,sum,sel;

	scanf("%d%d",&N,&W);

	for(i =0 ; i < N; ++i){
		scanf("%d",&weight[i]);
	}


	for(sel = (1<<N)-1; sel >= 0; --sel){
		sum  = 0;
		for(i = 0; i < N; ++i){
			if(!(sel&(1<<i))) continue;
			sum += weight[i];
			if(sum > W) break;
		}
		if(i < N) continue;
		valid[sel] = 1;

		for(i = 0; i < N; ++i){
			if(sel&(1<<i)) continue;
			if(valid[sel|(1<<i)]) break;
		}

		if(i < N) continue;
		test[T++] = sel;
	}

	printf("%d\n",dp());

	cur = (1<<N)-1;


#ifdef PRINT_SOL
	while(cur){
		printf("%d",__builtin_popcount(prev[cur]));
		for(i = 0; i < N; ++i){
			if(!(prev[cur]&(1<<i))) continue;
			printf(" %d",i+1);
		}
		printf("\n");
		cur ^= prev[cur];
	}
#endif

	return 0;
}
