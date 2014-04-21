/*
 Created By: Malvika Joshi
 Problem: Cow Photography (December-2011 Bronze)
 Link: http://usaco.org/index.php?page=viewproblem2&cpid=95
*/

#include <cstdio>
#include <map>
#include <algorithm>

#define MAXN 20010

using namespace std;

int photo[5][MAXN];
int pos[5][MAXN];
int next[MAXN];
int N;

map<int,int> C;

int gC(){
	pair<int,int> p= make_pair(-1,1);
	for(map<int,int>::iterator it = C.begin(); it != C.end(); ++it){
		if(it->second > p.second) p = (*it);
	}
	return p.first;
}

void init(){
	int i,k,p,j;

	i = 0;
	for(j = 0; j <= N; j++){
		if(i) printf("%d\n",i);
		C.clear();
		for(k = 0; k < 5; k++){
			p = pos[k][i];
			C[photo[k][p+1]]++;
		}
		next[i] = gC();
		if(next[i] > 0){
			i = next[i];
			continue;
		}
		C.clear();
		for(k = 0; k < 5; k++){
			p = pos[k][i];
			C[photo[k][p+2]]++;
		}
		next[i] = gC();
		i = next[i];
	}

}

int main(){
	int i,k;
	scanf("%d",&N);
	for(k = 0; k < 5; k++){
		for(i = 1; i <= N; i++){
			scanf("%d",&photo[k][i]);
			pos[k][photo[k][i]] = i;
		}
		photo[k][i] = i+k;
	}

	init();

	return 0;
}
