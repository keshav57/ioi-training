/*
 Created By: Malvika Joshi
 Problem: milk
 Link: http://cerberus.delos.com:791/usacoprob2?a=xxfhBCrOcq5&S=milk
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int price,amount; }m_cost;

int compare(const void* a, const void* b){
	const m_cost *p1 = a;
	const m_cost *p2 = b;
	return p1->price - p2->price;
}

m_cost A[5000];
int N,M;

int min_cost(){
	int cost,qty,i;

	cost = 0;
	i = 0;
	qty = N;

	while(i < M && qty > 0){
		if(A[i].amount <= qty){
			qty -= A[i].amount;
			cost += A[i].amount * A[i].price;
		}else{
			cost += qty * A[i].price;
			qty = 0;
		}
		i++;
	}
	return cost;
}

int main(){
	int i;
	scanf("%d%d",&N,&M);
	for(i = 0; i < M; i++){
		scanf("%d%d",&A[i].price,&A[i].amount);
	}

	qsort(A,M,sizeof(m_cost),compare);

	printf("%d\n",min_cost());
	return 0;
}
