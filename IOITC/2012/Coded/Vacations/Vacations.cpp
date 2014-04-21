/*
 Created By: Malvika Joshi
 Problem: Vacations (IOITC-2012 Test 5)
*/

#include <stdio.h>
#include <vector>

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }

std::vector<int> T[90000];
int L[30010];
int V[30010];
int last[1000010];
int N,M;


void init(int node, int s, int e){

	if(s == e){
		T[node].push_back(L[s]);
		return;
	}

	int i,j,l,r,nl,nr;

	l = left(node);
	r = right(node);

	init(l,s,(s+e)/2);
	init(r,(s+e)/2+1,e);

	nl = T[l].size();
	nr = T[r].size();

	i = 0;
	j = 0;

	while(i < nl && j < nr){
		if(T[l][i] < T[r][j]){
			T[node].push_back(T[l][i]);
			i++;
		}else{
			T[node].push_back(T[r][j]);
			j++;
		}
	}

	while(i < nl){
		T[node].push_back(T[l][i]);
		i++;
	}
	while(j < nr){
		T[node].push_back(T[r][j]);
		j++;
	}
}

int search(std::vector<int> &A, int target){

	int low,high,mid;

	low = 0;
	high = A.size()-1;


	while(low <= high){
		mid = (low + high)/2;

		if(target <= A[mid]){
			high = mid-1;
		}else{
			low = mid+1;
		}

	}

	return high+1;
}

int query(int node, int s, int e, int i, int j){

	if(i > e || j < s) return 0;

	if(s >= i && e <= j) return search(T[node],i);

	int p1,p2;

	p1 = query(left(node),s,(s+e)/2,i,j);
	p2 = query(right(node),(s+e)/2+1,e,i,j);

	return p1+p2;
}

int main(){
	int i,a,b,k = 1000000;

	scanf("%d",&N);

	for(i = 0;i <= k; i++){ last[i] = -1; }

	for(i = 0;i < N; i++){
		scanf("%d",&V[i]);
	}

	for(i =0 ;i < N; i++){
		L[i] = last[V[i]];
		last[V[i]] = i;
	}



	scanf("%d",&M);
	init(0,0,N-1);

	for(i = 0;i < M; i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",query(0,0,N-1,a-1,b-1));
	}

	return 0;
}
