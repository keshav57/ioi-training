/*
 Created By: Malvika Joshi
 Problem: contact
 Link: http://cerberus.delos.com:791/usacoprob2?S=contact&a=l22R33vpcwt
*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <stdio.h>

using namespace std;

pair<int,string> sol[10000];
int S = 0,N;
char A[200010];

int compare(pair<int,string> a, pair<int,string> b){
	if(a.first == b.first){
		return a.second.length() ==  b.second.length() ? a.second < b.second : a.second.length() < b.second.length();
	}
	return a.first > b.first;
}

void sel_subset(int K){
	int i,k;
	map<string,int > len_map;
	string key;

	for(i = 0;i <= N-K; i++){
		key.clear();
		for(k = 0;k < K; k++){
			key.push_back(A[i+k]);
		}
		len_map[key] += 1;
	}

	for(map<string,int>::iterator it = len_map.begin(); it != len_map.end(); ++it){
		if(it->second > 0){
			sol[S].first = it->second;
			sol[S].second = it->first;
			S++;
		}
	}

}

int main(){

	int a,b,L;
	char c;

	scanf("%d%d%d\n",&a,&b,&L);

	N= 0;
	c = getchar();
	while(c != EOF){
		if(c != '\n'){ A[N++] = c; }
		c = getchar();
	}

	int i;
	for(i = a; i <= b; i++){
		sel_subset(i);
	}

	sort(sol,sol+S,compare);

	int k = 0,j;

	for(i = 0;i < S && k <= L; i++){
		if(i && sol[i].first == sol[i-1].first){
			if(j){ printf(" "); }
			else{printf("\n");}
			cout  << sol[i].second;
			j++;
			if(j == 6){
				j = 0;
			}
		}else{
			if(k < L){
				j = 1;
				if(i) printf("\n");
				printf("%d\n",sol[i].first);
				cout << sol[i].second;
			}
			k++;
		}
	}

	printf("\n");

}
