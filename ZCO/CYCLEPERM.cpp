/*
 Created By: Malvika Joshi
 Problem: CYCLEPERM
 Link: http://opc.iarcs.org.in/index.php/problems/CYCLEPERM
*/

#include <iostream>

using namespace std;

int main(){

	int n;
	cin >> n;
	int perm[n+1];
	bool vis[n+1];

	perm[0] = 0;
	vis[0] = false;

	for(int i = 1;i <= n; i++){
		cin >> perm[i];
		vis[i] = true;
	}

	int output[n+n];
	int size = 0;

	for(int i =1, c = 0; i < n+1;i++){
		int j = i;
		int first = perm [j];
		while(vis[j]){
			output[c] = j;
			vis[j] = false;
			j = perm[j];
			c++;
			if(perm[j] == first){
				output[c]  = j;
				c++;
				size++;
				break;
			}
		}
	}

	cout << size << endl;
	for(int i = 0, j = 0;i < size; j++){
		int first = output[j];
		j++;
		cout << first << " ";
		while(output[j] != first){
			cout << output[j] << " ";
			j++;
		}
		i++;
		cout << first << endl;

	}

	return 0;
}
