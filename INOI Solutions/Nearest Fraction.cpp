/*
 Created By: Malvika Joshi
 Problem: Nearest Fraction (INOI-2003)
 Link: http://www.iarcs.org.in/inoi/2003/inoi2003/qpaper/inoi2003-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

typedef struct {int n, d;} fraction;

fraction X[9801];
fraction A[500];
int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int n_p = 15;
int N,K;

int is_reduced(int n, int d){
	int i;
	for(i = 0;i < n_p;i++){
		if(n % primes[i] == 0 && d % primes[i] == 0){
			return 0;
		}
	}
	return 1;
}

int compare(fraction a, fraction b){
	return (a.n * b.d) < (b.n * a.d);
}

int binary_search(fraction target){
	int low = 0;
	int high = K-1;
	int mid;

	while(low <= high){
		mid = low + (high-low)/2;
		if(compare(X[mid],target)){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}

	return low;
}

int main(){

	int i,j;

	scanf("%d",&N);

	for(i = 2 ;i < 99; i++){
		for(j = 1;j < i; j++){
			if(is_reduced(j,i)){
				X[K].d = i;
				X[K].n = j;
				K++;
			}
		}
	}

	std::sort(X,X+K,compare);

	for(i = 0;i < N; i++){
		scanf("%d%d",&A[i].n, &A[i].d);
	}

	for(i = 0;i < N;i ++){
		j = binary_search(A[i]);
		printf("%d %d %d %d\n",X[j-1].n,X[j-1].d,X[j].n,X[j].d);
	}

	return 0;
}
