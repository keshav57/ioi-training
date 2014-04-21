/*
 Created By: Malvika Joshi
 Problem: STADIUM
 Link: http://opc.iarcs.org.in/index.php/problems/STADIUM
*/

#include <iostream>
#include <algorithm>
using namespace std;

struct event{
	int s;
	int e;
};

bool compare(event a, event b){
	return a.e < b.e;
}

int main(){
	int n;
	cin >> n;

	event list[n];

	for(int i = 0;i < n; i++){
		int a,b;
		cin >> a >> b;
		list[i].s = a;
		list[i].e = a+b;
	}

	sort(list,list+n,compare);

	int count = 0;
	int accept = -1;

	for(int i = 0;i < n;i++){
		if(list[i].s > accept){
			accept = list[i].e;
			count++;
		}
	}

	cout << count;
	return 0;
}
