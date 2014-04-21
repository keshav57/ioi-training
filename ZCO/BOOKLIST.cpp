/*
 Created By: Malvika Joshi
 Problem: BOOKLIST
 Link: http://opc.iarcs.org.in/index.php/problems/BOOKLIST
*/

#include <iostream>
#include <set>

using namespace std;

int main(){

	int nbooks;
	cin >> nbooks;

	int booklist[nbooks];

	for(int i = 0;i < nbooks;i++){
		cin >>booklist[i];
	}

	int n;
	cin >> n;

	set<int> sorted;
	int order[n];

	int newentry;

	for(int count = 0; count < n; count++){
		cin >> newentry;
		for(set<int>::iterator i = sorted.begin() ; i!=sorted.end();i ++){
			if(*i <= newentry){
				newentry++;
			}else{
				break;
			}
		}
		sorted.insert(newentry);
		order[count] = newentry;
	}

	for(int i  = 0;i < n;i ++){
		cout << booklist[order[i] - 1] << endl;
	}

	return 0;
}
