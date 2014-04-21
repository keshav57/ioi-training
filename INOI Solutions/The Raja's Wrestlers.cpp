/*
 Created By: Malvika Joshi
 Problem: The Rajah's Wrestlers (INOI-2004)
 Link: http://www.iarcs.org.in/inoi/2004/inoi2004/inoi2004-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

int strength[10000];
int powers[10000];
int id[10000];
int N;

int compare(int i, int j){
	int fi_i = strength[i] + (powers[i] * strength[j]);
	int fi_j = strength[j] + (powers[j] * strength[i]);

	return fi_i > fi_j;
}

int main(){

	int i;
	scanf("%d",&N);

	for(i = 0;i < N;i ++){
		id[i] = i;
		scanf("%d%d",&strength[i],&powers[i]);
	}

	std::sort(id,id+N,compare);

	for(i = 0;i < N;i ++){
		printf("%d\n",id[i]+1);
	}

	return 0;
}
