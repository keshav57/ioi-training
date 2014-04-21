/*
 Created By: Malvika Joshi
 Problem: BUFFALOES
 Link: http://opc.iarcs.org.in/index.php/problems/BUFFALOES
*/

#include <stdio.h>

typedef struct{
	int buffalo;
	int days;
	int price;
}chain;

int costs[400];
chain temp[100000];
int t = 0;
chain cur[100000];
int c = 0;
int N,K;

void removet(){
	int i,j;
	for(i = 0;i < t;i ++){
		for(j = i+1;j < t;j++){
			if(temp[j].days != -1 && temp[j].buffalo == temp[i].buffalo && temp[j].days <= temp[i].days && temp[j].price >= temp[i].price){
				temp[i].days = -1;
			}else if(temp[i].days != -1 && temp[i].buffalo == temp[j].buffalo && temp[i].days <= temp[j].days && temp[i].price >= temp[j].price){
				temp[j].days = -1;
			}
		}
	}
}

void copy(){
	int i;
	for(i = 0;i < c;i ++){
		temp[i] = cur[i];
	}
}

void find(){

	int i = 0,j;
	temp[t].price = 0;
	temp[t].days = 0;
	temp[t].buffalo = 0;
	t++;
	temp[t].price = - costs[i];
	temp[t].buffalo = 1;
	temp[t].days = 1;
	t++;

	for(i = 1;i < N; i++){
		for(j = 0;j < t;j++){
			if(temp[j].days != -1){
				cur[c]  = temp[j];
				c++;
				if(temp[j].days < K){
				if(temp[j].buffalo){
					cur[c].buffalo = 0;
					cur[c].days = temp[j].days + 1;
					cur[c].price = temp[j].price + costs[i];
					c++;
				}else{
					cur[c].buffalo = 1;
					cur[c].days = temp[j].days+1;
					cur[c].price = temp[j].price - costs[i];
					c++;
				}
				}
			}
		}
		copy();
		t = c;
		removet();

		c = 0;
	}

}

int main(){

	int i, max = 0;
	scanf("%d%d",&N,&K);

	for(i = 0;i < N; i++){
		scanf("%d",&costs[i]);
	}

	find();

	for(i = 0;i < t;i ++){
		if(temp[i].days != -1){
			if(temp[i].price > max){
				max = temp[i].price;
			}
		}
	}

	printf("%d",max);

	return 0;

}
