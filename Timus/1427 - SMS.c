/*
 Created By: Malvika Joshi
 Problem: SMS
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1427
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char str[100010];
int last[100010];
int sms[100010];
int N,A,B;

void init(){
	int i,k = 0;

	for(i = 0;i < N; i++){
		while(k < N  && (isalpha(str[k]) || str[k] == ' ' || i-k+1 > A)) k++;
		if(!(isalpha(str[i]) || str[i] == ' ')) last[i] = i-1,k = i;
		else if(k > i) last[i] = i < A ? -1 : i-A;
		else last[i] = k;
	}
}

int DP(){
	int i;

	for(i = 0;i < N; i++){
		if(i < B || last[i] == -1){
			sms[i] = 1;
			continue;
		}
		sms[i] = sms[i-B] < sms[last[i]] ? sms[i-B] : sms[last[i]];
		sms[i]++;
	}

	return sms[N-1];
}

int main(){
	scanf("%d%d",&B,&A);
	getchar();
	scanf("%[^\n]s",str);
	N = strlen(str);
	init();
	printf("%d",DP());
	return 0;
}
