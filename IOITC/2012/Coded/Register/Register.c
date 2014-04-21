/* 
 Created By: Malvika Joshi
 Problem Register (IOITC-2012 Test 3)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int index, value; }pair;

inline int left(int p){ return (p+1)*2-1; }
inline int right(int p){ return (p+1)*2; }
inline int parent(int x){ return (x+1)/2-1; }


int compare(const void *a, const void *b){
	const pair *p1 = a;
	const pair *p2 = b;
	return p1->value-p2->value;
}

int T[300000];
pair A[100000];
int lookup[100000];
int leaves[100000];
int N,Q;

void init(int node, int s, int e){

	if(s == e){
		T[node] = A[s].value;
		leaves[s] = node;
		return;
	}

	init(left(node),s,(s+e)/2);
	init(right(node),(s+e)/2+1,e);

	T[node] = 0;
}

void update(int node, int s, int e, int i, int j){

	if(i > e || j < s) return;

	if(s >= i && e <= j){
		T[node]--;
		return;
	}

	update(left(node),s,(s+e)/2,i,j);
	update(right(node),(s+e)/2+1,e,i,j);
}

int get_val(int leaf){

	int k = leaf,val =0;

	while(k >= 0){
		val += T[k];
		k = parent(k);
	}

	return val;
}

int search(int target){
	int low  = 0,mid,val,high = N-1;

	while(low <= high){
		mid = (high+low)/2;
		val = get_val(leaves[mid]);
		if(target >= val){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}
	return high;
}


void preprocess(){
	qsort(A,N,sizeof(pair),compare);
	int i;

	for(i= 0;i < N; i++){
		lookup[A[i].index] = i;
	}

}

void perform1(int i){
	int target,k;

	target = get_val(leaves[lookup[i]]);
	k = search(target);
	T[leaves[k]]++;
	lookup[A[k].index] = lookup[i];
	A[lookup[i]].index = A[k].index;
	lookup[i] = k;
	A[k].index = i;
}

int perform2(int x){
	int k;
	k = search(x-1);
	return N-k-1;
}

void perform3(int x){
	int k;
	k = search(x-1)+1;
	update(0,0,N-1,k,N-1);
}

int main(){
	int i,x,q;
	scanf("%d%d",&N,&Q);

	for(i = 0;i < N; i++){
		scanf("%d",&A[i].value);
		A[i].index = i;
	}

	preprocess();
	init(0,0,N-1);

	for(i = 0;i < Q; i++){
		scanf("%d%d",&q,&x);
		if(q == 1){
			perform1(x);
		}else if(q == 2){
			printf("%d\n",perform2(x));
		}else{
			perform3(x);
		}
	}
	if(Q == 1) return 1;

	return 0;
}
