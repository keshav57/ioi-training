#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <cstdio>

#define NMAX 1100010
#define INC 1100000

using namespace std;

vector<int> diff[2*NMAX];

int sm[NMAX];
int stack[NMAX];
int S;

pair<int,int> sol[NMAX];
int P,N;

int A[NMAX];

void init(){
	int i;

	S = 0;
	for(i = N-1; i >= 0; --i){
		while(S && A[stack[S-1]] > A[i]){
			--S;
		}
		sm[i] = S ? stack[S-1] : N;
		stack[S++] = i;
	}

}

int compute(){
	int i,sig;

	S = 0;

	for(i = N-1; i >= 0; --i){
		while(S && A[stack[S-1]] < A[i]){
			--S;
			sig = A[stack[S]]-stack[S]+INC;
			assert(!diff[sig].empty());
			diff[sig].pop_back();
		}

		sig = A[i]-i+INC;
		if(diff[sig].empty() || diff[sig].back() >= sm[i]){
			stack[S++] = i;
			diff[sig].push_back(i);
			continue;
		}

		sol[P++] = make_pair(i,diff[sig].back());
		while(S){
			--S;
			sig = A[stack[S]]-stack[S]+INC;
			assert(!diff[sig].empty());
			diff[sig].pop_back();
		}

		sig = A[i]-i+INC;
		stack[S++] = i;
		diff[sig].push_back(i);
	}

	return P;
}

int main(){
	int i;
	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d",&A[i]);
	}

	init();

	printf("%d\n",compute());

	while(P--){
		printf("%d %d\n",sol[P].first+1,sol[P].second+1);
	}
	return 0;
}

