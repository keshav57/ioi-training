/*
 Created By: Malvika Joshi
 Problem: Cultural Programme (INOI-2008)
 Link: http://www.iarcs.org.in/inoi/2008/inoi2008/inoi2008-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

int E[100000];
int X[100000];
int N;

int compare(int a, int b){
	return a < b;
}

int main(){

	int i,j,k,max,cur;
	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d%d",&E[i],&X[i]);
	}

	std::sort(E,E+N,compare);
	std::sort(X,X+N,compare);

	i = 0;
	j = 0;
	max = 0;
	cur = 0;

	for(k = 0;k < N*2; k++){
		if(i >= N){
			cur--;
			j++;
		}else if(j >= N){
			cur++;
			i++;
			if(cur > max){
				max = cur;
			}
		}else if(E[i] < X[j]){
			cur++;
			i++;
			if(cur > max){
				max = cur;
			}
		}else{
			cur--;
			j++;
		}
	}

	printf("%d",max);

}
