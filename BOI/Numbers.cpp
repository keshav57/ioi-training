/*
 Created By: Malvika Joshi
 Problem: Palindrome-Free Numbers (BOI-2013)
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

long long mem[2][2][21][110];
char start[21],end[21];

int N;

long long pos(int b1,int b2, int digits, int last){
	if(digits >= N){
		return 1;
	}

	long long &res = mem[b1][b2][digits][last];
	if(res >= 0) return res;


	res = 0;
	int i,sd,ed,t1,t2;

	sd = b1 ? start[digits] : 0;
	ed = b2 ? end[digits] : 9;

	for(i = sd; i <= ed; ++i){
		if(i == last%10 || i == last/10) continue;
		t1 = (b1 && i == sd);
		t2 = (b2 && i == ed);
		res += pos(t1,t2,digits+1,(last%10)*10+i);
	}

	return res;
}

int main(){

	int i,st,en,n,m,b1,b2;
	long long sol;

	scanf("%s %s",start,end);

	n = strlen(start);
	m = strlen(end);

	for(i = 0; i < n; ++i) start[i] -= '0';
	for(i = 0; i < m; ++i) end[i] -= '0';

	sol = 0;
	if(n < 2 && m < 2) sol += end[0]-start[0]+1;
	else if(n < 2) sol += 10-start[0];

	for(N = max(2,n); N <= m; ++N){
		memset(mem,-1,sizeof(long long)*2*2*21*110);
		b1 = N == n;
		b2 = N == m;
		st = b1 ? start[0]*10+start[1] : 10;
		en = b2 ? end[0]*10+end[1] : 99;

		for(i = st; i <= en; ++i){
			if(i%10 == i/10) continue;
			sol += pos(b1 && i==st ,b2 && i==en,2,i);
		}
	}

	printf("%lld\n",sol);

	return 0;
}
