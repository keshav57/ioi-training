#include <algorithm>
#include <cstdio>
#include <iostream>
#include<vector>
#include <utility>
#include <set>
#include <numeric>

#define NMAX 100010
#define INF (long long)1e9

using namespace std;
typedef long long lli;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]);


vector<pair<int,int> > adj[NMAX];
int N,M;

set<pair<lli,int> > Q;

lli dist1[NMAX];
lli dist2[NMAX];
int ex[NMAX];

lli path(){
	int v,u,i;
	lli tmp;

	for(i = 0; i < N; ++i){
		dist1[i] = dist2[i] = ex[i] ? 0 : INF ;
		Q.insert(make_pair(dist2[i],i));
	}

	while(!Q.empty()){
		v = Q.begin()->second;
		Q.erase(Q.begin());

		if(!v) return dist2[v];

		for(i = 0; i < (int)adj[v].size(); ++i){
			tmp = dist2[v]+adj[v][i].second;
			u = adj[v][i].first;

			if(tmp < dist1[u]){
				Q.erase(Q.find(make_pair(dist2[u],u)));
				dist2[u] = dist1[u];
				dist1[u] = tmp;
				Q.insert(make_pair(dist2[u],u));
			}else if(tmp < dist2[u]){
				Q.erase(Q.find(make_pair(dist2[u],u)));
				dist2[u] = tmp;
				Q.insert(make_pair(dist2[u],u));
			}
		}
	}

/*5 7 2
0 2 4
0 3 3
3 2 2
2 1 10
0 1 100
0 4 7
3 4 9
1 3
 * */

	return INF;
}


int travel_plan(int n, int m, int r[][2], int l[], int k, int p[]){
	int i;

	N = n;
	M = m;

	while(m--){
		adj[r[m][0]].push_back(make_pair(r[m][1],l[m]));
		adj[r[m][1]].push_back(make_pair(r[m][0],l[m]));
	}

	for(i = 0; i < k; ++i){
		ex[p[i]] = 1;
	}

	return path();
}


