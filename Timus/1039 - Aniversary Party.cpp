/*
 Created By: Malvika Joshi
 Problem: Aniversary Party
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1039
*/

#include <stdio.h>
#include <vector>

inline int max(int a, int b){ return a > b ? a : b; }

typedef struct{
	int sel,nsel,parent;
	std::vector<int> C;
}node;

node T[6010];
int N;

void dfs(int root){
	int i,n,k;
	n = T[root].C.size();

	for(i = 0;i < n; i++){
		 k = T[root].C[i];
		 dfs(k);
		 T[root].sel += T[k].nsel;
		 T[root].nsel += max(T[k].sel,T[k].nsel);
	}

}

int get_sel(){
	int i;
	for(i = 0;i < N; i++){
		if(T[i].parent == i) break;
	}

	dfs(i);

	return max(T[i].sel,T[i].nsel);
}

int main(){
	int i,l,k;

	scanf("%d",&N);

	for(i = 0;i < N; i++){
		scanf("%d",&T[i].sel);
		T[i].nsel = 0;
		T[i].parent = i;
	}

	for(i = 0;i < N-1;i ++){
		scanf("%d%d",&l,&k);
		l--;
		k--;
		T[k].C.push_back(l);
		T[l].parent = k;
	}

	printf("%d",get_sel());

	return 0;
}
