/*
 Created By: Malvika Joshi
 Problem: CHGLSTGT
 Link: http://www.codechef.com/problems/CHGLSTGT
*/

#include <stdio.h>
#include <string.h>

#define MAXN 5010

char cur_palin[MAXN];
char pre_palin[MAXN];
int palin_count[MAXN];
char str[MAXN];
int N;

inline int min(int a, int b){ return a < b ? a : b; }

int DP(){
	int i,j;

	memset(cur_palin,0,sizeof(char)*N);

	cur_palin[0] = 1;
	palin_count[0] = 1;

	for(i = 1; i < N; i++){
		cur_palin[i] = 1;
		palin_count[i] = palin_count[i-1]+1;
		memcpy(pre_palin,cur_palin,sizeof(char)*N);
		for(j = i-1; j >= 0; --j){
			cur_palin[j] = (pre_palin[j+1] && str[i] == str[j]);
			if(!cur_palin[j]) continue;
			palin_count[i] = j ? min(palin_count[i],palin_count[j-1]+1) : 1;
		}
	}

	return palin_count[N-1];
}

int main(){
	int t;
	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);
		scanf("%s",str);
		printf("%d\n",DP());
	}

	return 0;
}
