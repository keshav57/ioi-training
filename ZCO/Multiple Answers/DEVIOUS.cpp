/*
 Created By: Malvika Joshi
 Problem: DEVIOUS
 Link: http://opc.iarcs.org.in/index.php/problems/DEVIOUS
*/

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <limits.h>

using namespace std;

struct element{
  int index;
  int value;
};

bool compare(element a, element b){
  return a.value < b.value;
}

int main(){
    int n;
    cin >> n;
    int array [n];
    element elements[n];
    int sum = 0;

    for(int i = 0 ;i < n; i ++){
        cin >> array[i];
        sum = sum + array[i];
        elements[i].index = i;
        elements[i].value = sum;
    }
    sort(elements,elements+n,compare);
    int diff = INT_MAX;
    int i1 = 0,i2 = 0;

    for(int i = 1;i < n;i ++){
        int temp = elements[i].value - elements[i-1].value;
        if(temp < diff){
            diff = temp;
            i1 = elements[i].index;
            i2 = elements[i-1].index;
        }
        else if(temp == diff){
            if(abs(elements[i].index - elements[i-1].index) > abs(i1-i2)){
                i1 = elements[i].index;
                i2 = elements[i-1].index;
            }
        }
    }

    diff = 0;
    int s,e;
    if(i1 >= i2){
        e = i1, s = i2+1;
    }else{
    	s = i1+1, e = i2;
    }

    for(int i = s;i <= e ; i++){
        diff = diff+array[i];
    }
    cout << diff << endl;

    cout << s+1 << " " << e+1;

    return 0;
}
