#include <cstring>
#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#define NMAX 25010
#define A 26
#define TMAX 500010

using namespace std;

class trie{
private:

	vector<int> child[TMAX];
	char ch[TMAX];
	int N,ins;

	int create_node(char c){
		ch[N] = c;
		return N++;
	}

	void print(int node, int stop){
		int i;

		if(ch[node] > 'z'){
			cout << "P\n";
			return;
		}

		if(node) cout << ch[node] << '\n';

		for(i = 0; i < (int)child[node].size()-1; ++i){
			print(child[node][i],0);
		}
		print(child[node][i],stop);

		if(!stop) cout << "-\n";
	}

	int dfs(int node){
		int i,prev,ht,cur;

		ht = 1;
		prev = -1;
		for(i = 0; i < (int)child[node].size(); ++i){
			cur = dfs(child[node][i]);
			if(i && cur < prev){
				swap(child[node][i],child[node][i-1]);
				continue;
			}
			ht = cur+1;
			prev = cur;
		}

		return ht;
	}

public:

	trie(){
		ch[0] = '\0';
		N = 1;
		ins = 0;
	}

	void insert(string &str){
		int i,node,k;
		++ins;
		node = 0;

		for(i = 0; i < (int)str.length(); ++i){
			for(k = 0; k < (int)child[node].size(); ++k){
				if(ch[child[node][k]] == str[i]) break;
			}

			if(k < (int)child[node].size()){
				node = child[node][k];
				continue;
			}

			child[node].push_back(create_node(str[i]));
			node = child[node].back();
		}
	}

	void print_all(){
		int longest;

		longest = dfs(0);
		cout <<	(N*2)-ins-longest << '\n';
		print(0,1);
	}
};

int N;
trie T;

int main(){
	string str;

	ios_base::sync_with_stdio(0);
	cin >> N;

	while(N--){
		cin >> str;
		str.push_back('z'+1);
		T.insert(str);
	}

	T.print_all();

	return 0;
}


