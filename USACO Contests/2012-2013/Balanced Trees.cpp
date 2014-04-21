/*
 Created By: Malvika Joshi
 Problem: Balanced Trees (November-2013 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=195
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <cassert>
#include <cstring>
#include <vector>
#include <iostream>

#define NMAX 40010

using namespace std;

vector<int> child[NMAX];

int unmatched_sub[NMAX][2];
int unmatched_out[NMAX][2];

int seq[NMAX];
int N;

void sub(){
	int i,u,v,p,add;

	for(v = N-1; v >= 0; --v){

		add = seq[v];

		for(p = 0; p < 2; ++p, add *= -1){

			for(i = 0; i < child[v].size(); ++i){
				u = child[v][i];
				unmatched_sub[v][p] = max(unmatched_sub[v][p],unmatched_sub[u][p]);
			}

			unmatched_sub[v][p] += add;
		}
	}

}

void out(){
	int i,u,p,v,add;
	int max_depth,max_depth2;

	for(v = 0; v < N; ++v){

		add = seq[v];

		for(p = 0; p < 2; ++p,add*=-1){
			max_depth = max(0,unmatched_out[v][p]);
			max_depth2 = 0;

			for(i = 0; i < child[v].size(); ++i){
				u = child[v][i];
				if(unmatched_sub[u][p] > max_depth){
					max_depth2 = max_depth;
					max_depth = unmatched_sub[u][p];
				}else{
					max_depth2 = max(max_depth2,unmatched_sub[u][p]);
				}
			}

			for(i = 0; i < child[v].size(); ++i){
				u = child[v][i];
				unmatched_out[u][p] = unmatched_sub[u][p] == max_depth ? max_depth2 : max_depth;
				unmatched_out[u][p] += add;
			}
		}
	}
}

int get_max(){
	int depth,i;

	depth = 0;
	for(i = 0 ; i < N; ++i){
		depth = max(depth, min(unmatched_out[i][1],unmatched_sub[i][0]) );
		depth = max(depth, min(unmatched_out[i][0],unmatched_sub[i][1]) );
	}

	return depth;
}

int main(){

	int i,p;
	char c;

	scanf("%d",&N);

	for(i = 1; i < N; ++i){
		scanf("%d\n",&p);
		child[p-1].push_back(i);
	}

	for(i =0 ; i < N; ++i){
		scanf(" %c",&c);
		seq[i] = c == '(' ? 1 : -1;
	}

	sub();
	out();

	printf("%d\n",get_max());

	return 0;
}
