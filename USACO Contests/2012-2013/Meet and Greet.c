/*
 Created By: Malvika Joshi
 Problem: Meet and Greet (December-2012 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=205
*/

#include <stdio.h>

int bessie[1000001];
int elsie[1000001];
int E,B;

int main(){

    int en = 0,bn = 0;

	scanf("%d%d",&B,&E);
	int i,j,n;
	char c;
	bessie[0] = 0;
	bn++;
	elsie[0] = 0;
	en++;
	for(i = 0;i < B;i++){
		scanf("%d ",&n);
		c = getchar();
		if(c == 'R'){
			for(j = bn;j < (bn+n);j ++){
				bessie[j] = bessie[j-1] +1;
			}
		}else {
			for(j = bn;j < (bn+n);j ++){
				bessie[j] = bessie[j-1] -1;
			}
		}
		bn = bn + n;
	}

	for(i = 0;i < E;i++){
		scanf("%d ",&n);
		c = getchar();
		if(c == 'R'){
			for(j = en;j < (en+n);j ++){
				elsie[j] = elsie[j-1] +1;
			}
		}else {
			for(j = en;j < (en+n);j ++){
				elsie[j] = elsie[j-1] -1;
			}
		}
		en = en + n;
	}

	for(i = bn;i < en;i ++){
		bessie[i] = bessie[i-1];
		bn++;
	}

	for(i = en;i < bn;i ++){
		elsie[i] = elsie[i-1];
		en++;
	}

	int count = 0;

	n = bn;

	for(i = 1;i < n; i++){
		if(bessie[i] == elsie[i] && bessie[i-1] != elsie[i-1]){
			count++;
		}
	}

	printf("%d",count);

	return 0;
}
