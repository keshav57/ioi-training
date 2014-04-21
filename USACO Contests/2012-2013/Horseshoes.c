/*
 Created By: Malvika Joshi
 Problem: Horseshoes (November-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=189
*/

#include <stdio.h>

char H[10][10];
int N;
int largest;

void recur(int x, int y, int opened ,int closed){

	if(H[x][y] == '0'){
		return;
	}

	if(H[x][y] == '('){
		opened++;
	}else {
		closed++;
	}

	if(H[x][y] == '(' && closed > 0){
		return;
	}

	if(opened == closed){
		largest = opened << 1 > largest ? opened << 1 : largest;
		return;
	}


	char temp = H[x][y];
	H[x][y] = '0';

	if(x+1 < N){
		recur(x+1,y,opened,closed);
	}

	if(y+1 < N){
		recur(x,y+1,opened,closed);
	}

	if(x-1 >= 0){
		recur(x-1,y,opened,closed);
	}

	if(y-1 >= 0){
		recur(x,y-1,opened,closed);
	}

	H[x][y] = temp;

	return;
}

int main(void){

	int i;
	largest = 0;

	scanf("%d",&N);

	for(i = 0;i < N;i ++){
		scanf("%s",H[i]);
	}

	recur(0,0,0,0);

	printf("%d\n",largest);

	return 0;
}
