/*
 Created By: Malvika Joshi
 Problem: SMS Dictionary (INOI-2007)
 Link: http://www.iarcs.org.in/inoi/2007/inoi2007/inoi2007-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>
#include <string.h>

int append(int num,int dig){
	return (num*10)+dig;
}

int look_up[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
int keys[100000];
int N;

int get_key(char word[8]){
	int key,i,n,d;

	n = strlen(word);
	key = 0;

	for(i = 0;i < n;i++){
		d = word[i];
		d = d-97;
		d = look_up[d];
		key = append(key,d);
	}

	return key;
}

int compare(int a, int b){
	return a < b;
}

int main(){

	char word[8];
	int i,cur,max = 0,max_i = 0;

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%s",word);
		keys[i] = get_key(word);
	}

	std::sort(keys,keys+N,compare);

	i = 0;
	while(i < N){
		cur = 1;
		while(i < N-1 && keys[i+1] == keys[i]){
			i++;
			cur++;
		}
		if(cur > max){
			max = cur;
			max_i = i;
		}
		i++;
	}

	printf("%d",keys[max_i]);

	return 0;
}
