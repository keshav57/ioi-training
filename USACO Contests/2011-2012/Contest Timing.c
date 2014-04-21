/*
 Created By: Malvika Joshi
 Problem: Contest Timing (November-2011 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=84
*/

#include <stdio.h>

#define start 671

int main(){

	int fin,day,hrs,min,tim;

	scanf("%d%d%d",&day,&hrs,&min);
	day -= 11;

	fin = day*1440;
	fin += hrs*60;
	fin += min;

	tim = start > fin ? -1 : fin-start;

	printf("%d\n",tim);


	return 0;
}
