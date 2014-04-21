/*
 Created By: Malvika Joshi
 Problem: Kindergarten (IOITC-2013 Final 2)
 
 When we remove one child from the circle, the number of gaps are not affected and the circle transforms into a line. So,
 instead we can solve the problem where we want to seat N-1 people on a line and the number of 'groups' at any point is
 not more than K. If we are already given an arrangement of which seats are taken, we can find the number of ways to obtain it by
 deciding in which of the taken seats does the current child sit and find the number of ways to obtain the arrangement before he sat.
 So we just need to find how many ways are there obtain the arrangement where all N-1 seats are taken and multiply it by N, the number
 of ways to seat the Nth child.
 This works only for the first two subtaks (40%) where N <= 18, because it takes O(2^N*N) time, for the first subtask (10%) we can simply
 try all permutations and count the ones which are valid.
 */

#include <stdio.h>
#include <assert.h>

#define MAXS (1<<18)
#define MAXN 18
#define MOD ((int)1e9+7)

int F[MAXS+10];	// F[S] is the number of ways to obtain the arrangement described by the bits in S
int N,K;	// K is the number of toys, N is the number of seats

int DP(){

	int i,k;
	int S,X;

	// N is one less than the actual number of seats.

	F[0] = 1;	//All seats are empty
	for(S = 1; S < (1<<N); S++){
		// 0 indicates an empty seat, 1 indicates an already taken seat.
		F[S] = 0;

		// k is the number of toys in the current arrangement
		k = S&1;	// Check if anyone is sitting on the first seat, if yes then they need a new toy.

		for(i = 1; i < N; i++){
			if((S&(1<<i)) && !(S&(1<<(i-1))))	++k;	// If the current seat is taken and the previous one is not, we need a new toy.
		}

		if(k > K) continue;		// We can't have more than K toys.

		for(i = 0; i < N; i++){
			if(S&(1<<i)){
				X = S-(1<<i);	// For every taken seat, we assign it to the current child.
				F[S] += F[X];	// X is the arrangement before the child sat.
				F[S] %= MOD;
			}
		}

	}

	return F[(1<<N)-1]; //(1<<N)-1 is the arrangement when all seats are taken.
}

int main(){

	long long sol;

	scanf("%d%d",&N,&K);
	assert(N <= MAXN);	// This works only for the first two subtasks.

	--N;	// We count the number of ways to seat N-1 children on a line.

	sol = (long long)DP();
	sol *= (N+1); // The last child can go into any of the N+1 seats. As we multiplied by N+1, we need long long.
	sol %= MOD;

	printf("%lld",sol);
	return 0;
}
