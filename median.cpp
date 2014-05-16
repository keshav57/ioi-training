#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

#define NMAX 1510

using namespace std;

int A[NMAX];
int order[NMAX];
int N,P;

int f;
int med3(int x, int y, int z){
	++f;
	assert(x <= N && y <= N && z <= N);
	if((A[x] < A[y]) == (A[y] < A[z])) return y;
	if((A[z] < A[x]) == (A[x] < A[y])) return x;
	return z;
}

/*
5
2 5 4 3 1
 */

int prev1 = -1,prev2 = -1;

int search(int i){
	int high,low,mid1,mid2,n;

	double m;

	m = (P-1)/2.0;
	low = max(0.0,m-((double)N-i+1)/2.0);
	high = min(P-1.0,m+((double)N-i+1)/2.0);

	while(low <= high){
		n = high-low+1;

		n/=3;
		mid1 = low+n;
		mid2 = mid1+n;

		if(mid1 == mid2){
			if(mid2 < P-1) ++mid2;
			else{
				assert(mid1);
				--mid1;
			}
		}

		m = med3(order[mid1],order[mid2],i);

		if(m == i){
			low = mid1+1;
			high = mid2-1;
		}else if(m == order[mid1]){
			high = mid1-1;
		}else{
			low = mid2+1;
		}
	}

	return low;
}

void insert(int k, int pos){
	int i;

	for(i = P; i > pos; --i){
		order[i] = order[i-1];
	}
	order[i] = k;
	++P;
}

int main(){
	int i,m;

	scanf("%d",&N);
	for(i = 1; i <= N; ++i){
		scanf("%d",&A[i]);
	}

	order[0] = 1;
	order[1] = 2;
	P = 2;

	for(i = 3; i <= N; ++i){
		insert(i,search(i));
	}

	m = A[order[N/2]];

	sort(A+1,A+N+1);

	assert(m == A[(N+1)/2]);

	cout << f << endl;

	return 0;
}
