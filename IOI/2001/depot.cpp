#include <vector>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<int> arr[20];
int R;

int perm[20];
int P;

void dfs(int f_val, int f_row){
	int i,val,row,k;

	if(f_val < 0 && arr[0].empty()){
		for(i = P-1; i >= 0; --i){
			printf("%d ",perm[i]);
		}
		printf("\n");
		return;
	}

	if(f_val < 0){
		for(i = 0; !arr[i].empty() && i < R; ++i){
			if(arr[i].size() == arr[i+1].size()) continue;
			row = i;
			val = arr[i].back();
			arr[i].pop_back();
			dfs(val,row);
			arr[i].push_back(val);
		}

		return;
	}

	if(!f_row){
		perm[P++] = f_val;
		dfs(-1,-1);
		--P;
		return;
	}

	row = f_row-1;
	for(i = 0; i < (int)arr[row].size() && arr[row][i] < f_val; ++i){
		if(i+1 < arr[row].size() && arr[row][i+1] < f_val) continue;
		val = arr[row][i];
		arr[row][i] = f_val;
		dfs(val,row);
		arr[row][i] = val;
	}
}

int main(){
	int i,n;

	scanf("%d",&R);

	for(i = 0; i < R; ++i){
		scanf("%d",&n);
		while(n--){
			arr[i].push_back(0);
			scanf("%d",&arr[i].back());
		}
	}


	dfs(-1,-1);
}

