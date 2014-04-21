/*
 Created By: Malvika Joshi
 Problem: K-th Number
 Link: http://www.spoj.com/problems/MKTHNUM/
*/

#include <stdio.h>
#include <vector>
#include <stdlib.h>

int left(int p){ return (p+1)*2-1; }
int right(int p){ return (p+1)*2; }

int compare(const void *a, const void *b){ return *(int*)a-*(int*)b;}

std::vector<int> T[300000];
int A[100010];
int inrange;
int N,M;

void init(int node, int s, int e){

	if(s == e){
		T[node].push_back(A[s]);
		return;
	}

	int l,r,n1,n2,i,j;

	l = left(node);
	r = right(node);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	n1 = T[l].size();
	n2 = T[r].size();

	i = 0;
	j = 0;

	while(i < n1 && j < n2){
		if(T[l][i] < T[r][j]){
			T[node].push_back(T[l][i]);
			i++;
		}else{
			T[node].push_back(T[r][j]);
			j++;
		}
	}

	while(i < n1){
		T[node].push_back(T[l][i]);
		i++;
	}

	while(j < n2){
		T[node].push_back(T[r][j]);
		j++;
	}

}

int search(std::vector<int> &a, int  target){
	int low,high,mid;

	low = 0;
	high = a.size()-1;

	while(low <= high){
		mid = (low+high)/2;

		if(target <= a[mid]){
			high = mid-1;
		}else{
			low = mid+1;
		}

	}

	return high+1;
}

int query(int node, int s, int e, int i, int j, int v){

	if(i > e || j < s) return 0;

	int less;

	if(s >= i && e <= j ){
		less = search(T[node],v);
		if(less < T[node].size() && T[node][less] == v) inrange = 1;
		return less;
	}

	int p1,p2;

	p1 = query(left(node),s,(s+e)/2,i,j,v);
	p2 = query(right(node),(s+e)/2+1,e,i,j,v);

	return p1+p2;
}

int query2(int i,int j, int k){

	int low,high,mid,less;

	low = 0;
	high = N-1;

	while(low <= high){

		mid = (low + high)/2;

		inrange = 0;
		less = query(0,0,N-1,i,j,A[mid]);

		if(less == k-1){
			if(inrange) return A[mid];
			else low = mid+1;
		}else if(less >= k){
			high = mid-1;
		}else{
			low = mid+1;
		}

	}

	return -1;
}

int main(){
	int i,a,b,k,sol;
	scanf("%d%d",&N,&M);

	for(i = 0;i < N; i++) scanf("%d",&A[i]);

	init(0,0,N-1);
	qsort(A,N,sizeof(int),compare);


	for(i =0 ;i < M ;i++){
		scanf("%d%d%d",&a,&b,&k);
		sol = query2(a-1,b-1,k);
		printf("%d\n",sol);
	}

	return 0;
}
