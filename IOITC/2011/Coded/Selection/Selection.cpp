/*
 Created By: Malvika Joshi
 Problem: Selection (IOITC-2011 Final-1)
*/

#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdlib>

#define MAXN 1000010

using namespace std;

int fair[MAXN];

vector<int> children[MAXN];
int par[MAXN];
char node_sel[MAXN];
int weight[MAXN];

int subtree_sel[MAXN];
pair<int,int> min_weight[MAXN];

int N,S,sum;

int Q[MAXN];
int order[MAXN];
int H,T;

void create_order(){
    int n,i,v;

   Q[T++] = 0;

    n = 0;
    while(H < T){
        v = Q[H++];
        order[n++] = v;
        for(i = 0; i < children[v].size(); ++i){
            Q[T++] = children[v][i];
        }
    }

}

int gcd(int a, int b){
    int t;

    while(b){
        t = b;
        b = a%b;
        a = t;
    }

    return a;
}


void init(){

	unsigned i;
	int v,k;

    for(k = N-1; k >= 0; --k){
       v = order[k];

        min_weight[v] = make_pair(weight[v],v);

        for(i = 0; i < children[v].size(); ++i){
       //     init(children[v][i]);
            subtree_sel[v] += subtree_sel[children[v][i]];
            min_weight[v] = min(min_weight[v],min_weight[children[v][i]]);
        }

        if(subtree_sel[v] > 1 && node_sel[v]){
            printf("NO\n");
            exit(0);
        }

        if(subtree_sel[v] || !node_sel[v]) continue;

        subtree_sel[v] = 1;
        sum += min_weight[v].first;
        fair[S++] = min_weight[v].second;
	}
}


int main(){

	int typ,i,n;

	scanf("%d",&N);

	for(i = 0; i < N; ++i) 	scanf("%d",&weight[i]);

	for(i = 1; i < N; ++i){
		scanf("%d",&par[i]);
		children[--par[i]].push_back(i);
	}

	scanf("%d",&n);
	while(n--){
		scanf("%d",&i);
		++node_sel[i-1];
	}

	scanf("%d",&typ);

    create_order();
	init();

	printf("YES\n");
	if(typ == 1) return 0;

	if(typ == 2 || typ == 4) printf("%d\n",sum);
	else{
        int g = gcd(sum,S);
        printf("%d %d\n",sum/g,S/g);
    }

	if(typ < 4) return 0;

	sort(fair,fair+S);
	printf("%d",S);
	for(i = 0; i < S; ++i) printf(" %d",fair[i]+1);
	printf("\n");

	return 0;
}
