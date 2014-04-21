/*
 Created By: Malvika Joshi
 Problem: NEXTPERM
 Link: http://opc.iarcs.org.in/index.php/problems/NEXTPERM
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){

	int n,k;
	cin >> n >> k;

	int array[n];

	for(int m = 0; m <k ;m++){
		for(int i = 0;i < n; i++){
			cin >> array[i];
		}
		int ii = 0,ij = 0;

		for(int i = n-2;i >=0 ; i--){
			if(array[i] < array[i+1]){
				ii = i;
				break;
			}
		}

		for(int j = n-1;j > ii;j--){
			if(array[j] > array[ii]){
				ij = j;
				break;
			}
		}
		swap(array[ii],array[ij]);
		for(int i = 0;i <= ii; i++){
			cout << array[i] << " ";
		}

		for(int i = n-1;i > ii;i--){
			cout << array[i] << " ";
		}

		cout << endl;
	}

}
