#include <algorithm>
#include <iostream>
#include <cstdio>

#define NMAX 5010

using namespace std;

int dp[NMAX][NMAX];
int N;

char str[NMAX];

int compute(){
	int i,j,n;

	for(n = 2; n <= N; ++n){
		for(i = 0; i+n <= N; ++i){
			j = i+n-1;

			dp[i][j] = str[i]^str[j] ? 2+dp[i+1][j-1] : dp[i+1][j-1];
			dp[i][j] = min(dp[i][j],min(dp[i+1][j],dp[i][j-1])+1);
		}
	}

	return dp[0][N-1];
}

int main(){


	scanf("%d",&N);
	scanf("%s",str);

	printf("%d\n",compute());

	return 0;
}
