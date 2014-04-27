/*
 Created By: Malvika Joshi
 Problem: First (December-2012 Gold)
 Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=212
*/

#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <numeric>
#include <iostream>

#define CHMAX 300010
#define NMAX 30010

using namespace std;

int adj[CHMAX][27];
int V;

void init(){
	memset(adj,-1,sizeof(int)*CHMAX*27);
	V = 1;
}

void addword(string &word){
	int i,v;

	v = 0;

	for(i = 0; i < (int)word.length(); ++i){
		if(adj[v][word[i]-'a'] < 0){
			adj[v][word[i]-'a'] = V++;
		}
		v = adj[v][word[i]-'a'];
	}
}

char graph[27][27];
char visited[27];

void create_graph(string &word){
	int i,v,k;

	v = 0;
	memset(graph,0,27*27);
	memset(visited,0,27);

	for(i = 0; i < 26; ++i){
		graph[26][i] = 1;
	}

	for(i = 0; i < (int)word.length(); ++i){
		for(k = 0; k < 27; ++k){
			if(k == word[i]-'a' || adj[v][k] < 0) continue;
			graph[word[i]-'a'][k] = 1;
		}
		v = adj[v][word[i]-'a'];
	}

}

int dfs(int v){
	int i;
	if(visited[v]) return visited[v] >= 0;
	visited[v] = -1;

	for(i = 0; i < 27; ++i){
		if(!graph[v][i]) continue;
		if(!dfs(i)){
			return 0;
		}
	}

	visited[v] = 1;

	return 1;
}

int first[NMAX];
string str[NMAX];
int N;

int main(){
	int i;

	ios::sync_with_stdio(false);
	init();
	cin >> N;

	for(i = 0; i < N; ++i){
		cin >> str[i];
		str[i].push_back('z'+1);
		addword(str[i]);
	}

	for(i =0 ; i < N; ++i){
		create_graph(str[i]);
		first[i] = dfs(26);
	}

	cout << accumulate(first,first+N,0) << "\n";

	for(i = 0; i < N; ++i){
		if(!first[i]) continue;
		str[i].erase(str[i].end()-1);
		cout << str[i] << "\n";
	}

	return 0;
}
