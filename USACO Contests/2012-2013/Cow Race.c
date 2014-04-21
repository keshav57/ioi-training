/*
 Create By: Malvika Joshi
 Problem: Cow Race (March-2013 Bronze)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=259
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
	int spd,time;
} run_seg;

run_seg B[MAX_N+10];
run_seg E[MAX_N+10];
int	Run[MAX_N*2+10];

int M,N,R;

int compare(const void *a, const void *b){
	return *(int*)a-*(int*)b;
}

int f(int time, int cow){
	int i,dist;
	run_seg *S = cow ? E : B;
	i = 0;
	dist = 0;

	while(S[i].time && S[i].time <= time){
		time -= S[i].time;
		dist += S[i].time*S[i].spd;
		++i;
	}

	dist += S[i].spd*time;

	return dist;
}

int main(){

	int i,lead,prev,d0,d1,changes;

	scanf("%d%d",&N,&M);

	for(i = 0; i < N; i++,R++){
		scanf("%d%d",&B[i].spd,&B[i].time);
		Run[R] = i ? B[i].time + Run[R-1] : B[i].time;
	}

	for(i = 0; i < M; i++,R++){
		scanf("%d%d",&E[i].spd,&E[i].time);
		Run[R] = i ? E[i].time + Run[R-1] : E[i].time;
	}

	qsort(Run,R,sizeof(int),compare);

	prev  = -1;
	changes = 0;
	for(i = 0; i < R; i++){
		if(i && Run[i] == Run[i-1]) continue;
		d0 = f(Run[i],0);
		d1 = f(Run[i],1);
		lead = d0 == d1 ? -1 : d0 < d1;

		if(lead == -1) continue;
		changes += prev == -1 ? 0 : lead != prev;
		prev = lead;
	}

	printf("%d\n",changes);

	return 0;
}
