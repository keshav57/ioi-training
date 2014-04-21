/*
  Created By: Malvika Joshi
  Problem: Segment Flip (IOITC-2011 Final-1)
*/

#include <utility>
#include <set>
#include <stdio.h>
#include <stdlib.h>

typedef struct { int next,prev,key; } l_i;

inline int type(int x){  return x >= 0; }

std::set<std::pair<int,int> > Q;
l_i List[100000];
int H,T,N,K,L;

void list_delete(int x){
	if(x == H){
		H = List[x].next;
	}
	if(x == T){
		T = List[x].prev;
	}

	List[List[x].next].prev = List[x].prev;
	List[List[x].prev].next = List[x].next;

	L--;
}

int list_sum(){
	int sum = List[T].key,i;

	for(i = H; i != T; i = List[i].next){
		sum += List[i].key;
	}

	return sum;
}

int list_fsum(){
	int sum = abs(List[T].key),i;

	for(i = H; i != T; i = List[i].next){
		sum += abs(List[i].key);
	}

	return sum;
}


int main(){

	int i,key,j,k,del;

	j = 0;
	scanf("%d%d",&N,&K);

	for(i = 0;i < N; i++){
		scanf("%d",&key);
		if(j > 0 && type(key) == type(List[j-1].key)){
			List[j-1].key += key;
		}else {
			List[j].prev = j-1;
			List[j].next = j+1;
			List[j].key = key;
			j++;
		}
	}

	N = j;
	H = 0;
	T = N-1;
	L = N;
	k = 0;

	for(i = 0; i < N; i++){
		Q.insert(std::make_pair(abs(List[i].key),i));
		if(type(List[i].key) == 0){
			k++;
		}
	}

	int deleted = 0;

	if(K == 0){
		printf("%d",list_sum());
		return 0;
	}

	while(k > K){
		del = Q.begin()->second;

		Q.erase(Q.begin());


		if((del == H || del == T) && List[del].key >= 0){
			deleted += List[del].key;
			list_delete(del);
		}else{
			if(del != H){
				List[del].key += List[List[del].prev].key;
				Q.erase(std::make_pair(abs(List[List[del].prev].key),List[del].prev));
				list_delete(List[del].prev);
			}
			if(del != T){
				List[del].key += List[List[del].next].key;
				Q.erase(std::make_pair(abs(List[List[del].next].key),List[del].next));
				list_delete(List[del].next);
			}

			Q.insert(std::make_pair(abs(List[del].key),del));

			k--;
		}
	}

	printf("%d ",list_fsum()+ deleted);

	return 0;
}

