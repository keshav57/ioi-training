#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 1000010
#define INC 1000000

using namespace std;

int order[NMAX];
int rev[NMAX];

int N;

int P[NMAX];

int pref[NMAX+NMAX];

void sort(int *A){
	int i;

	memset(pref,0,sizeof(pref));

	for(i = 0; i < N; ++i){
		++pref[A[i]+INC];
	}

	for(i = 1; i <= INC+INC; ++i){
		pref[i] += pref[i-1];
	}

	for(i = 0; i < N; ++i){
		P[--pref[A[i]+INC]] = A[i];
	}
}


int get_sol(){
	int i,d,sol;

	sol = 0;
	P[N] = P[0]+N;
	for(i = 0; i < N; ++i){
		d = P[i+1]-P[i];
		sol = max(sol,d);
	}

	return (N-sol+1)/2;
}


int main(){
	int i,sol,q1,q2;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d",&order[i]);
		--order[i];
		rev[N-i-1] = order[i];
 	}

	for(i = 0; i < N; ++i){

		q1 = i-order[i];
		q2 = q1 >= 0 ? q1-N : N+q1;

		order[i] =  abs(q1) < abs(q2) ? q1 : q2;
//		cout << order[i] << " ";

		q1 = i-rev[i];
		q2 = q1 >= 0 ? q1-N : N+q1;

		rev[i] = abs(q1) < abs(q2) ? q1 : q2;
	}


	sol = N;
	sort(order);
	sol = min(sol,get_sol());
	sort(rev);
	sol = min(sol,get_sol());

	printf("%d\n",sol);

	return 0;
}
