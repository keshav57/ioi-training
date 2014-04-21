/*
 Created By: Malvika Joshi
 Problem: transform
 Link: http://cerberus.delos.com:791/usacoprob2?a=a1gMVAO4hsK&S=transform
*/

#include <stdio.h>
#include <string.h>

int A[10][10];
int S[10][10];
int T[10][10];
int N = 3;

void rotate(int arr[10][10]){
	int O[10][10];
	int i,j,k;

	memcpy(O, arr, 100*sizeof(int));

	for(i = 0;i < N; i++){
		for(j = N-1,k = 0; j >= 0; j--,k++){
			T[i][k] = O[j][i];
			O[j][i] = 9;
		}
	}
}

void flip(int O[10][10]){
	int i,j,k;

	for(i = 0; i < N; i++){
		for(j = N-1,k = 0; j >= 0; j--,k++){
			T[i][k] = O[i][j];
		}
	}
}

int is_same(int C[10][10]){
	int i,j;
	for(i = 0;i < N; i++){
		for(j = 0;j < N; j++){
			if(S[i][j] != C[i][j]){
				return 0;
			}
		}
	}
	return 1;
}

int get_change(void){
	rotate(A);
	if(is_same(T)) return 1;

	rotate(T);
	if(is_same(T)) return 2;

	rotate(T);
	if(is_same(T)) return 3;

	flip(A);
	if(is_same(T)) return 4;

	rotate(T);
	if(is_same(T)) return 5;

	rotate(T);
	if(is_same(T)) return 5;

	rotate(T);
	if(is_same(T)) return 5;

	if(is_same(A)) return 6;

	return 7;
}

int main(){
	int i,j;
	char c;

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("\n");
		for(j = 0;j < N; j++){
			scanf("%c",&c);
			A[i][j] = c == '@';
		}
	}

	for(i = 0;i < N; i++){
		scanf("\n");
		for(j = 0;j < N; j++){
			scanf("%c",&c);
			S[i][j] = c == '@';
		}
	}

	printf("%d\n",get_change());

	return 0;
}
