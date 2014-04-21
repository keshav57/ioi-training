/*
 Created By: Malvika Joshi
 Problem: SMS (IOITC-2012 Test 5)
*/

#include <stdio.h>
#include <string.h>

#define MOD 100000007

int lookup[26][2] = {{2,1},{2,2},{2,3},{3,1},{3,2},{3,3},{4,1},{4,2},{4,3},{5,1},{5,2},{5,3},
		{6,1},{6,2},{6,3},{7,1},{7,2},{7,3},{7,4},{8,1},{8,2},{8,3},{9,1},{9,2},{9,3},{9,4}};

int f[400010];
int code[400010];
int M;

int DP(int N){
	int i;
	f[0] = 0;
	f[1] = 1;
	f[2] = 2;

	for(i = 3 ;i <= N; i++){
		f[i] = 1 + f[i-1] + f[i-2] + f[i-3];
		f[i] %= MOD;
	}

	return f[N];
}


int DP2(int N){
	int i;
	f[0] = 0;
	f[1] = 1;
	f[2] = 2;
	f[3] = 4;

	for(i = 4 ;i <= N; i++){
		f[i] = 1 + f[i-1] + f[i-2] + f[i-3] + f[i-4];
		f[i] %= MOD;
	}

	return f[N];
}

int main(){
	char str[100010];
	int n,k,i,j,c;

	long long sol;
	scanf("%d",&M);
	for(i = 0; i < M; i++){
		scanf("%s",str);
		n = strlen(str);
		k = 0;
		for(j = 0;j < n; j++){
			for(c= 0; c < lookup[str[j]-'a'][1] ; c++){
				code[k++] = lookup[str[j]-'a'][0];
			}
		}

		c = 1;
		sol = 1;
		for(j = 1; j < k; j++){
			if(code[j] == code[j-1]){
				c++;
			}else{
				if(code[j-1] == 7 || code[j-1] == 9) sol *= DP2(c);
				else sol*=DP(c);
				sol %= MOD;
				c = 1;
			}
		}

		if(code[j-1] == 7 || code[j-1] == 9) sol *= DP2(c);
		else sol*=DP(c);
		sol %= MOD;
		printf("%lld\n",sol);
		memset(str,'\0',sizeof(char)*100010);
	}

	return 0;
}
