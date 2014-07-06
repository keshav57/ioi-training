#include <algorithm>
#include <iostream>
#include <cassert>
#include <queue>
#include <cstring>
#include <cstdio>

#define NMAX 5010

using namespace std;

queue<pair<int,int> >Q;
int stand[NMAX*2];
int N,R,rank;

int order[NMAX*2];
int M;

int ct[3];

int rotate(int pos){
	int i,r,f1,f2;

	memset(ct,0,sizeof(ct));
	M = 0;

	while(!Q.empty())Q.pop();

	for(i = 0; i < 2*N; ++i){
		if(i == pos) order[M++] = 0;
		if(i < 2*N-1) order[M++] = stand[i] < rank ? -1 : 1;
	}

	for(i = 2; i < 2*N; ++i){
		Q.push(make_pair(i/2,order[i]));
	}

	f1 = order[0];
	f2 = order[1];
	if(f2 < f1) swap(f2,f1);
	Q.push(make_pair(N,f2));

	r = 0;
	while(r < 3*N){
		++r;
		while(Q.front().first <= r){
			++ct[Q.front().second+1];
			if(!Q.front().second){
				if(Q.front().first >= 2*N-1) return Q.front().first-2*N-1;
			}
			Q.pop();
		}

		for(i =0; i < 3; ++i) if(ct[i]) break;
		assert(i < 3);
		--ct[i];
		f2 = i-1;
		if(f2 < f1) swap(f2,f1);
		Q.push(make_pair(N+r,f2));
	}

	assert(0);
	return -1;
}



int fixed(int pos){
	int i,r,k;

	memset(ct,0,sizeof(ct));

	M = 0;

	for(i = 0; i < 2*N; ++i){
		if(i == pos) order[M++] = 0;
		if(i < 2*N-1) order[M++] = stand[i] < rank ? -1 : 1;
	}

	for(r = 0,i = 0; r < 2*N; ++r, --i){
		++ct[order[i*2]+1];
		++ct[order[i*2+1]+1];


		if(!i){

			for(k = 0; k < 3; ++k) if(ct[k]) break;


			order[i*2] = k-1;
			order[i*2+1] = -1;
			--ct[k];
			i = N;
			continue;
		}

		for(k = 2; k >= 0; --k){
			if(ct[k]) break;
		}
		assert(k >= 0);


		order[i*2] = k-1;
		order[i*2+1] = -1;
		--ct[k];
	}


	for(i = 0; i < N; ++i){
		if(order[i*2] && order[i*2+1]) continue;
		break;
	}

	return i;
}

int main(){
	int i;


	scanf("%d%d",&N,&R);
	--R;

	if(N > NMAX) exit(1);
	scanf("%d",&rank);
	if(rank == 1){
		printf("%d\n",N);
		return 0;
	}
	--rank;
	for(i = 0; i < 2*N-1; ++i){
		scanf("%d",&stand[i]);
		--stand[i];
	}

	int st,k,en;

	if(rank > N){
		st = -1;
		en = (1e9);
		for(i = 0; i < N; ++i){
			k = fixed(i*2);
			if(k < en) en = k, st = i;
			if(k == en) st = max(st,i);
		}

		printf("%d\n",st+1);
		return 0;
	}

	st = -1;
	en = (1e9);
	for(i =0; i < N; ++i){
		k = rotate(i*2);
		k = (N+k-(R%N))%N;
		if(k < en) en = k, st = i;
		if(k == en) st = max(st,i);
	}

	printf("%d\n",st+1);

	return 0;
}

