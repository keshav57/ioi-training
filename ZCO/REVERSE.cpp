/*
 Created By: Malvika Joshi
 Problem: REVERSE
 Link: http://opc.iarcs.org.in/index.php/problems/REVERSE
*/

#include <iostream>
#include <string>

using namespace std;

int main(){

	int n;
	cin >> n;
	string str[n][80];
	int size[n];

	cin.ignore(1000,'\n');

	for(int  i = 0;i < n; i ++){
		char chars[80] = "";
		cin.getline(chars,80);
		size[i] = 0;
		for(int j = 0 , s = 0; chars[j] != '\0'; j++){
			str[i][j] = "";
			while(chars[j] != '\'' && chars[j] != '.' && chars[j] != ',' && chars[j] != ';' && chars[j] != ':' && chars[j] != ' ' && chars[j]!= '\0'){
				str[i][s].append(1,chars[j]);
				j++;
			}
			size[i] = s;
			if(str[i][s] != ""){
				s++;
			}
		}
	}

	for(int k = n-1; k >= 0; k--){
		for(int c = size[k]; c >=0; c--){
			cout << str[k][c] << " ";
		}
		cout << endl;
	}
	return 0;
}
