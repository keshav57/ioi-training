/*
 Created By: Malvika Joshi
 Problem: Moo Sick (November-2011 Bronze)
 Link: 	http://usaco.org/index.php?page=viewproblem2&cpid=86
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200010
#define MAX_C 15

int song[MAX_N];
int chord[MAX_C];
int rs_chord[MAX_C];
int ind[MAX_N];
int C,N,I;

int compare(const void *a, const void *b){
	return *(int*)a-*(int*)b;
}

int check(){
	int i,d;
	qsort(chord,C,sizeof(int),compare);
	d = chord[0] - rs_chord[0];

	for(i = 1; i < C; ++i){
		if(chord[i]-rs_chord[i] != d) return 0;
	}

	return 1;
}

int main(){

	int i;
	scanf("%d",&N);
	for(i = 0; i < N; ++i) scanf("%d",&song[i]);

	scanf("%d",&C);
	for(i = 0; i < C; ++i) scanf("%d",&rs_chord[i]);
	qsort(rs_chord,C,sizeof(int),compare);

	for(i = 0; i+C <= N; ++i){
		memcpy(chord,song+i,sizeof(int)*C);
		if(check(i)) ind[I++] = i;
	}

	printf("%d\n",I);
	for(i = 0; i < I; ++i) printf("%d\n",ind[i]+1);

	return 0;
}
