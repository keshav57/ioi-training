/*
 Created By: Malvika Joshi
 Problem: FINDNUMS
 Link: http://opc.iarcs.org.in/index.php/problems/FINDNUMS
*/

#include <stdio.h>
#include <math.h>

int A[4];

int findnums(int k, int S, int P,int c){

	if(k == 1){
		if(S == P){
			A[c] = P;
			return 1;
		}else{
			return 0;
		}
	}

	int i,n = sqrt(P);
	for(i = 1;i <= n;i ++){
		if(P%i == 0){
			A[c] = i;
			if(findnums(k-1,S-i,P/i,c+1)){
				return 1;
			}
		}
	}

	return 0;

}

int main(){

	int S,k,P,i,r = 0;
	scanf("%d%d%d",&S,&P,&k);

	if(findnums(k,S,P,0)){
		for(i = 0;i < k;i ++){
			if(A[i] == 1){
				r = 1;
				break;
			}
		}
		if(r){
			for(i = k-1;i >= 0; i--){
				printf("%d ", A[i] );
			}
		}else{
			for(i = 0;i < k; i++){
				printf("%d " ,A[i]);
			}
		}
	}else{
		printf("NO");
	}

	return 0;
}
