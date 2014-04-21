/*
 Created By: Malvika Joshi
 Problem: Video Game Combos (January-2012 Gold)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=109
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>

#define K_MAX 1002
#define N_MAX 22
#define LEN_MAX 17
#define C 3

using namespace std;

string words[N_MAX];
int N,K;

pair<int,int> next[N_MAX][LEN_MAX][C];
int score[N_MAX][LEN_MAX];
int len_match[N_MAX];

int get_score(string &str1, string &str2){
	if(str2.length() > str1.length()) return 0;

	int i,k;

	i = str2.length(), k =str1.length();

	for(--i,--k; i >= 0 ; --i,--k){
		if(str2[i] != str1[k]) return 0;
	}

	return 1;
}

void match(int i, int m){
	string str;
	int w,k,c;

	str = words[i].substr(0,m);

	for(w = 0; w < N; ++w){
		score[i][m] += get_score(str,words[w]);
	}

	str.push_back('#');
	++m;

	for(c = 0; c < C; ++c){
		str[str.length()-1] = 'A'+c;

		for(w = 0; w < N; ++w){

			for(k = 0; k < m; ++k){
				if(m-k > (int)words[w].length()) continue;
				if(str.substr(k) == words[w].substr(0,m-k)) break;
			}

			len_match[w] = m-k;
		}

		w = max_element(len_match,len_match+N)-len_match;
		next[i][m-1][c] = make_pair(w,len_match[w]);
	}

}

int max_score[K_MAX][N_MAX][LEN_MAX];

int dp(){
	int k,i,m,c;

	for(k = 0; k <= K; ++k){
		for(i = 0; i < N; ++i){
			for(m = 0; m <= (int)words[i].length(); ++m){
				if(!k){
					max_score[k][i][m] += score[i][m];
					continue;
				}

				for(c = 0; c < C; ++c){
					max_score[k][i][m] = max(max_score[k][i][m],\
							max_score[k-1][next[i][m][c].first][next[i][m][c].second]);
				}

				max_score[k][i][m] += score[i][m];

			}
		}
	}

	return max_score[K][0][0];
}

void init(){
	int i,m;

	for(i = 0; i < N; ++i){
		for(m = 0; m <= (int)words[i].length(); ++m){
			match(i,m);
		}
	}
}

int main(){
	int i;

	scanf("%d%d",&N,&K);

	for(i = 0; i < N; ++i){
		cin >> words[i];
	}

	init();
	printf("%d\n",dp());

	return 0;
}
