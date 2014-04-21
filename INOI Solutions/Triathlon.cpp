/*
 Created By: Malvika Joshi
 Problem: Triathlon (INOI-2012)
 Link: http://www.iarcs.org.in/inoi/2012/inoi2012/inoi2012-qpaper.pdf
*/

#include <stdio.h>
#include <algorithm>

struct t_data{
	int cobol;
	int other;
};

t_data A[200000];

bool compare(t_data a, t_data b){
	return a.other > b.other;
}

int main(){

	int n,c,p,d,i;
	int worst,temp,C;
	scanf("%d",&n);

	for(i = 0;i < n ;i ++){
		scanf("%d%d%d",&c,&p,&d);

		A[i].cobol = c;
		A[i].other = d+p;
	}

	std::sort(A,A+n,compare);

	worst = 0;
	C = 0;
	for(i = 0;i < n;i ++){
		C = C + A[i].cobol;
		temp = C + A[i].other;
		if(worst < temp){
			worst = temp;
		}
	}

	printf("%d",worst);

	return 0;
}
