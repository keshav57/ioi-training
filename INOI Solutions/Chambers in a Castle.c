/*
 Created By: Malvika Joshi
 Problem: Chambers in a Castle (INOI-2003)
 Link: http://www.iarcs.org.in/inoi/2003/inoi2003/qpaper/inoi2003-qpaper.pdf
*/

#include <stdio.h>

int Floor_plan[500][500];
int M,N;
int filled = 0;


int fill(int x_t,int y_t){

	if(Floor_plan[x_t][y_t]){
		return 0;
	}

	Floor_plan[x_t][y_t] = 1;
	filled++;

	fill(x_t-1,y_t);
	fill(x_t+1,y_t);
	fill(x_t,y_t-1);
	fill(x_t,y_t+1);

	return 1;
}

int main(){

	int i,j;
	int max_fill = 0,chambers = 0;
	scanf("%d%d",&M,&N);

	for(i = 0;i < M; i++){
		for(j = 0;j < N; j++){
			scanf("%d",&Floor_plan[i][j]);
		}
	}

	for(i = 0;i < M;i ++){
		for(j = 0;j < N;j++){
			if(fill(i,j)){
				chambers++;
				if(filled > max_fill){
					max_fill =  filled;
				}
				filled = 0;
			}
		}
	}


	printf("%d\n%d",chambers,max_fill);

	return 0;

}
