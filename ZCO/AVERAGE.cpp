/*
 Created By: Malvika Joshi
 Problem: AVERAGE
 Link: http://opc.iarcs.org.in/index.php/problems/AVERAGE
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main(){

	int n;
	cin >> n;
	 int array[n];
	int count = 0;

	for(int i = 0;i < n; i++){
		cin >> array[i];
	}

	sort(array,array+n);

	for(int i = 0;i < n;i ++){
		if(array[i] == array[i-1] || array[i] == array[i+1]){
			count++;
		}else{
		int l = i-1,h = i+1;
		while(l >= 0 && h < n){
		 int sum = array[l]+array[h];
			if(sum == array[i]*2){
				count++;
				break;
			}
			if(sum < array[i]*2){
				++h;
			}else{
				--l;
			}
		}
		}
	}

	cout << count;

}

