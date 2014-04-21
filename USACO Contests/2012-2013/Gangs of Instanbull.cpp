/*
 Created By: Malvika Joshi
 Problem: Gangs of Istanbull/Cowstantinople
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=211
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>

#define NMAX 110

using namespace std;

int gangs[NMAX];
int N,M;

int rem[NMAX];

int max_left(){
	int i,need,fst;

	fst = 0;

	for(i = 1; i < M; ++i){
		fst = max(fst,gangs[i]);
	}

	need = max(0,fst-(N-gangs[0]-fst));

	if((N-gangs[0]+need)%2) ++need;

	return max(0,gangs[0]-need);
}

int is_valid(int cmax, int csum){
	return cmax <= csum/2;
}

void print(int left){
	int i,sum,id,cmax,unmatched;

	sum = N-left;

	rem[0] -= left;

	for(id = 0; id < M; ++id){
		if(!rem[id]) continue;

		unmatched = 0;

		while(rem[id]--){
			printf("%d\n",id+1);
			++unmatched;
		}
		++rem[id];

		while(unmatched--){
			for(i = 0; i < M; ++i){
				if(!rem[i]) continue;

				cmax = max_element(rem,rem+N)-rem;
				assert(rem[cmax]);

				if(cmax != i && !is_valid(rem[cmax],sum-2)) continue;
				printf("%d\n",i+1);
				sum -= 2;

				--rem[i];
				break;
			}
		}

	}

	for(i = 0; i < left; ++i) printf("1\n");
}

int main(){
	int i,left;


	scanf("%d%d",&N,&M);

	for(i = 0; i < M; ++i){
		scanf("%d",&gangs[i]);
		rem[i] = gangs[i];
	}

	left = max_left();

	if(!left){
		printf("NO\n");
		return 0;
	}

	printf("YES\n%d\n",left);
	print(left);

	return 0;
}
