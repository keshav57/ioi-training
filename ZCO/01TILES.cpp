/*
 Created By: Malvika Joshi
 Problem: 0/1TILES
 Link: http://opc.iarcs.org.in/index.php/problems/01TILES
*/

#include <iostream>

using namespace std;

int main(){

	 int n;
	cin >> n;
	int pre = 1;
	int cur = 1;
	 int fib;

	for( int i = 0;i < n-1;i ++){
		fib = (pre+cur)%15746;
		pre = cur;
		cur = fib;
	}

	cout << cur;


	return 0;
}
