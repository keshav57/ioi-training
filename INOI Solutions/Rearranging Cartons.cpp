/*
 Created By: Malvika Joshi
 Problem: Rearranging Cartons (INOI-2009)
 Link: http://www.iarcs.org.in/inoi/2009/inoi2009/inoi2009-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

struct e_seq{
	int id;
	int key;
};

e_seq O_A[100000];
int A[100000];
int N;
int inv = 0;

int search(int target){
	int low = 0;
	int high = N;
	int mid;

	while(low <= high){
		mid = low + (high-low)/2;
		if(O_A[mid].key < target){
			low = mid+1;
		}else if(O_A[mid].key > target){
			high = mid-1;
		}else{
			return O_A[mid].id;
		}
	}
	return -1;
}

void merge(int si,int mid,int ei){
	int C[100000];
	int i,j,k,n;
	i = si;
	j = mid+1;
	n = (ei-si)+1;
	for(k = 0;k < n;k++){
		if(i > mid){
			C[k] = A[j];
			j++;
		}else if(j > ei){
			C[k] = A[i];
			i++;
		}else if(A[i] < A[j]){
			C[k] = A[i];
			i++;
		}else{
			C[k] = A[j];
			j++;
			inv = inv + (mid-i)+1;
		}
	}

	for(i = 0;i < n;i++){
		A[si+i] = C[i];
	}

}

void mergesort(int si,int ei){
	if(si >= ei){
		return;
	}

	int mid = si + (ei-si)/2;

	mergesort(si,mid);
	mergesort(mid+1,ei);
	merge(si,mid,ei);
}

int compare(e_seq a, e_seq b){
	return a.key < b.key;
}

int main(){

	int i;
	scanf("%d",&N);
	for(i = 0;i < N;i ++){
		scanf("%d",&A[i]);
	}
	for(i = 0;i < N; i++){
		scanf("%d",&O_A[i].key);
		O_A[i].id = i;
	}

	std::sort(O_A,O_A+N,compare);

	for(i = 0;i < N;i++){
		A[i] = search(A[i]);
	}

	mergesort(0,N-1);

	printf("%d",inv);

	return 0;
}
