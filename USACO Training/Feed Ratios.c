/*
 Created By: Malvika Joshi
 Problem: ratios
 Link: http://cerberus.delos.com:791/usacoprob2?a=3zLnjccTCIq&S=ratios
*/

#include <stdio.h>

typedef struct { int a,b,c; } ratio;

int proper(ratio a, ratio b){

	int g;

	if(b.a && !(a.a%b.a)){
		g = a.a/b.a;
	}else if(b.b && !(a.b%b.b)){
		g = a.b/b.b;
	}else if(b.c && !(a.c%b.c)){
		g = a.c/b.c;
	}else{
		return 0;
	}

	if(b.a*g != a.a || b.b*g != a.b || b.c*g != a.c){
		return 0;
	}
	return g;
}

ratio r1,r2,r3,goal;

int main(){
	int i,j,k,min = 301;
	int s1,s2,s3,p = 0,g;
	ratio temp;

	scanf("%d%d%d",&goal.a,&goal.b,&goal.c);
	scanf("%d%d%d",&r1.a,&r1.b,&r1.c);
	scanf("%d%d%d",&r2.a,&r2.b,&r2.c);
	scanf("%d%d%d",&r3.a,&r3.b,&r3.c);

	for(i = 0;i <= 100; i++){
		for(j = 0;j <= 100; j++){
			for(k = 0;k <= 100; k++){
				temp.a = r1.a*i + r2.a*j + r3.a*k;
				temp.b = r1.b*i + r2.b*j + r3.b*k;
				temp.c = r1.c*i + r2.c*j + r3.c*k;
				g = proper(temp,goal);
				if(i+j+k < min && g){
					s1 = i;
					s2 = j;
					s3 = k;
					p = g;
					min = i+j+k;
				}
			}
		}
	}

	if(!p){
		printf("NONE\n");
	}else{
		printf("%d %d %d %d\n",s1,s2,s3,p);
	}

	return 0;
}
