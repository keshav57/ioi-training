/*
 Created By: Malvika Joshi
 Problem: spin
 Link: http://cerberus.delos.com:791/usacoprob2?S=spin&a=M1sjMcmpoAb
*/
#include <stdio.h>
#include <string.h>

int light[360];
int start[5][5];
int extent[5][5];
int wedges[5];
int speed[5];

void mark_light(int w){
	int i,k;

	for(i = 0; i < wedges[w]; i++){
		for(k = 0; k <= extent[w][i]; k++){
			light[(start[w][i]+k)%360]++;
		}
	}
}

int main(){
	int i,j,time,flag = 0;

	for(i = 0;i < 5;i ++){
		scanf("%d %d",&speed[i],&wedges[i]);
		for(j = 0; j < wedges[i]; j++){
			scanf("%d%d",&start[i][j],&extent[i][j]);
		}
	}

	for(time = 0;!flag && time < 360; time++){
		memset(light,0,sizeof(int)*360);
		for(i = 0; i < 5; i++){
			for(j = 0; time && j < wedges[i]; j++){
				start[i][j] += speed[i];
				start[i][j] %= 360;
			}
			mark_light(i);
		}
		for(i = 0;i < 360; i++){
			if(light[i] >= 5){
				flag = 1;
			}
		}
	}

	if(flag){
		printf("%d\n",time-1);
	}else{
		printf("none\n");
	}


	return 0;
}

