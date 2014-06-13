#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;


int main(int argc, char **arg){

	assert(argc == 3);

	int i,f;
	char c,c2;

	f = 0;

	FILE *sol = fopen(arg[1],"r");
	FILE *out = fopen(arg[2],"r");


	while(fscanf(sol," %c",&c) != EOF){

		if(fscanf(out," %c",&c2) == EOF){
			printf("WRONG\n");
			return 0;
		}

		if(c2 == '?') continue;
		if(c^c2){
			printf("WRONG\n");
			return 0;
		}
		++f;
	}

	printf("OK %d\n",f);

	return 0;
}
