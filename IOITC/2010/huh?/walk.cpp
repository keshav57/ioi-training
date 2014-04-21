/*
 Created By: Malvika Joshi
 Problem: Walk
*/

#include <cstdio>
#include <vector>
#include <set>
#define MAXN 100010
#define INF (long long)2e15
#define MOD (long long)1000000007

using namespace std;

typedef long long int64;

vector<pair<int,long long> > adjacent[MAXN];
set<std::pair<int64,int> > Q;
int64 D[MAXN];
int P[MAXN];
int N,M;

void Dijkstra(int src){
    int v,u,i;
    long long dist;

    for(i = 1; i < N; i++){
        D[i] = INF;
        P[i] = 0;
        Q.insert(make_pair(D[i],i));
    }

    D[src] = 0;
    P[src] = 1;

    Q.insert(make_pair(0,src));

    while(!Q.empty()){
        v = (*Q.begin()).second;
        Q.erase(Q.begin());

        for(i = 0; i < (int)adjacent[v].size(); i++){
        	u = adjacent[v][i].first;
        	dist = adjacent[v][i].second + D[v];
        	if(dist < D[u]){
        		P[u] = 1;
        		Q.erase(make_pair(D[u],u));
        		D[u] = dist;
        		Q.insert(make_pair(D[u],u));
        	}else if(D[u] == dist){
        		++P[u];
        		P[u] %= MOD;
        	}
        }
    }
}

int64 tree_count(){

        int64 trees = 1;
        int i;

        for(i = 0;i < N; i++){
                trees *= P[i];
                trees %= MOD;
        }

        return trees;
}

int main(int argc, char **argv){

        int i,a,b;
        long long c;

        freopen(argv[1],"r",stdin);
        freopen("temp.out","w",stdout);

        scanf("%d %d",&N,&M);

        for(i = 0; i < M; i++){
                scanf("%d%d%lld",&a,&b,&c);
                adjacent[a].push_back(make_pair(b,c));
                adjacent[b].push_back(make_pair(a,c));
        }

        Dijkstra(0);
        int64 sol = tree_count();

        printf("%lld\n",sol);

        return 0;
}
