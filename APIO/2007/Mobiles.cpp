/*
 APIO 2007 Mobiles
*/

#include <algorithm>
#include <iostream>
#include <cstdio>

#define NMAX 200010

using namespace std;

int typ[NMAX];
int height[NMAX];

int swapped[NMAX];

int child[NMAX][2];
int leaf[NMAX];

int N;

void dfs(int v){
	if(leaf[v]){
		height[v] = 1;
		typ[v] = 1;
		return;
	}

	int l,r;

	l = child[v][0];
	r = child[v][1];

	dfs(l);
	dfs(r);


//	cout << l << " " << typ[l] << " " << swapped[l] << " " << height[l] << endl;
//	cout << r << " " << typ[r] << " " << swapped[r] << " " << height[r] << endl;

	height[v] = max(height[l],height[r])+1;
	typ[v] = min(typ[l],typ[r]);
	swapped[v] = swapped[l]+swapped[r];

	if(typ[v] < 0) return;

	if(!typ[l] && !typ[r]){		//both incomplete
		typ[v] = -1;
		return;
	}

	if(height[l] == height[r]){			//heights are same then the complete subtree will go first
		swapped[v] += typ[l] < typ[r];
		return;
	}

	typ[v] = 0;
	if(height[l] < height[r]){			//height are different then the larger subtree will go first
		swap(l,r);
		swapped[v] += 1;
	}

	if(height[l] > height[r]+1){
		typ[v]  = -1;
		return;
	}

	if(!typ[r]){						//if the right subtree is smaller than left and not complete
		typ[v] = -1;
		return;
	}
}

int main(){
	int i,tmp;

	scanf("%d",&N);
	tmp = N;

	for(i =0 ; i < tmp; ++i){
		scanf("%d%d",&child[i][0],&child[i][1]);
		if(child[i][0] < 0){
			leaf[N] = 1;
			child[i][0] = N++;
		}else{
			--child[i][0];
		}
		if(child[i][1] < 0){
			leaf[N] = 1;
			child[i][1] = N++;
		}else{
			--child[i][1];
		}
	}

	dfs(0);

	printf("%d\n",typ[0] < 0 ? typ[0] : swapped[0]);

	return 0;
}
