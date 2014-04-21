/*
 Created By: Malvika Joshi
 Problem: ttwo
 Link: http://cerberus.delos.com:791/usacoprob2?S=ttwo&a=pCHmrNTn9hl
*/

#include <stdio.h>
#include <string.h>

typedef struct { int x,y,dir; } pos;

int visited[10][10][10][10][4][4];
int Grid[10][10];

pos move(pos cur){
	if(cur.dir == 0 && cur.x > 0 && Grid[cur.x-1][cur.y]){
		cur.x -= 1;
	}else if(cur.dir == 1 && cur.y < 9 && Grid[cur.x][cur.y+1]){
		cur.y += 1;
	}else if(cur.dir == 2 && cur.x < 9 && Grid[cur.x+1][cur.y]){
		cur.x += 1;
	}else if(cur.dir == 3 && cur.y > 0 && Grid[cur.x][cur.y-1]){
		cur.y -= 1;
	}else{
		cur.dir += 1;
		cur.dir %= 4;
	}
	return cur;
}


int dfs(pos fj, pos cow){

	int mins = 0;

	while(!visited[fj.x][fj.y][cow.x][cow.y][fj.dir][cow.dir]){
		visited[fj.x][fj.y][cow.x][cow.y][fj.dir][cow.dir] = 1;
		if(fj.x == cow.x && fj.y == cow.y)	return mins;
		fj = move(fj);
		cow = move(cow);
		mins++;
	}

	return 0;
}

int main(){
	int i,j;
	char c;
	pos fj,cows;

	fj.dir = 0;
	cows.dir = 0;
	memset(visited,0,sizeof(int)*10000*16);

	for(i = 0;i < 10; i++){
		if(i) scanf("\n");
		for(j = 0;j < 10; j++){
			scanf("%c",&c);
			Grid[i][j] = !(c == '*');
			if(c == 'C'){
				cows.x = i;
				cows.y = j;
			}
			if(c == 'F'){
				fj.x = i;
				fj.y = j;
			}
		}
	}

	printf("%d\n",dfs(fj,cows));

	return 0;
}
