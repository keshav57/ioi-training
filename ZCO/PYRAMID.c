/*
 Created By: Malvika Joshi
 Problem: PYRAMID
 Link: http://opc.iarcs.org.in/index.php/problems/PYRAMID
*/

#include <stdio.h>
#include <stdlib.h>

int comp (const void * elem1, const void * elem2) {
	return (*(int*)elem1 - *(int*)elem2);
}


int main(){
	int i,h,n,temp;
	int array[1000000];

	scanf("%d",&n);
	for(i = 0;i < n; i++){
		scanf("%d%d",&array[i],&temp);
		if(array[i] > temp){
			array[i] = temp;
		}
	}

	qsort(array,n,sizeof(int),comp);

	h = 0;

	for(i = 0;i < n; i++){
		if(array[i] > h){
			h++;
		}
	}


	printf("%d",h);

	return 0;
}


