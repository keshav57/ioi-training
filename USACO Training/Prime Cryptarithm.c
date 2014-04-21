/*
 Created By: Malvika Joshi
 Problem: crypt1
 Link: http://cerberus.delos.com:791/usacoprob2?a=lbNQDgJoHdG&S=crypt1
*/

#include <stdio.h>
#include <stdlib.h>

int M_1[800];
int M_2[100];
int n_1 = 0,n_2 = 0;
int selected[9] = {0};

void generate1(void){
	int i,j,k;
	for(i = 0;i < 9; i++){
		if(!selected[i]) continue;
		for(j = 0;j < 9; j++){
			if(!selected[j]) continue;
			for(k = 0;k < 9; k++){
				if(!selected[k]) continue;
				M_1[n_1] = i*100 + j*10 + k + 111;
				n_1++;
			}
		}
	}
}

void generate2(void){
	int i,j;
	for(i = 0;i < 9; i++){
		if(!selected[i]) continue;
		for(j = 0;j < 9;j++){
			if(!selected[j]) continue;
			M_2[n_2] = i*10+j+11;
			n_2++;
		}
	}
}

int get_digits(int num){
    int digits = 0;
    while (num) {
        num /= 10;
        digits++;
    }
    return digits;
}

int is_valid(int num,int k){
	if(get_digits(num) != k) return 0;

	while(num > 0){
		if(!selected[num%10-1]){
			return 0;
		}
		num /= 10;
	}
	return 1;
}

int count_valid(void){
	int i,j,p1,p2,sol = 0;

	for(i = 0;i < n_1; i++){
		for(j = 0;j < n_2; j++){
			p1 = M_1[i] * (M_2[j]%10);
			p2 = M_1[i] * ((M_2[j]/10)%10);
			if(is_valid(M_1[i]*M_2[j],4) && is_valid(p1,3) && is_valid(p2,3)){
				sol++;
			}
		}
	}

	return sol;
}

int main(void){

	int i,n,b;

	scanf("%d",&n);

	for(i = 0; i< n; i++){
		scanf("%d",&b);
		selected[b-1] = 1;
	}

	generate1();
	generate2();


	printf("%d\n",count_valid());

	return 0;
}
