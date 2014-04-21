/*
 Created By: Malvika Joshi
 Problem: Gift Coupons (INOI-2006)
 Link: http://www.iarcs.org.in/inoi/2006/inoi2006/inoi2006-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

int compare(int a, int b){
	return a < b;
}

int x,y;
int N,M;
int A[8000];

int exist_xy(int s,int sum){
	int i,j,temp_s;
	i = s;
	j = N-1;

	while(i < j){
		temp_s = A[i]+A[j];
		if(temp_s == sum){
			x = A[i];
			y = A[j];
			return 1;
		}else if(temp_s < sum){
			i++;
		}else{
			j--;
		}
	}
	return 0;
}

int main(){

	int i,z = -1;
	scanf("%d%d",&N,&M);

	for(i = 0;i < N;i ++){
		scanf("%d",&A[i]);
	}

	std::sort(A,A+N,compare);

	for(i = 0;i < N-2; i++){
		if(exist_xy(i+1,M-A[i])){
			z = A[i];
			break;
		}
	}

	if(z != -1){
		printf("%d\n%d\n%d\n",z,x,y);
	}else {
		printf("0\n0\n0");
	}

	return 0;
}
