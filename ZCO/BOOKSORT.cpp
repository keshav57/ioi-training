/*
 Created By: Malvika Joshi
 Problem: BOOKSORT
 Link: http://opc.iarcs.org.in/index.php/problems/BOOKSORT
*/

#include <iostream>

using namespace std;

int binary_search(int target, int array[], int size){
    int low = 0;
    int high = size-1;

    while(low <= high){
        int mid = low + (high - low)/2;
        if(target < array[mid]) {
            high = mid-1;
        }else{
            low = mid+1;
        }
    }
    return low;
}

int main(){

	int n;
	cin >> n;

	int mew[n];
	int size = 0;
	int key;
	int j = 0;


	while(j < n){
		cin >> key;
		int i = binary_search(key,mew,size);
		mew[i] = key;
		if(i == size){
			size++;
		}
		j++;
	}

	cout << n-size;
	return 0;
}
