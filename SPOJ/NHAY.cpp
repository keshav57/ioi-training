/*
 Created By: Malvika Joshi
 Problem: A Needle in a Haystack
 Link: http://www.spoj.com/problems/NHAY/
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

vector<int> T;
string W;
int N;

void init(){
	int i,j;

	T.push_back(0);
	i = 1,j = 0;

	while(i < N){
		if(W[j] == W[i]){
			T.push_back(++j);
			++i;
		}
		else if(j){
			j = T[j-1];
		}else{
			T.push_back(0);
			++i;
		}
	}
}

int main(){
	int i,m;
	char c;

	while(scanf("%d",&N) == 1){
		W.clear();
		T.clear();

		for(i = 0; i < N; ++i){
			scanf(" %c",&c);
			W.push_back(c);
		}

		init();

		scanf(" %c",&c);

		i = 0;
		m = 0;
		while(c != '\n'){
			if(W[i] == c){
				if(i == N-1){
					printf("%d\n",m-i);
				}
				++m;
				++i;
				scanf("%c",&c);
			}else if(i){
				i = T[i-1];
			}else{
				++m;
				scanf("%c",&c);
			}
		}
		printf("\n");
	}

	return 0;
}
