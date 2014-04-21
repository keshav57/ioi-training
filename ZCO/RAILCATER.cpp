/*
 Created By: Malvika Joshi
 Problem: RAILCATER
 Link: http://opc.iarcs.org.in/index.php/problems/RAILCATER
*/

#include <iostream>
using namespace std;

int main(){

	int n, k;
	cin >> n >> k;
	int array[n];
	for(int i = 0;i < n; i++){
		cin >> array[i];
	}

	int sum = 0;


	for(int i = 0;i < k;i ++){
		sum = sum+array[i];
	}


	int max_ending_here = sum;
	int max_so_far = sum;

	for(int i = k;i < n; i++){
		sum = sum + array[i] - array[i-k];
		max_ending_here = max_ending_here+ array[i];
		if(sum > max_ending_here) max_ending_here= sum;

		if(max_ending_here > max_so_far) max_so_far = max_ending_here;

	}

	cout << max_so_far;

	return 0;
}
