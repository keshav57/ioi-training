/*
 Created By: Malvika Joshi
 Problem: zerosum
 Link: http://cerberus.delos.com:791/usacoprob2?a=rQv2h69LAhX&S=zerosum
*/

#include <stdio.h>
#include <string.h>

int N,T = 0;

long long calc_sum(char A[20]){
	int n,i,sum,a,sign;
	n = strlen(A);

	sum = 0;
	a = 0;
	sign = 1;

	for(i = 0;i < n; i++){
		if(A[i] == ' '){ continue; }
		if(A[i]-'0' >= 0){
			a  *= 10;
			a += A[i]-'0';
		}else{
			sum += a * sign;
			sign = A[i] == '-' ? -1 : 1;
			a = 0;
		}
	}

	sum += a * sign;

	return sum;
}

int K = 0;
void generate(char A[20], int dig){
	int temp;
	if(dig > N){
		temp = calc_sum(A);
		if(!temp){
			printf("%s\n",A);
			T++;
		}
		K++;
		return;
	}

	char E[20];
	sprintf(E,"%s %d",A,dig);
	generate(E,dig+1);

	sprintf(E,"%s+%d",A,dig);
	generate(E,dig+1);

	sprintf(E,"%s-%d",A,dig);
	generate(E,dig+1);
}

int main(){
	char S[20] = "1";
	scanf("%d",&N);
	generate(S,2);
	return 0;
}
