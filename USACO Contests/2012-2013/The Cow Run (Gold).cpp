/*
 Created By: Malvika Joshi
 Problem: The Cow Run (March-2013 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=265
*/

#include <cstdio>
#include <algorithm>

#define MAXN 1010

using namespace std;

int pos[MAXN];
int M[MAXN][MAXN];
int N;

int DP(int farm){

	int i,j,n;

	n = N;
	for(j = farm+1; j <= N; j++){
		M[farm][j] = M[farm][j-1] + n*(pos[j]-pos[j-1]);
		--n;
		M[j][farm] = M[farm][j] + n*pos[j];
	}

	n = N;
	for(i = farm-1; i >=0 ; i--){
		M[farm][i] = M[farm][i+1] + n*(pos[i+1]-pos[i]);
		--n;
		M[i][farm] = M[farm][i] + n*(-pos[i]);
	}


	for(i = farm-1; i >= 0; --i){
		for(j = farm+1; j <= N; ++j){
			n = N-(j-i-1);

			M[i][j] = min(M[i][j-1]+n*(pos[j]-pos[j-1]),M[j-1][i]+n*(pos[j]-pos[i]));
			M[j][i] = min(M[j][i+1]+n*(pos[i+1]-pos[i]),M[i+1][j]+n*(pos[j]-pos[i]));
		}
	}

	return min(M[0][N],M[N][0]);
}

int main(){

	int i;

	scanf("%d",&N);

	for(i = 1; i <= N; i++){
		scanf("%d",&pos[i]);
	}

	sort(pos,pos+N+1);
	i = lower_bound(pos,pos+N+1,0)-pos;

	printf("%d\n",DP(i));

	return 0;
}
