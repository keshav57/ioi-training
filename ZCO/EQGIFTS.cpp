/*
 Created By: Malvika Joshi
 Problem: EQGIFTS
 Link: http://opc.iarcs.org.in/index.php/problems/EQGIFTS
*/

#include <iostream>
#include <stdlib.h>
#include <limits.h>

using namespace std;

int BalancedPartition ( int a[] , int n ){

    int sum = 0;
    for( int i = 0 ; i < n ; i++)
        sum += a[i];

    int *s = new int[sum+1];

    s[0] = 1;
    for(int i = 1 ; i < sum+1 ; i++)    s[i] = 0;

    int diff = INT_MAX , ans;

    for(int i = 0 ; i < n ; i++)
    {
        for(int j = sum ; j >= a[i] ; j--)
        {
            s[j] = s[j] | s[j-a[i]];
            if( s[j] == 1 )
            {
                if( diff > abs( sum/2 - j) )
                {
                    diff = abs( sum/2 - j );
                    ans = j;
                }

            }
        }
    }

    return abs((sum-ans)-ans) ;
}


int main(){

	int sum = 0;
	int n ;
	cin >> n;
	int array[n];

	for(int i = 0;i < n; i++){
		int a,b;
		cin >> a >> b;
		array[i] = abs(a-b);
	}

	for(int i = 0; i< n; i++){
		sum = sum+ array[i];
	}


	cout << BalancedPartition(array,n);

	return 0;
}
