#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <set>

#define NMAX 20010
#define MMAX 52

int A[NMAX];
int occ[NMAX];
int N,T,W;



using namespace std;

pair<int,int> m[NMAX];
int M;

int main(int argc, char ** arg){
	int i,ct,moves,n,s,e,k;

	assert(argc == 3);

	FILE *in1 = fopen(arg[1],"r");
	FILE *sol = fopen(arg[2],"r");


	fscanf(in1,"%d%d%d",&N,&T,&W);
	assert(N <= NMAX);
	assert(T <= MMAX);
	assert(W <= NMAX && W > 1);
	for(i = 0; i < N; ++i){
		fscanf(in1,"%d",&A[i]);
		assert(A[i] <= T);
	}

	set<int> dist;
	fscanf(sol,"%d",&moves);

	for(i = 0; i < moves; ++i){
		fscanf(sol,"%d",&n);
		if(n > W){
			cout << "Wrong" << endl;
			return 0;
		}

		dist.clear();
		k = n;
		M = 0;
		while(n--){
			fscanf(sol,"%d%d",&s,&e);
			m[M++] = make_pair(e-1,A[s-1]);
			dist.insert(s);
			dist.insert(e);
		}

		while(M--){
			A[m[M].first] = m[M].second;
		}

		if(dist.size() != k){
			cout << "Wrong2" << endl;
			return 0;
		}
	}

	for(i = 0; i < N; ++i){
		printf("%d\n",A[i]);
	}
	cout << endl;

	for(i = 1; i < N; ++i){
		if(A[i] < A[i-1]){
			printf("%d %d\n",A[i],A[i-1]);
			cout << "Wrong1" << endl;
			return 0;
		}
	}

	cout << "Correct" << endl;
	cout << ceil(N/(double)(W-1)) << " " << moves << endl;;

	return 0;
}
