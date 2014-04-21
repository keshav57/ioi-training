/*
 Created By: Malvika Joshi
 Problem: TILINGS
 Link: http://opc.iarcs.org.in/index.php/problems/TILINGS
*/

#include <iostream>
using namespace std;
int main(){
	int o;
	cin >> o;

	long long unsigned int f1 = 2,f2 = 1,g2 = 1,fn = 2;

	for(int n = 3;n <= o;n ++){
		fn = (f1 + f2 + 2*(g2))%10000;
		g2 = g2 + f2;
		f2 = f1;
		f1 = fn;
	}

	cout << (fn)%10000;

	return 0;
}
