#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <cstdio>

#define NMAX 1000010

using namespace std;

typedef long long lli;


char visited[NMAX];

int par[NMAX];
int pdist[NMAX];

lli lsub[NMAX];
lli lstart[NMAX];
lli out_path[NMAX];
char onpath[NMAX];

vector<pair<int,int > > adj[NMAX];

int b1,b2,dist;

int stack[NMAX];
int S;
int it[NMAX],f[NMAX];

void dfs2(int src){
	int v,u;
	lli m2;

	stack[S++] = src;

	while(S){
		v = stack[S-1];

		if(!visited[v]){
			visited[v] = 1;
			it[v] = -1;
		}

		for(++it[v]; it[v] < (int)adj[v].size(); ++it[v]){
			u = adj[v][it[v]].first;
			if(!f[v] && u == par[v]){
				f[v] = 1;
				adj[v][it[v]].first = -1;
				continue;
			}
			if(visited[u]){
				if(visited[u] == 2){
					adj[v][it[v]].first = -1;
					continue;
				}
				assert(b1 < 0);
				b1 = v;
				b2 = u;
				dist = adj[v][it[v]].second;
				onpath[v] = 1;
				adj[v][it[v]].first = -1;
				continue;
			}

			par[u] = v, pdist[u] = adj[v][it[v]].second;
			stack[S++] = u;
			break;
		}

		if(it[v] < (int)adj[v].size()) continue;

		++visited[v];

		m2 = 0;
		for(int i = 0; i < (int)adj[v].size(); ++i){
			u = adj[v][i].first;
			if(u < 0) continue;
			onpath[v] |= onpath[u];
			lsub[v] = max(lsub[u],lsub[v]);

			if(lstart[u]+pdist[u] > lstart[v]){
				m2 = lstart[v];
				lstart[v] = lstart[u]+pdist[u];
			}else{
				m2 = max(m2,lstart[u]+pdist[u]);
			}

			if(!onpath[u]) out_path[v] = max(out_path[v], lstart[u]+pdist[u]);
		}

		lsub[v] = max(lsub[v],lstart[v]+m2);
		--S;
	}

//	cout << b1 << " " << b2 << endl;
}


lli max_sel_back(){

	assert(b1 >= 0 && b2 >= 0 && b1 != b2);
	int v;
	lli len,append,tot,tmp,back;

	v = b1;
	len = 0;
	append = 0;
	tmp = 0;
	tot = 0;

	while(v != b2){
		append = max(append,len+out_path[v]);
		len += pdist[v];
		v = par[v];
	}
	tmp = dist+append;

	v = b2;
	len = 0;
	append = 0;
	while(v >= 0){
		append = max(append,len+out_path[v]);
		len += pdist[v];
		v = par[v];
	}
	tmp += append;
	tot = max(tot,tmp);				//CASE 1


	len= 0;
	v = b1;
	while(v != b2){
		len += pdist[v];
		v = par[v];
	}
	back = len;

	append = 0;
	v = par[b1];
	len -= pdist[b1];


	while(v != b2){
		append = max(append,out_path[v]+len);
		len -= pdist[v];
		v = par[v];
	}

	tot = max(tot,append+dist+lstart[b1]);					//CASE 2

	v = b1;
	len = 0;
	while(v != b2){
		len = max(len,out_path[v]);
		len -= pdist[v];
		append = dist+back+len+out_path[par[v]];
		tot = max(tot,append);		//CASE 3
		v = par[v];
	}

	return tot;
}

lli compute(int root){
	par[root] = -1;
	pdist[root] = 0;
	b1 = b2 = -1;
	dist = 0 ;
	dfs2(root);

	return max(lsub[root],max_sel_back());
}

int N;

int main(){
	int i,j,k;
	lli tot;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		scanf("%d%d",&j,&k);
		--j;
		assert(j >= 0 && j < N);
		adj[i].push_back(make_pair(j,k));
		adj[j].push_back(make_pair(i,k));
	}

	tot = 0;
	for(i =0 ; i < N; ++i){
		if(visited[i]) continue;
		tot += compute(i);
	}

	printf("%lld\n",tot);

	return 0;
}
