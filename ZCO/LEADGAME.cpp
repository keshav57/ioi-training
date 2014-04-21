/*
 Created By: Malvika Joshi
 Problem: LEADGAME
 Link: http://opc.iarcs.org.in/index.php/problems/LEADGAME
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){

	int n;
	cin >> n;
	int diff[n];
	int a = 0;
	int b = 0;
	int lead = 0;

	for(int i = 0;i < n; i++){
		int t, u;
		cin >> t >> u;
		a = a+t;
		b = b+u;
		diff[i] = a-b; // a is leading if +, b if -
		if(abs(lead) < abs(diff[i])){
			lead = diff[i];
		}
	}

	if(lead > 0){
		cout << "1 ";
	}else{
		cout << "2 ";
	}

	cout << abs(lead);

	return 0;

}
