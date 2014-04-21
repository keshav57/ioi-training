/*
 Created By: Malvika Joshi
 Problem: The Price is Wrong (Code Jam Beta 2008  Problem B)
 Link: https://code.google.com/codejam/contest/32014/dashboard#s=p1
*/

#include <algorithm>
#include <cstdio>
#include <cassert>
#include <string>
#include <cstring>
#include <iostream>
#include <map>

#define NMAX 70

using namespace std;

int lis[NMAX];
long long unsigned licost[NMAX];
int prev[NMAX];
int my_order[NMAX];

string order[NMAX];
pair<string,int> lex[NMAX];

string sol[NMAX];

long long unsigned cost[NMAX];
int sel[NMAX];

int N;

pair<int,int> tmp[NMAX];

int dp(){
	int i,k;

	for(i = 0; i < N; ++i){

		lis[i] = 0;
		licost[i] = 0;
		prev[i] = -1;
		sel[i] = 0;

		for(k = i-1; k >= 0; --k){
			if(my_order[k] > my_order[i] || lis[k] < lis[i]) continue;
			if(lis[k] > lis[i] || licost[i] > licost[k]){
				lis[i] = lis[k];
				prev[i] = k;
				licost[i] = licost[k];
			}
		}

		licost[i] += cost[my_order[i]];
		lis[i] += 1;

	}

	k = 0;

	for(i = 1; i < N; ++i){
		if(lis[i] < lis[k]) continue;
		if(lis[i] > lis[k] || licost[i] < licost[k]) k = i;
	}

	return k;
}

int main(){

	int t,i,c,k;

	ios_base::sync_with_stdio(false);

	freopen("in","r",stdin);
	freopen("out","w",stdout);

	c = 0;
	cin >> t;

	while(++c <= t){
		N = 0;
		cin >> order[N];
		while(order[N][0] >= '_'){
			lex[N] = make_pair(order[N],N);
			cin >> order[++N];
		}

		tmp[0].first = atoi(order[N].c_str());
		tmp[0].second = 0;
		for(i = 1; i < N; ++i){
			cin >> tmp[i].first;
			tmp[i].second = i;
		}

		sort(lex,lex+N);

		for(i = 0; i < N; ++i){
			cost[lex[i].second] = (N-i-1) ? (1LL<<(N-i-1)) : 0;
		}

		sort(tmp,tmp+N);

		for(i = 0; i < N; ++i){
			my_order[i] = tmp[i].second;
		}

		i = dp();

		int t2 = lis[i];
		while(i >= 0){
			sel[my_order[i]] = 1;
			i = prev[i];
		}

		k =0;
		cout << "Case #" << c << ":";
		for(i = 0; i < N; ++i){
			if(sel[i]) continue;
			sol[k++] = order[i];
		}

		sort(sol,sol+k);

		assert(t2+k == N);

		for(i =0 ; i < k ; ++i){
			cout << " " << sol[i];
		}
		cout << "\n";
	}

}
