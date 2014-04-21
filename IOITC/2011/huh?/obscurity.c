/*
 Problem: Security by Obscurity
*/

#include <stdio.h>

int freq[26] = {0};
int A[100000];
int N;

int getmax(){
	int j,i,rarity,max;

	rarity = 0;
	max = 0;
	j = 0;

	for(i = 0; i < N; i++){
		if(freq[A[i]] == 0){
			freq[A[i]]++;
			rarity++;
		}else if(freq[A[i]] == 1){
			freq[A[i]]++;
			rarity--;
			while(j < i && freq[A[j]] > 1){
				freq[A[j]]--;
				if(freq[A[j]] == 1) { rarity++; }
				j++;
			}
		}
		if(rarity > max){
			max = rarity;
		}
	}

	return max;
}

int main(){

	int i,maxr;
	scanf("%d\n",&N);

	for(i = 0;i < N; i++){
		A[i] = getchar() - 'a';
	}

	maxr = getmax();

	printf("%d",maxr);

	return 0;
}
