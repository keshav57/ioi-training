/*
 Created By: Malvika Joshi
 Problem: TIMBER
 Link: http://opc.iarcs.org.in/index.php/problems/TIMBER
*/

#include <stdio.h>

int R[1001][1001];
int Q[1001][1001];
int M,N;
int C;

main() {
	int i,j,k;

	int sum;
	int tx,ty,bx,by;

	scanf("%d %d", &M, &N);

	for (i=1;i<=M;i++)
		for (j=1;j<=N;j++)
			scanf("%d", &(R[i][j]));

	sum=0;
	for (i=1;i<=N;i++) {
		sum=sum+R[1][i];
		Q[1][i]=sum;
	}

	sum=0;
	for(i=1;i<=M;i++) {
		sum=sum+R[i][1];
		Q[i][1]=sum;
	}

	for(i=2;i<=M;i++)
		for(j=2;j<=N;j++)
			Q[i][j]=Q[i][j-1] + Q[i-1][j] - Q[i-1][j-1] + R[i][j];

	for (i=1;i<=M;i++) {
		for (j=1;j<=N;j++)
			printf("%d ", Q[i][j]);
		printf("\n");
	}

	scanf("%d",&C);

	for (i=1;i<=C;i++) {
		scanf("%d %d %d %d", &tx,&ty,&bx,&by);
		sum=Q[bx][by];
		if (tx!=1) sum=sum - Q[tx-1][by];
		if (ty!=1) sum=sum - Q[bx][ty-1];
		if ((tx!=1)&&(ty!=1)) sum=sum+Q[tx-1][ty-1];
		printf("%d\n",sum);
	}

	return  0;

}



