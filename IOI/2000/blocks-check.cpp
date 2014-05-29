#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>
#include <utility>
#include <cassert>

#define NMAX 52
#define TYP 12
#define ROT 64

using namespace std;

vector<int> sols[200];
vector<int> D;
int S;

int main(int argc, char **arg){
	int d1,d2,i;

	assert(argc == 3);

	FILE *sol = fopen(arg[1],"r");
	FILE *out = fopen(arg[2],"r");

	fscanf(sol,"%d",&d1);
	fscanf(out,"%d",&d2);

	if(d1 != d2){
		printf("WRONG\n");
		return 0;
	}

	fscanf(sol,"%d",&S);

	for(i = 0; i < S; ++i){
		for(int k = 0; k < d1; ++k){
			sols[i].push_back(0);
			fscanf(sol,"%d",&sols[i][k]);
		}
		sort(sols[i].begin(),sols[i].end());
	}

	for(i = 0; i < d1; ++i){
		D.push_back(0);
		fscanf(out,"%d",&D[i]);
	}

	sort(D.begin(),D.end());

	for(i = 0; i < S; ++i){
		if(sols[i] == D){
			printf("CORRECT\n");
			return 0;
		}
	}

	printf("WRONG\n");

	return 0;
}
