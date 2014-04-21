/*
 Created By: Malvika Joshi
 Problem: The Jester (IOITC-2013 Final 1)

 Once the array starts increasing, it cannot decrease again, because either ends of any subsection have to be the maximum
 elements in that range, so once the array starts increasing the left endpoint will not be the maximum, so the right endpoint has to be
 the maximum, i.e it has to be greater than or equal to the current rightmost element, thus the array will continue to be non-decreasing.
 So the array can either be non-decreasing, or non-increasing, or non-increasing and then non-decreasing. If the maximum element in the array
 is M, There will be atmost two subsections with all the elements equal to M, one will start at the beginning and one will end at the end
 of the array. So if the first 'a' elements are equal to M and the first 'b' elements are equal to M then removing them we get an array of size
 N-a-b where all the elements are less than or equal to M-1. Instead of trying for all possible values for a and b, we can try it for all
 possible values for k, where k = a+b, and then multiply it by the number of ways to divide k into a and b, which is k+1. We will have to
 consider the special case where k = N separately, because we cannot find a and b as described above.

 This will take O(N^3) time and will work only for the first two subtasks (40%), (for the first subtask (10%) we try all possibilities
 of a and b so it takes O(N^4) time).
*/

#include <stdio.h>
#include <assert.h>

#define MAXN 200
#define MAXM 200
#define MOD ((long long)1e9+7)

typedef long long lli;

int F[MAXN+10][MAXM+10];	//We precompute the number of possible arrays for all the values of N and M in F.

void init(){
	int i,j,k;
	lli temp,f;

	for(i = 1; i <= MAXN; ++i)	F[i][0] = 0;
	for(j = 0; j <= MAXM; ++j)  F[0][j] = 1;

	for(i = 1; i <= MAXN; ++i){		// i is the size of the array
		for(j = 1; j <= MAXM; ++j){		//j is the limit on the elements in the array
			temp = 1;				//The case where all elements in the array are equal to j
			for(k = 0; k < i; ++k){		//k is the number of elements which have value j
				f = (lli)F[i-k][j-1];
				temp += (f * (k+1)) % MOD;		//We can assign k elements to the two end of the array in k+1 ways.
				temp %= MOD;
			}
			F[i][j] = (int)temp;		//This is done to prevent overflow and so we don't need to have F as an array of long long.
		}
	}
}

int main(){
	int Q,N,M;

	init();
	scanf("%d",&Q);

	while(Q--){
		scanf("%d%d",&M,&N);
		assert(M <= MAXM && N <= MAXN);	//This algorithm takes O(N^3) time so will only work for the first two subtasks.
		printf("%d\n",F[N][M]);
	}

	return 0;
}
