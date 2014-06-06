#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 2000010

using namespace std;

int lookup[NMAX];
pair<int,int> tel[NMAX];
int N,M;

char visited[NMAX];

int compute_len(int st){
	int i,len;

	i = st;
	len = 0;

	while(!visited[i]){
		visited[i] = 1;
		if(i >= N-1) break;
		i = lookup[tel[i+1].second];
		++len;
	}

	return len;
}

int path;
int cyc[NMAX];
int C;


int main(){
	int i;

	scanf("%d%d",&N,&M);

	tel[0] = make_pair(0,-1);
	for(i = 1; i <= N; ++i){
		scanf("%d%d",&tel[i].first,&tel[i].second);
		tel[N+i] = make_pair(tel[i].second,tel[i].first);
	}
	N*=2;
	++N;

	sort(tel,tel+N);
	for(i = 0; i < N; ++i){
		lookup[tel[i].first] = i;
	}

	path = compute_len(0);

	for(i = 0; i < N; ++i){
		if(visited[i]) continue;
		cyc[C++] = compute_len(i);
	}

	sort(cyc,cyc+C);

	while(M-- && C){
		path += cyc[--C]+2;
	}

	++M;
	while(M--){
		if(C){
			path += cyc[--C]+2;
			continue;
		}
		path++;
		cyc[C++] = 1;
	}
	printf("%d\n",path);

	return 0;
}
