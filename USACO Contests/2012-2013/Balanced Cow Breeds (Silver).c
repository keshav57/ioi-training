/*
 Created By: Malvika Joshi
 Problem: Balanced Cow Breeds (November-2012 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=193
*/

#include <stdio.h>
#include <string.h>

char Str[1000];
int DP[1000][501];
int N,U;


int main(){
	int i,j,temp;
	scanf("%s",Str);

	N = strlen(Str);

	U = 1;
	DP[N-1][0] = 1;
	DP[N-1][1] = 1;

	for(i = N-2;i >= 0;i --){
		if(Str[i] == ')'){
			U++;
			for(j = 0;j <= U; j++){
				temp = DP[i+1][j];
				if(j > 0) temp += DP[i+1][j-1];
				DP[i][j] = temp % 2012;
			}
		}else {
			U--;
			for(j = 0;j <= U; j++){
				temp = DP[i+1][j] + DP[i+1][j+1];
				DP[i][j] = temp % 2012;
			}
		}
	}

	printf("%d",DP[0][0]);

	return 0;
}
