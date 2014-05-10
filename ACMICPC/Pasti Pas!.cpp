/*
 Problem: Pasti Pas! (Regionals 2013: Asia-Jakarta)
 Link: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=596&page=show_problem&problem=4450
*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

#define NMAX 50010
#define LOGN 17

using namespace std;
typedef pair<pair<int,int>, int> suffix;

suffix order[NMAX];
int P[LOGN][NMAX];
int N,log;

char str[NMAX];
int suffix_array[NMAX];

suffix tmp[NMAX];
int ct[NMAX];

void radix_sort(){
	int i;

	memset(ct,0,sizeof(int)*NMAX);

	for(i = 0; i < N; ++i) ++ct[order[i].first.second+1];
	for(i = 0; i <= N || i <= 26; ++i)	ct[i] += i ? ct[i-1] : 0;

	for(i = N-1; i >= 0; --i) tmp[--ct[order[i].first.second+1]] = order[i];

	memset(ct,0,sizeof(int)*NMAX);
	for(i = 0; i < N; ++i) ++ct[tmp[i].first.first+1];
	for(i = 0; i <= N || i <= 26; ++i)	ct[i] += i ? ct[i-1] : 0;

	for(i = N-1; i >= 0; --i) order[--ct[tmp[i].first.first+1]] = tmp[i];

}


int init(){
	int i,n;

	for(i = 0; i < N; ++i){
		P[0][i] = str[i]-'A';
	}

	for(n = 1; n < 2 || (1<<(n-1)) < N; ++n){

		for(i =0; i < N; ++i){
			order[i].first.first = P[n-1][i];
			order[i].first.second = i+(1<<(n-1)) < N ? P[n-1][i+(1<<(n-1))] : -1;
			order[i].second = i;
		}

		radix_sort();

		for(i = 0; i < N; ++i){
			P[n][order[i].second] = (i && order[i].first == order[i-1].first) ? P[n][order[i-1].second] : i;
		}
	}

	for(i = 0; i < N; ++i){
		suffix_array[P[n-1][i]] = i;
	}

	return n;
}

int lcp(int i, int j){
	int k,pref;

	pref = 0;

	if(i == j) return N-i;

	for(k = log-1; k >= 0 && i < N && j < N; --k){
		if(P[k][i] != P[k][j]) continue;
		i += (1<<k);
		j += (1<<k);
		pref += (1<<k);
	}

	return pref;
}

int compute_length(){
	int st,en,k,len,b,cuts;
	log =init();

//	for(k = 0; k < N; ++k){
//		printf("%s\n",str+suffix_array[k]);
//	}

	st = 0;
	en = N-1;

	cuts = 0;

	while(st < en){

		k = en;
		b = 0;
		while((st+en)/2 < k){
			len = lcp(k,st);
//			cout << k << " " << st << " " << len << endl;
			if(len >= en-k+1){
				b = 1;
				break;
			}
			--k;
		}

		if(!b) break;

//		cout << k << endl;

		cuts += 2;
		st += (en-k+1);
		en = k-1;
	}

	cuts += (st <= en);

	return cuts;
}

int T;

int main(){
	int t;

	scanf("%d",&T);

	for(t = 1; t <= T; ++t){
		scanf("%s",str);
		N = strlen(str);

		printf("Case #%d: %d\n",t,compute_length());
	}

	return 0;
}
