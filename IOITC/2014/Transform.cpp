#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

#define NMAX 510

using namespace std;

int N,M;

vector<pair<pair<int,int>,int> > buf;

void print(int i, int j, int d){
	int k;

	for(k = 30; k >= 0; --k){
		if(!(d&(1<<k))) continue;
		buf.push_back(make_pair(make_pair(i,j),k));
		++M;
	}
}

int clear(int a, int b, int i, int j){

	assert((a < 0) != (b < 0));

	int aval,bval,d;

	while(a % b){
		aval = abs(a);
		bval = abs(b);

		if(aval < bval){
			d = bval/aval;
			bval %= aval;
			if(!bval) bval = aval, --d;
			print(j,i,d);
		}else{
			d = aval/bval;
			aval %= bval;
			print(i,j,d);
		}

		a = a < 0 ? -aval : aval;
		b = b < 0 ? -bval : bval;
	}

	print(i,j,abs(a)/abs(b));

	return b;
}

int neg[NMAX];
int pos[NMAX];
int A[NMAX];

int main(){
	int i,n,p,z;

	n = p = z = 0;
	scanf("%d",&N);
	for(i = 0; i < N; ++i){
		scanf("%d",&A[i]);

		if(A[i] > 0){
			pos[p++] = i;
		}else if(A[i] < 0){
			neg[n++] = i;
		}else{
			++z;
		}
	}

	if(z == N-1){
		printf("1\n0\n");
		return 0;
	}
	if(!n || !p){
		printf("0\n");
		return 0;
	}

	printf("1\n");

	while(n && p){
		if(n > p){
			A[pos[p-1]] = clear(A[neg[n-1]],A[pos[p-1]],neg[n-1]+1,pos[p-1]+1);
			A[neg[--n]] = 0;
		}else{
			A[neg[n-1]] = clear(A[pos[p-1]],A[neg[n-1]],pos[p-1]+1,neg[n-1]+1);
			A[pos[--p]] = 0;
		}
	}

	printf("%d\n",M);

	for(i =0 ; i < M; ++i){
		printf("%d %d %d\n",buf[i].first.first,buf[i].first.second,buf[i].second);
	}

	return 0;
}
