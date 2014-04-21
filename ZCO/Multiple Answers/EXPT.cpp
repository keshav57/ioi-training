/*
 Created By: Malvika Joshi
 Problem: EXPT
 Link: http://opc.iarcs.org.in/index.php/problems/EXPT
*/

#include <stdio.h>

typedef struct{int i,j;}parent;

parent P[300][300];
int L[300][300];
int s1[300];
int s2[300];
int o1[300],o2[300];
int N;


int max(int a, int b){
	return a > b ? a : b;
}

void LCS(void){
	int i,j,k,l;

	for(i = 0;i < N-1;i ++){
		for(j = 0;j < N-1;j ++){
			for(k = i+1;k < N;k++){
				for(l = j+1;l < N; l++){
					if(s1[k]-s1[i] == s2[l]-s2[j]){
						if(L[i][j]+1 >= L[k][l]){
							L[k][l] = L[i][j] + 1;
							P[k][l].i = i;
							P[k][l].j = j;
						}
					}
				}
			}
		}
	}

}

int lengthlcs(){
	int i,j,p1,p2;
	for(i = 0; i< N; i++){
		for(j = 0;j < N;j ++){
			if(L[i][j] > L[p1][p2]){
				p1 = i;
				p2 = j;
			}
		}
	}

	i = 0;
	while(p1 != -1 && p2 != -1){
		o1[i] = s1[p1];
		o2[i] = s2[p2];
		i++;
		j = P[p1][p2].i;
		p2 = P[p1][p2].j;
		p1 = j;
	}

	return i;
}

int main(void){
	int i,j;

	scanf("%d",&N);

	for(i = 0;i < N;i ++){
		scanf("%d",&s1[i]);
	}
	for(i = 0;i < N;i ++){
		scanf("%d",&s2[i]);
	}

	for(i = 0;i < N;i ++){
		for(j = 0;j < N;j ++){
			L[i][j] = 0;
			P[i][j].i = -1;
			P[i][j].j = -1;
		}
	}

	LCS();

	int max = lengthlcs();

	printf("%d\n",max);

	for(i = max-1;i >= 0;i--){
		printf("%d ",o1[i]);
	}

	printf("\n");

	for(i = max-1;i >= 0;i--){
		printf("%d ",o2[i]);
	}

	return 0;
}
