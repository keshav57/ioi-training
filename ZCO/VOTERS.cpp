/*
 Created By: Malvika Joshi
 Problem: VOTERS
 Link: http://opc.iarcs.org.in/index.php/problems/VOTERS
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool binary_search(int , int[], int, int&);

int main(){

	int An, Bn, Cn;
	cin >> An >> Bn >> Cn;
	int A[An], B[Bn], C[Cn];
	bool look[Bn];
	vector<int> output;

	for(int i = 0;i < An;i ++) cin >> A[i];
	for(int i = 0;i < Bn;i ++){
		cin >> B[i];
		look[i] = true;
	}
	for(int i = 0;i < Cn; i++) cin >> C[i];

	for(int i = 0;i < An;i ++){
		int key;
		if(binary_search(A[i] , B , Bn, key)){
			look[key] = false;
			output.push_back(A[i]);
		}else if(binary_search(A[i] , C , Cn, key)){
			output.push_back(A[i]);
		}
	}

	for(int i = 0;i < Bn; i++){
		if(look[i]){
			int temp;
			if(binary_search(B[i] , C , Cn, temp)){
				output.push_back(B[i]);
			}
		}
	}

	int s = output.size();
	cout << s << endl;

	sort(output.begin() , output.end());

	for(int i = 0; i < s; i++){
		cout << output[i] << endl;
	}


	return 0;
}

bool binary_search(int target, int array[], int size, int &key){
    int low = 0;
    int high = size-1;

    while(low <= high){
        int mid = low + (high - low)/2;
        if(target < array[mid]) {
            high = mid-1;
        }else if(target > array[mid]){
            low = mid+1;
        }
        else{
        	key = mid;
        	return true;
        }
    }
    return false;

}

