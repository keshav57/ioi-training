#include <iostream>
#include <cstdio>

using namespace std;

int main(){

	int i,k;

	for(i = 0; i <= 14; ++i){
		if(i&1){
				cout << "min" << i <<":\nleft\njump move_right" << i << "\n\n";

				cout << "found" << i << ":\n";
				k = i;
				while(k--) cout << "put\n";
				cout << "border down" << i << "\nmove\nmove_right" << i << ":\n";

				k = i;
				while(k--) cout <<"get\n";
				cout << "pebble found" << i << "\n";
				cout << "jump add" << i << "\n\n";

				cout << "go_back" << i << ":\nright\nback" << i << ":\nborder up" << i << "\nmove\njump back" << i << "\n\n";

				cout << "up" << i << ":\nright\nborder min" << i+1 << "\nmove\nright\njump move_right" << i << "\n\n";

			continue;
		}
		cout << "min" << i <<":\nright\njump move_right" << i << "\n\n";

		cout << "found" << i << ":\n";
		k = i;
		while(k--) cout << "put\n";
		cout << "border go_back" << i << "\nmove\nmove_right" << i << ":\n";

		k = i;
		while(k--) cout <<"get\n";
		cout << "pebble found" << i << "\n";
		cout << "jump add" << i << "\n\n";

		cout << "go_back" << i << ":\nleft\nleft\nback" << i << ":\nborder down" << i << "\nmove\njump back" << i << "\n\n";

		cout << "down" << i << ":\nleft\nborder min" << i+1 << "\nmove\nleft\njump move_right" << i << "\n\n";
	}

	cout << "min15:\nhalt\n\n";


	for(i = 14; i; --i){
		cout << "add" << i << ":\n";
		cout << "put\n";
	}
	cout << "add" << i << ":\nhalt\n\n";

	return 0;
}
