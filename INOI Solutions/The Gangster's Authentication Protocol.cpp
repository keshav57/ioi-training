/*
 Created By: Malvika Joshi
 Problem: The Gangster's Authentication Protocol (INOI-2005)
 Link: http://www.iarcs.org.in/inoi/2005/inoi2005/inoi2005-qpaper.pdf
*/
#include <stdio.h>
#include <algorithm>

int Code[2000];
int Decoded[4000];
int N,K;

int compare(int a, int b){
	return a < b;
}

int main(){
	int code_s = 0,i,j,c = 0;
	scanf("%d%d",&N,&K);

	for(i = 0;i < K; i++){
		scanf("%d",&code_s);
		Decoded[c] = code_s;
		c++;
		for(j = 0;j < code_s;j++){
			scanf("%d",&Code[j]);
		}
		std::sort(Code,Code+code_s,compare);
		for(j = 0;j < code_s;j++){
			Code[j] = Code[j]+j;
			Decoded[c] = Code[j]+1;
			c++;
		}
	}

	for(i = 0;i < c;i++){
		for(j = 1;j <= Decoded[i];j++){
			printf("%d ",Decoded[i+j]);
		}
		i = i + Decoded[i];
		printf("\n");
	}


	return 0;
}
