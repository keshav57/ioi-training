/*
 Created By: Malvika Joshi
 Problem: cowcycles
 Link: http://cerberus.delos.com:791/usacoprob2?a=VzhPBcPn9aw&S=cowcycle
*/
#include <stdio.h>

int F,R,F1,R1,F2,R2;
int rear[15],front[10];
int sol_rear[15],sol_front[10];
double ratio[60],diff[60],minvar = 1000000000;


void find_min(){

	if(front[0]*rear[0]*3 > front[F-1]*rear[R-1]) return;

	int i,j,k,n;
	double r,mean,variance;

	n = 0;
	for(i = F-1;i >= 0;i--){
		for(j = 0; j < R; j++){
			r = (double)front[i]/rear[j];
			k = n++;
			while(k > 0 && ratio[k-1] < r){
				k--;
				ratio[k+1] = ratio[k];
			}
			ratio[k] = r;
		}
	}

	n--;
	mean = 0;
	variance = 0;
	for(i = 0; i < n; i++){
		diff[i] = ratio[i] - ratio[i+1];
		mean += diff[i];
	}

	mean /= n;


	for(i = 0;i < n; i++){
		variance += (diff[i]-mean)*(diff[i]-mean);
	}

	variance /= n;

	if(variance < minvar){
		minvar = variance;
		for(i = 0;i < F; i++) sol_front[i] = front[i];
		for(i = 0;i < R; i++) sol_rear[i] = rear[i];
	}
}

void init_rear(int k){
	if(k >= R){
		find_min();
		return;
	}
	int i;
	i = k ? rear[k-1]+1 : R1;
	for(; i <= R2-R+k+1; i++){
		rear[k] = i;
		init_rear(k+1);
	}
}

void init_front(int k){
	if(k >= F){
		init_rear(0);
		return;
	}
	int i;
	i = k ? front[k-1]+1 : F1;
	for(; i <= F2-F+k+1; i++){
		front[k] = i;
		init_front(k+1);
	}
}

void print(){
	int i;
	printf("%d",sol_front[0]);
	for(i = 1;i < F; i++) printf(" %d",sol_front[i]);
	printf("\n");
	printf("%d",sol_rear[0]);
	for(i = 1; i < R; i++) printf(" %d",sol_rear[i]);
	printf("\n");
}

int main(){
	scanf("%d%d%d%d%d%d",&F,&R,&F1,&F2,&R1,&R2);
	init_front(0);
	print();
	return 0;
}
