/*
 Created By: Malvika Joshi
 Problem: range
 Link: http://cerberus.delos.com:791/usacoprob2?S=range&a=vO5sS8b2zo5
*/

/*
 Runs in cubic time quadratic space. Dynamic Programming.
 For each cell, we find out whether there is a square of size k with upper left corner on that cell, This is true if and only if there is a square of size k-1
 with upper left corner on that cell, the cell right of it, the cell below it and the cell below the cell to its right (diagonal to it).

 square[i][j][k] = square[i][j][k-1] & square[i][j+1][k-1] & square[i+1][j][k-1] & square[i+1][j+1][k-1]
 where '&' is a bitwise 'and'.

 This will have cubic space but we can optimize it as shown in the code below.
*/

#include <stdio.h>
#include <string.h>

int squares[251][251];
int total[251] = {0};
int N;

void find_squares(){
	int i,j,k;

	for(k = 2; k <= N; k++){
		for(i = 0;i < N; i++){
			for(j = 0;j < N; j++){
				if(i == N-1 || j == N-1){
					squares[i][j] = 0;
					continue;
				}
				squares[i][j] = squares[i][j] & squares[i+1][j+1] & squares[i+1][j] & squares[i][j+1];
				total[k] += squares[i][j];
			}
		}
	}
}

int main(){
	int i,j;
	char c[300];

	scanf("%d",&N);
	for(i = 0;i < N; i++){
		scanf("%s",c);
		for(j = 0; j< N; j++){
			squares[i][j] = c[j]-'0';
		}
	}

	find_squares();

	for(i = 2;i <= N; i++){
		if(!total[i]) continue;
		printf("%d %d\n",i,total[i]);
	}

	return 0;
}

