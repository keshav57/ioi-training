/*
 Created By: Malvika Joshi
 Problem: TOURNAMENT
 Link: Dead
*/

#include <iostream>
#include <algorithm>
using namespace std;

long long n;
long long str[200000];
long long diff[200000];

int main(){

	cin >> n;
	for(int i = 0;i < n; i++){
		cin >> str[i];
	}

	sort(str,str+n);

	diff[0] = str[0];
	for(int j = 1;j < n;j ++){
		diff[j] = str[j] - str[j-1];
	}

	long long int sum = 0;
	long long int add = 0;

	for(int i = 0;i < n; i++){
		add = add + str[i];
	}

	for(int i = 0;i < n;i ++){
		add = add - (diff[i] * (n-i));
		sum = sum + add;
	}

	cout << sum;

	return 0;
}
