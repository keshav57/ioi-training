/*
 Created By: Malvika Joshi
 Problem: Auto-Complete (February-2014 Silver)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=397
*/

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <cstdio>

using namespace std;

vector<pair<string,int> > dictionary;

int main(){

	int i,low,high,n,w;
	string word;


	cin >> w >> n;

	i = 1;
	while(w--){
		cin >> word;
		dictionary.push_back(make_pair(word,i++));
	}

	sort(dictionary.begin(),dictionary.end());

	cout << endl;

	while(n--){
		cin >> i >> word;

		low = lower_bound(dictionary.begin(),dictionary.end(),make_pair(word,0))-dictionary.begin();
		word.append("}");
		high = upper_bound(dictionary.begin(),dictionary.end(),make_pair(word,0))-dictionary.begin();

		if(low+i-1 >= high){
			cout << -1 << "\n";
			continue;
		}

		cout << dictionary[low+i-1].second << "\n";
	}

	return 0;
}
