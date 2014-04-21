/*
 Created By: Malvika Joshi
 Problem: namenum
 Link: http://cerberus.delos.com:791/usacoprob2?a=a1gMVAO4hsK&S=palsquare
*/

#include <stdio.h>
#include <string.h>

int lookup[9][3] = {{'A','B','C'},{'D','E','F'},{'G','H','I'},{'J','K','L'},
		{'M','N','O'},{'P','R','S'},{'T','U','V'},{'W','X','Y'}};
char dictionary[5000][20];
int code[20];
char name[20];
int D,N;

int is_valid(){
	int low = 0,high = D-1,mid,res;

	while(low <= high){
		mid = (high+low)/2;
		res = strcmp(name,dictionary[mid]);
		if(!res){
			return 1;
		}else if(res > 0){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}
	return 0;
}

int lins(){
	int i;
	for(i = 0;i < D;i ++){
		if(!strcmp(name,dictionary[i])){
			return 1;
		}
	}
	return 0;
}

int print_words(int cur){
	if(cur == N){
		if(is_valid()){
			printf("%s\n",name);
			return 1;
		}
		return 0;
	}
	int i,found = 0;
	for(i = 0 ;i < 3; i++){
		name[cur] = lookup[code[cur]][i];
		found |= print_words(cur+1);
	}
	return found;
}

int main(){

	int i;
	char c[12];
	FILE *dict = fopen("dict.txt","r");
	D = 0;

	while(fscanf(dict,"%s",dictionary[D]) != EOF) D++;
	fclose(dict);

	scanf("%s",c);
	N = strlen(c);

	for(i = 0;i < N; i++) code[i] = c[i]-'2';

	if(!print_words(0)){
		printf("NONE\n");
	}


	return 0;
}
