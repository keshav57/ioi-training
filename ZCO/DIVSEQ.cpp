/*
 Created By: Malvika Joshi
 Problem: DIVSEQ
 Link: http://opc.iarcs.org.in/index.php/problems/DIVSEQ
*/

#include <iostream>

using namespace std;

int main(){

	int n;
	cin >> n;
	int array[n];

	for(int i = 0;i < n; i++){cin >> array[i];}

	int DP[n];
	int prev[n];
	int maxlength = 1;
	int bestEnd = 0;

	DP[0] = 1;
	prev[0] = -1;

	for(int i = 1;i < n; i ++){
		DP[i] = 1;
		prev[i] = -1;

		for(int j = i-1; j >=0; j--){
			if(DP[j] + 1 > DP[i] && array[i] % array[j] == 0){
				DP[i] = DP[j] + 1;
				prev[i] = j;
			}
		}

		if(DP[i] > maxlength){
			bestEnd = i;
			maxlength = DP[i];
		}
	}

	cout << maxlength;
	return 0;
}
