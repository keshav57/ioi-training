#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define NMAX 1000010
#define LOGN 21

using namespace std;

class tree{
private:
	int ances[NMAX][LOGN];
	char key[NMAX];
	int N,log;

	int get_len(int i){
		int k,n;

		n = 1;
		for(k = log-1; k >= 0; --k){
			if(ances[i][k] < 0) continue;
			i = ances[i][k];
			n += (1<<k);
		}


		return n;
	}

public:

	tree(){
		N = 0;
		log = 0;
		memset(ances,-1,sizeof(ances));
	}

	int insert(int p, char c){
		int k;

		ances[N][0] = p;

		for(k = 1; ances[N][k-1] >= 0; ++k){
			ances[N][k] = ances[ances[N][k-1]][k-1];
		}

		log = max(log,k);
		key[N] = c;

		return N++;
	}

	char query(int i, int p){
		int k;

		p = get_len(i)-p-1;

		for(k = log-1; k >= 0; --k){
			if((1<<k) > p || ances[i][k] < 0) continue;
			i = ances[i][k];
			p -= (1<<k);
		}


		return key[i];
	}



};

tree str;

int Q;

int cur_node[NMAX];
int N;

int main(){

	int i;
	char c;

	scanf("%d",&Q);

	while(Q--){
		scanf(" %c",&c);

		if(c == 'T'){
			scanf(" %c",&c);
			cur_node[N] = str.insert(N ? cur_node[N-1] : -1,c);
			++N;
			continue;
		}

		scanf("%d",&i);

		if(c == 'U'){
			cur_node[N] = cur_node[N-1-i];
			++N;
			continue;
		}

		printf("%c\n",str.query(cur_node[N-1],i));
	}

	return 0;
}
