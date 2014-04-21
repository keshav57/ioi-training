/*Problem: Move to Front [RunC]*/

#include <stdio.h>
#include <set>

int U[1000010];
int N,mkey;
std::set<std::pair<int,int> > S;

void Init(int n){
	N = n;
	mkey = 0;

	int i;
	for(i = 0;i < N; i++){
		U[i] = i;
	}
}

void Insert(int x){
	S.insert(std::make_pair(U[x],x));
}

void Delete(int x){
	S.erase(std::make_pair(U[x],x));
}

void MoveToFront(int x){

	int exists;

	exists = S.erase(std::make_pair(U[x],x));
	U[x] = --mkey;
	if(exists) Insert(x);
}

int Min(){
	int min = (*S.begin()).second;
	return min;
}

