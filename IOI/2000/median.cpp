#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>

#define NMAX 1510

using namespace std;

int A[NMAX];
int N,P;

int f;
int med3(int x, int y, int z){
	++f;
	assert(x <= N && y <= N && z <= N);
	if((A[x] < A[y]) == (A[y] < A[z])) return y;
	if((A[z] < A[x]) == (A[x] < A[y])) return x;
	return z;
}

int select(vector<int> &range, int k, int p1, int p2){
	int  i,m,q1,q2;

	vector<int> r1,r2,r3;

	for(i = 0; i < (int)range.size(); ++i){
		if(range[i] == p1 || range[i] == p2) continue;
		m = med3(range[i],p1,p2);
		if(m == p1){
			r1.push_back(range[i]);
		}else if(m == p2){
			r3.push_back(range[i]);
		}else{
			r2.push_back(range[i]);
		}
	}

	if(k < (int)r1.size()){
		if(r1.size() == 1) return r1[0];
		q1 = r1[rand()%r1.size()];
		q2 = q1;
		while(q1 == q2){
			q2 = r1[rand()%r1.size()];
		}

		if(med3(q1,q2,p1) != q2) swap(q1,q2);

		return select(r1,k,q1,q2);
	}

	k -= r1.size();
	if(!k) return p1;
	--k;

	if(k < (int)r2.size()){
		if(r2.size() == 1) return r2[0];
		q1 = r2[rand()%r2.size()];
		q2 = q1;
		while(q1 == q2){
			q2 = r2[rand()%r2.size()];
		}

		if(med3(p1,q1,q2) != q1) swap(q1,q2);

		return select(r2,k,q1,q2);
	}

	k -= r2.size();
	if(!k) return p2;
	--k;

	assert(k < (int)r3.size());
	if(r3.size() == 1) return r3[0];

	q1 = r3[rand()%r3.size()];
	q2 = q1;
	while(q1 == q2){
		q2 = r3[rand()%r3.size()];
	}

	if(med3(p2,q1,q2) != q1) swap(q1,q2);

	return select(r3,k,q1,q2);
}

int main(){
	int i,m,sol;
	vector<int> r;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d",&A[i]);
		r.push_back(i);
	}

	r.pop_back();
	r.pop_back();
	m = select(r,N/2,N-1,N-2);
	sol = A[m];

	sort(A,A+N);

	cout << f << endl;
	assert(sol == A[N/2]);

	return 0;
}
