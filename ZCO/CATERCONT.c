/*
 Created By: Malvika Joshi
 Problem: CATERCONT
 Link: http://opc.iarcs.org.in/index.php/problems/CATERCONT
*/

#include<stdio.h>

typedef struct{
	int neightbours[50];
	int n;
}vertex;

vertex V[100000];
int Y[100000],N[100000];
int visited[100000];
int V_n;

void dfs(int root){

    visited[root]=1;
    int i,len = V[root].n;

    for(i = 0;i < len;i++) {
        if(!visited[V[root].neightbours[i]]){
             dfs(V[root].neightbours[i]);
             Y[root] += N[V[root].neightbours[i]];
             N[root]+= Y[V[root].neightbours[i]] > N[V[root].neightbours[i]]? Y[V[root].neightbours[i]]: N[V[root].neightbours[i]];
         }
     }
}

int main(void){

    int ans,i,a,b;
    scanf("%d",&V_n);

   for(i = 0;i < V_n; i++){
	   N[i] = 0;
	   visited[i] = 0;
	   V[i].n = 0;
   }

    for(i = 0;i < V_n; i++){
       scanf("%d",&Y[i]);
    }

    for(i = 1;i < V_n; i++) {
       scanf("%d%d",&a,&b);
       a--;
       b--;
       V[a].neightbours[V[a].n] = b;
       V[a].n ++;
       V[b].neightbours[V[b].n] = a;
       V[b].n ++;
    }

    dfs(0);

    ans = Y[0] > N[0]? Y[0]:N[0];
    printf("%d",ans);
    return 0;
}
