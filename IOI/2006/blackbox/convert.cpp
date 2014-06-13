#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

char box[32][32];
int N;

int main(){
	int i,j,ct;

	ct = 0;
	scanf("%s",box[i]);
	N = strlen(box[i]);

	for(i = 1; i < N;  ++i){
		scanf("%s",box[i]);
	}

	for(i =0 ; i < N; ++i){
		for(j = 0; j < N; ++j){
			ct += box[i][j] != '.';
		}
	}

	printf("%d\n",N);
	printf("%d\n",ct);

	for(i =0 ; i < N; ++i){
		for(j =0 ; j < N; ++j){
			if(box[i][j] == '.') continue;
			printf("%d %d %c\n",j+1,i+1,box[i][j]);
		}
	}

	return 0;
}
