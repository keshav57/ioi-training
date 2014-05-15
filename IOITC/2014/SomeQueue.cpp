#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

#define NMAX 1010
#define INF (1e9)

using namespace std;

int tree[NMAX][NMAX];
int N;

void update2(int x, int y, int val){
	if(!y){
		tree[x][y] += val;
		return;
	}

	while(y < N){
		tree[x][y] += val;
		y += (y&-y);
	}
}

void update(int x, int y, int val){
	if(!x){
		update2(x,y,val);
		return;
	}

	while(x < N){
		update2(x,y,val);
		x+=x&-x;
	}
}

int read2(int x, int y){
	if(y < 0) return 0;
	int sum = tree[x][0];

	while(y){
		sum += tree[x][y];
		y -= y&-y;
	}

	return sum;
}

int read(int x, int y1, int y2){
	if(x < 0) return 0;
	int sum = read2(0,y2)-read2(0,y1-1);

	while(x){
		sum += read2(x,y2)-read2(x,y1-1);
		x -= x&-x;
	}

	return sum;
}

int query(int x1, int x2, int y1, int y2){
	return read(x2,y1,y2)-read(x1-1,y1,y2);
}

void init(int n){
	N = n;
	memset(tree,0,sizeof(int)*NMAX);
}


int min_cost[NMAX][NMAX];

vector<int> adj[NMAX];

int cost[NMAX];

void init(){
	int i,g,k;

	for(i =0 ; i < N; ++i){
		for(k =0 ; k < N; ++k){
			min_cost[i][k] = INF;
		}
	}

	for(i =0 ; i < N; ++i){
		for(g = 1; i+g <= N; ++g){

			min_cost[i][i+g-1] = min(min_cost[i][i+g-1],cost[g]);

			for(k = g*2-1; k+i < N; k+=g){
				if(query(i+k-g+1,i+k,i,i+g-1) <= 0) break;
				min_cost[i][k+i] = min(min_cost[i][k+i],cost[g]);
			}
		}
	}

//	for(i =0 ; i < N; ++i){
//		for(k =i; k < N; ++k){
//			cout << min_cost[i][k] << " " << i << " " << k << endl;;
//		}
//		cout << endl;
//	}
}

int dp[NMAX];

int compute(){
	int i,j;

	dp[N] = 0;

	for(i = N-1; i >= 0; --i){
		dp[i] = INF;
		for(j = i+1; j <= N; ++j){
			dp[i] = min(dp[i],dp[j]+min_cost[i][j-1]);
		}
	}

	return dp[0];
}

int M;

int main(){
	int i,j;

	scanf("%d%d",&N,&M);

	while(M--){
		scanf("%d%d",&i,&j);
		--i,--j;
		adj[i].push_back(j);
		update(j,i,1);
	}

	for(i =1; i<=  N; ++i) scanf("%d",&cost[i]);

	init();
	printf("%d\n",compute());

	return 0;
}
