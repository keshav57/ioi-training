/*
 Created By: Malvika Joshi
 Problem: The Jester (IOITC-2013 Final 1)

 We use the same recurrence we used for the previous subtasks. But we are recomputing a lot of stuff:
 f[i][j] = 1 + ( f[i-k][j-1] * (k+1) for all k < i)
 f[i-1][j] = 1 + ( f[i-k][j-1] * (k) for all k < i-1 )
 So we can instead write it as:
 f[i][j] = f[i-1][j] + ( f[i-k][j-1] for all k < i ). So if we call the quantity ( f[i-k][j-1] for all k < i ), g[i][j-1], then
 g[i][j] = f[i][j] + g[i-1][j] and f[i][j] = f[i-1][j] + g[i][j-1].
 This will still work only for the first two subtasks because for N = 5000, it will require 200mb space and the limit is 128mb.
 We cannot discard the table f, we need it to answer the queries, but we don't need the complete table g, only the last row. So
 we can store just two rows of g. Actually we can manage everything in just one row, g[j] will actually be g[i-1][j] before we update it,
 so we just need to add f[i][j] to g[j] for the next iteration.
 Time taken is O(N^2) and space used is just about 100mb.
*/

#include <stdio.h>

#define MAXN 5000
#define MAXM 5000
#define MOD ((int)1e9+7)

typedef long long lli;

int F[MAXN+10][MAXM+10];	// For answering queries
int G[MAXM+10];		// We don't need the complete table

void init(){
	int i,j;

	for(j = 0; j <= MAXM; ++j)	F[0][j] = 1;
	//	G everything will be 0, because g[i][j] = ( f[i-k][j] for all k < i ), which won't run when i equals 0.

	for(i = 1; i <= MAXN; ++i)	F[i][0] = 0;
	// Even here G everything will be 0, because g[0][0] = 0.

	for(i = 1; i <= MAXN; ++i){
		for(j = 1; j <= MAXM; ++j){
			F[i][j] = F[i-1][j] + G[j-1];
			F[i][j] %= MOD;
			// Maximum F[i][j] can ever be is 2000000014, so we don't need long long, only need to take modulus at every step.
			G[j] += F[i][j];
			G[j] %= MOD;
		}
	}
}

int main(){
	int Q,N,M;

	init();
	scanf("%d",&Q);

	while(Q--){
		scanf("%d%d",&M,&N);
		printf("%d\n",F[N][M]);
	}

	return 0;
}
