#include <algorithm>
#include <cassert>
#include <cstring>
#include <set>
#include <iostream>
#include <cstdio>
#include <queue>

#define NMAX 1000010
#define TMAX 50000

using namespace std;

int N;
int wt[NMAX];
int sz[NMAX];

int wtorder[NMAX];
int szorder[NMAX];

int rem[NMAX];

int wtcap[TMAX];
int szcap[TMAX];

int A,B;

priority_queue<pair<int,int> > Q;

int verify(int M){
	int i,k,j,toy;

	for(i = 0; i< N; ++i) rem[i] = 0;

	while(!Q.empty())Q.pop();

	k = 0;
	for(i = 0; i < A; ++i){
		while(k < N && wt[wtorder[k]] < wtcap[i]){
			Q.push(make_pair(sz[wtorder[k]],wtorder[k]));
			++k;
		}

		for(j = 0; j < M && !Q.empty(); ++j){
			toy = Q.top().second;
			rem[toy] = 1;
			Q.pop();
		}
	}

	k = 0;
	for(i = 0; i < B; ++i){
		j = 0;
		while(j < M && k < N && sz[szorder[k]] < szcap[i]){
			if(rem[szorder[k]]){
				++k;
				continue;
			}
			rem[szorder[k]] = 1;
			++k;
			++j;
		}
	}


	for(k =0; k < N; ++k) if(!rem[k]) break;

	//verifies if it is possible to do it in M minutes

	return k >= N;
}



int search(){
	int low,high,mid;

	low = 0;
	high = N+1;

	while(low < high){
		mid = (low+(high-low)/2);
		if(verify(mid)){
			high = mid;
		}else{
			low = mid+1;
		}
	}

	return low <= N ? low : -1;
}

int compwt(int a, int b){
	return wt[a] < wt[b];
}

int compsz(int a, int b){
	return sz[a] < sz[b];
}

int main(){
	int i;
	scanf("%d%d%d",&A,&B,&N);

	for(i = 0; i < A; ++i){
		scanf("%d",&wtcap[i]);
	}

	sort(wtcap,wtcap+A);

	for(i = 0; i < B; ++i){
		scanf("%d",&szcap[i]);
	}

	sort(szcap,szcap+B);

	for(i = 0; i< N; ++i){
		scanf("%d%d",&wt[i],&sz[i]);
		wtorder[i] =i;
		szorder[i] =i;
	}

	sort(wtorder,wtorder+N,compwt);
	sort(szorder,szorder+N,compsz);

	printf("%d\n",search());


	return 0;
}
