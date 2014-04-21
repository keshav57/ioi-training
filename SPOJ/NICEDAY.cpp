/*
 Created By: Malvika Joshi
 Problem: The day of the competitors
 Link: http://www.spoj.com/problems/NICEDAY/
*/

#include <stdio.h>
#include <set>
#include <algorithm>

std::pair<int,std::pair<int,int> > A[100000];
std::set<std::pair<int,int> > C;
int N;

int excellent(){
	int i,x,y,count;
	std::set<std::pair<int,int> >::iterator first,last,prev;

	C.clear();

	C.insert(A[0].second);
	count = 1;

	for(i = 1; i < N; i++){
		x = A[i].second.first;
		y = A[i].second.second;

		prev = C.lower_bound(A[i].second);
		first = prev;

		if(prev == C.begin() || (*(--prev)).second > y){
			++count;
			last = first;
			while(last != C.end() && (*last).second > y) last++;

			if(first != last) C.erase(first,last);
			C.insert(A[i].second);
		}

	}

	return count;
}

int main(){
	int i,sol,t;

	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);
		for(i = 0;i < N; i++){
			scanf("%d%d%d",&A[i].first,&A[i].second.first,&A[i].second.second);
		}

		std::sort(A,A+N);

		sol = excellent();

		printf("%d\n",sol);
	}
	return 0;
}

