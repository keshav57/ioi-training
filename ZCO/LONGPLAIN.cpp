/*
 Created By: Malvika Joshi
 Problem: LONGPALIN
 Link: http://opc.iarcs.org.in/index.php/problems/LONGPALIN
*/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


string LCSubstring (string s1, string s2, int l1, int l2){

	short int **M;

	M= new short int*[l1+1]; //creates a new array of pointers to int objects
	for(short int i=0; i < l1+1; ++i){
		M[i] = new short int[l2+1];
	}

	int longest = 0;
	int x_longest = 0;

	for(int i = 0;i < l1+1;i ++){
		for(int j = 0;j < l2+1; j++){
			M[i][j] = 0;
		}
	}

	for(int x = 1; x < l1+1 ; x++){
		for(int y = 1; y <l2+1; y++){
			if(s1[x-1] == s2[y-1]){
				M[x][y] = M[x-1][y-1] +1;
				if(M[x][y] > longest){
					longest = M[x][y];
					x_longest = x;
				}
			}else{
				M[x][y] = 0;
			}
		}
	}

	cout << longest << endl;
	return s1.substr(x_longest-longest,longest);
}

int main(){

	int len;
	cin >> len;
	string str;
	cin >> str;
	string str2 = str;

	reverse(str2.begin(),str2.end());

	cout <<LCSubstring(str,str2,len,len);

	return 0;
}
