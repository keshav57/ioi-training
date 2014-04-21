/*
 Created By: Malvika Joshi
 Problem: Painting the Fence (January-2013 Silver)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=226
*/

#include <stdio.h>
#include <map>
#include <set>

typedef struct { int start,end; } move;

std::map<int,int> cc;
std::set<int> points;
move moves[100000];
int visited[100001] = {0};
int original[100001];
int P,N,K;

int main(void){

	int i,cur = 0,steps;
	char c;
	std::set<int>::iterator it1;

	points.insert(0);

	scanf("%d %d",&N,&K);

	//store moves in the form start-end
	for(i = 0;i < N; i++){
		scanf("\n%d %c",&steps,&c);

		if(c == 'R'){
			moves[i].start = cur;
			cur += steps;
			moves[i].end = cur;
		}else {
			moves[i].end = cur;
			cur -= steps;
			moves[i].start = cur;
		}
		points.insert(cur);
	}

	P = points.size();

	//compress coordinates
	for(it1 = points.begin(),i = 0; it1 != points.end(); ++it1,i++){
		cc[*it1] = i;
		original[i] = *it1;
	}

	//replace original with compressed values
	for(i = 0;i < N; i++){
		moves[i].start = cc[moves[i].start];
		moves[i].end = cc[moves[i].end];
	}

	//mark visited
	for(i = 0;i < N; i++){
		visited[moves[i].start+1] += 1;
		visited[moves[i].end+1] += -1;
	}

	int vis = 0;
	for(i = 0;i < P; i++){
		vis += visited[i];
		visited[i] = vis;
	}

	//count visited more than K times
	int count = 0;
	for(i = 1;i < P; i++){
		if(visited[i] >= K){
			count += original[i] - original[i-1];
		}
	}

	printf("%d\n",count);

	return 0;
}
