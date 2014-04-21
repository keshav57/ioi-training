/*
 Created By: Malvika Joshi
 Problem: shopping
 Link: http://cerberus.delos.com:791/usacoprob2?S=shopping&a=aTJVJLBs1Lw
*/

#include <stdio.h>
#include <string.h>

int O,N;
int lookup[1000];
int prices[5] = {0};
int purchases[5] = {0};
int offers[100][5] = {{0}};
int ofprice[100];
int K[6][6][6][6][6];


int knapsack(){
	int i,j,k,l,m;

	for(i = 0; i <= purchases[0]; i++)
	for(j  =0;j <= purchases[1]; j++)
	for(k = 0;k <= purchases[2]; k++)
	for(l = 0;l <= purchases[3]; l++)
	for(m = 0; m <= purchases[3]; m++)
		K[i][j][k][l][m] = prices[0]*i + prices[1]*j + prices[2]*k + prices[3]*l + prices[4]*m;

	int n,temp;

	for(n = 0; n < O; n++){
		for(i = 0;i <= purchases[0]; i++){
			if(i < offers[n][0]) continue;
			for(j = 0; j <= purchases[1]; j++){
				if(j < offers[n][1]) continue;
				for(k = 0; k <= purchases[2]; k++){
					if(k < offers[n][2]) continue;
					for(l = 0; l <= purchases[3]; l++){
						if(l < offers[n][3]) continue;
						for(m = 0; m <= purchases[4]; m++){
							if(m < offers[n][4]) continue;
							temp = ofprice[n] + K[i-offers[n][0]][j-offers[n][1]][k-offers[n][2]][l-offers[n][3]][m-offers[n][4]];
							if(temp < K[i][j][k][l][m]){ K[i][j][k][l][m] = temp; }
						}
					}
				}
			}
		}
	}

	return K[purchases[0]][purchases[1]][purchases[2]][purchases[3]][purchases[4]];
}


int main(){
	int tempdata[100][20];
	int i,j;

	scanf("%d",&O);

	for(i = 0;i < O; i++){
		scanf("%d",&tempdata[i][0]);
		for(j = 1;j <= tempdata[i][0]; j++){
			scanf("%d%d",&tempdata[i][j*2],&tempdata[i][j*2+1]);
		}
		scanf("%d",&tempdata[i][1]);
	}

	memset(lookup,-1,sizeof(int)*100);

	scanf("%d",&N);
	for(j = 0;j < N; j++){
		scanf("%d%d%d",&i,&purchases[j],&prices[j]);
		lookup[i] = j;
	}

	int k;
	for(i = 0,k = 0;i < O; i++,k++){
		for(j = 1;j <= tempdata[i][0];j ++){
			if(lookup[tempdata[i][j*2]] == -1){
				k--;
				break;
			}
			offers[k][lookup[tempdata[i][j*2]]] = tempdata[i][j*2+1];
		}
		ofprice[k] = tempdata[i][1];
	}

	O = k;

	printf("%d\n",knapsack());

/*
	for(i = 0;i < 5; i++){
		printf("%d ",prices[i]);
	}

	for(i = 0;i < O; i++){
		printf("\n%d\n",ofprice[i]);
		for(j = 0;j < 5; j++){
			printf("%d ",offers[i][j]);
		}
	}
*/
	return 0;
}
