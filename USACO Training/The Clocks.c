/*
 Created By: Malvika Joshi
 Problem: clocks
 Link: http://cerberus.delos.com:791/usacoprob2?S=clocks&a=p4AVC4mhs60
*/

#include <stdio.h>
#include <string.h>

int moves[9][9] = { {4,0,1,3,4}, {3,0,1,2}, {4,1,2,4,5} , {3,0,3,6},
{5,1,3,4,5,7}, {3,2,5,8}, {4,3,4,6,7}, {3,6,7,8}, {4,4,5,7,8}};
int sol[40];
int S = 0;

int reached(int clocks[10]){
	int i;
	for(i = 0;i < 9; i++){
		if(clocks[i] != 0){ return 0; }
	}
	return 1;
}

void perform_move(int m, int *clocks){
	int i,c;
	for(i = 1; i <= moves[m][0]; i++){
		c = moves[m][i];
		clocks[c] += 3;
		clocks[c] %= 12;
	}
	return;
}

int dfs(int move,int pos[10]){
	if(reached(pos)){ return 1; }
	if(move < 0){ return 0;	}

	int clocks[10];
	memcpy(clocks,pos,sizeof(int)*10);

	if(dfs(move-1,clocks)){return 1;}

	perform_move(move,clocks);
	if(dfs(move-1,clocks)){
		sol[S++] = move;
		return 1;
	}

	perform_move(move,clocks);
	if(dfs(move-1,clocks)){
		sol[S++] = move;
		sol[S++] = move;
		return 1;
	}

	perform_move(move,clocks);
	if(dfs(move-1,clocks)){
		sol[S++] = move;
		sol[S++] = move;
		sol[S++] = move;
		return 1;
	}

	return 0;
}

int main(){

	int i,C[10];

	for(i = 0;i < 9; i++){
		scanf("%d",&C[i]);
		C[i] %= 12;
	}

	if(!dfs(8,C)){
		return 0;
	}

	for(i = 0 ;i < S-1; i++){
		printf("%d ",sol[i]+1);
	}
	printf("%d\n",sol[i]+1);

	return 0;
}
