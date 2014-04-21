/*
 Created By: Malvika Joshi
 Problem: dualpal
 Link: http://cerberus.delos.com:791/usacoprob2?a=a1gMVAO4hsK&S=dualpal
*/
#include <stdio.h>
#include <string.h>

char _b[20];
int N,S,K;

int is_palindrome(){
	int i,j;
	for(i = 0,j = N-1; i < N; ++i,--j){
		if(_b[i] != _b[j]){
			return 0;
		}
	}
	return 1;
}

int to_B(int base,int dec){
	int temp;
	if(dec == 0){
		return 0;
	}
	temp = to_B(base,dec/base);
	_b[temp] = dec%base;
	return temp+1;
}

int is_dualpal(int dec){
	int count = 0,base;

	for(base = 2; base < 11; base++){
		N = to_B(base,dec);
		count += is_palindrome();
		if(count >= 2){
			return 1;
		}
	}
	return 0;
}

void print_dp(void){
	int i = 0,num = S+1;
	while(i < K){
		while(!is_dualpal(num)){
			num++;
		}
		printf("%d\n",num);
		num++;
		i++;
	}
}

int main(){
	freopen("dualpal.in","r",stdin);
	freopen("dualpal.out","w",stdout);
	scanf("%d%d",&K,&S);
	print_dp();
	return 0;
}
