/*
 Created By: Malvika Joshi
 Problem: Petrol tank (IOITC-2013 Final 1)

 There can be many ways to go from s to d, we only need the one which minimizes the maximum weight edge, so we first find
 an MST of the graph. Any path from s to d will go through their Lowest Common Ancestor c, so we need the maximum weight edges
 from s to c and s to d. So we create two tables P and T of size |V|*log|V| and the i,jth entry of the table P stores the 2^jth anscestor
 of i and the corresponding entry of table T stores the maximum weight edge encountered from i to its ancestor. As any number can be
 written as an addition of the powers of two, we can answer the queries quite efficiently in O(log|V|) time per query.
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#define MAXN 100010
#define LOGN 20

using namespace std;

vector<pair<int,int> > adj[MAXN]; //Adjacency List
set<pair<pair<int,int>,int> > Q; //Priority queue for finding MST

//MST information
int taken[MAXN];	//Visited nodes
int par[MAXN];			//Parents of every node
int pdist[MAXN];		//Weight of the edge to the parent
int lev[MAXN];			//BFS finishing time

//Information for the ancestor table
int P[MAXN][LOGN];		//Ancestor table
int T[MAXN][LOGN];	//Minimum weight edge on the way to the ancestor

int N,M;	//N vertices M edges

void build_tree(int root){

	//Find the minimum spanning tree using Prim's algorithm.

	int i,v,u,c;

	v = root;
	taken[v] = 1;
	lev[v] = 0;
	pdist[v] = 0;
	par[v] = -1;

	for(i = 0;i < (int)adj[v].size(); ++i){
		Q.insert(make_pair(adj[v][i],v));  //Q has all the edges going out of the tree ordered by weight.
	}

	while(!(Q.empty())){
		c = (*Q.begin()).first.first;	//The weight of the topmost edge in the queue
		v = (*Q.begin()).first.second;	//The vertex outside the tree to which the topmost edge is incident
		u = (*Q.begin()).second;		//The vertex in the tree to which the topmost edge is incident
		Q.erase(Q.begin());

		if(taken[v]) continue;			//Both the end-points of the edge are already in the tree.

		for(i = 0; i < (int)adj[v].size(); ++i){
			Q.insert(make_pair(adj[v][i],v));
		}

		/*As this algorithm proceeds in a breadth first manner, we can update the information of v(the new none)
		 using the information of u(the other end of the new edge).*/

		par[v] = u;
		pdist[v] = c;
		lev[v] = lev[u]+1;
		taken[v] = 1;
	}

}

void init(){
	int i,j;

	/*Create table of size NlogN where the i,jth entry of the table stores the 2^jth ancestor of i
	  and the maximum weight edge from i to its 2^th ancestor.*/

	 for (i = 0; i < N; i++){
		 for (j = 0; (1<<j) <= N; ++j){
			 P[i][j] = -1;
	 	 }
	 }

	for(i = 0; i < N; i++){
		P[i][0] = par[i];	//The 1st ancestor of everyone is their parent.
		T[i][0] = pdist[i];
	}

	for(j = 1; (1<<j) <= N; j++){
		for(i = 0; i < N; i++){
			if(P[i][j-1] == -1) continue;
			P[i][j] = P[P[i][j-1]][j-1];	// Because 2^j = 2^j-1 * 2.
			T[i][j] = max(T[i][j-1],T[P[i][j-1]][j-1]);
		}
	}
}

int query(int p, int q){
	int log,i;
	//p and q are the nodes we want to query.
	if(lev[p] < lev[q])	swap(p,q); //So that we can assume p is the lower node.


	for(log = 0; (1<<log) <= lev[p]; ++log);
	--log;

	int mcost = 0;

	for(i = log; i >= 0; i--){
		if(lev[p]-(1<<i) >= lev[q]){
			mcost = max(mcost,T[p][i]);
			p = P[p][i]; //Move p upwards till it is on the same level as q while updating the maximum weight edge seen so far.
		}
	}

	for(log = 0; (1 << log) <= lev[p]; ++log);
	--log;

	if(p == q) return mcost;

	for(i = log; i >= 0; --i){
		if(P[p][i] != -1 && P[p][i] != P[q][i]){
			mcost = max(mcost,T[p][i]); //As we only go higher up the tree, we store the maximum of all the edges encountered in the way.
			mcost = max(mcost,T[q][i]);
			/*Unless the ith ancestor of p and q is equal, we can jump to their ith ancestor. Recall p and q are
			  on the same level so the same can be said for their ith ancestors*/
			p = P[p][i];
			q = P[q][i];
		}
	}

	/*The search terminates when p and q have the same parent, but this does not mean p and q are equal,
	 so we need to consider two more edges.*/

	return max(mcost,max(pdist[q],pdist[p]));
}

int main(){

	int i,a,b,c;

	scanf("%d%d",&N,&M);

	for(i = 0;i < M; i++){
		scanf("%d%d%d",&a,&b,&c);
		a--,b--; //Vertices in the input were numbered starting from 1.
		adj[a].push_back(make_pair(c,b));
		adj[b].push_back(make_pair(c,a));
	}

	build_tree(0);	//Tree is rooted at an arbitrary node.
	init();

	int t;	//Number of queries
	scanf("%d",&t);

	while(t--){
		scanf("%d%d",&a,&b);
		a--,b--;
		c = query(a,b);
		printf("%d\n",c);
	}

	return 0;
}
