/*
 Created By: Malvika Joshi
 Problem: Sorted Vectors
*/

#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::pair<int,int> > col[500010];
std::vector<int> outgoing[1000010];
std::set<int> incoming[1000010];
int id[1000010] = {0};

int N,Cn,M;

void init(){

	int i,j,k;

	for(i = 0;i < M; i++){
		std::sort(col[i].begin(),col[i].end());
	}

	Cn = N;
	id[Cn] = 0;
	for(i = 0; i < M; i++){
		for(j = 0; j < N-1; j++){
			if(col[i][j].first == -1) continue;
			outgoing[col[i][j].second].push_back(Cn);
			incoming[Cn].insert(col[i][j].second);
			if(col[i][j].first != col[i][j+1].first){
				k = j+1;
				id[Cn] = col[i][k].second;
				outgoing[Cn].push_back(col[i][k].second);
				incoming[col[i][k].second].insert(Cn);
				k++;
				while(k < N && col[i][k].first == col[i][k-1].first){
					outgoing[Cn].push_back(col[i][k].second);
					incoming[col[i][k].second].insert(Cn);
					id[Cn] = std::min(id[Cn],col[i][k].second);
					k++;
				}
				Cn++;
			}
		}
		Cn++;
	}

}

int L[1000010];
int l = 0;
std::set<std::pair<int,int> > S;

int topsort(){

	int i,n,m;

	std::set<std::pair<int,int> >::iterator it;

	for(i = 0;i < Cn; i++){
		if(incoming[i].size() == 0){
			S.insert(std::make_pair(id[i],i));
		}
	}

	while(S.size() > 0){
		it = S.begin();
		n = (*it).second;
		S.erase(S.begin());
		if(n < N) L[l++] = n;
		while(outgoing[n].size() > 0){
			m = outgoing[n].back();
			outgoing[n].pop_back();
			incoming[m].erase(n);
			if(incoming[m].size() == 0) S.insert(std::make_pair(id[m],m));
		}
	}

	for(i = 0;i < Cn; i++){
		if(incoming[i].size() > 0 || outgoing[i].size() > 0){
			return 0;
		}
	}

	return 1;
}

int main(){

	int i,j,x;

	scanf("%d%d",&N,&M);

	for(i =0 ;i < N; i++){
		for(j = 0;j < M; j++){
			scanf("%d",&x);
			col[j].push_back(std::make_pair(x,i));
		}
		id[i] = i;
	}

	init();

	if(topsort()){
		printf("YES\n");
		for(i = 0;i < l; i++) printf("%d ",L[i]+1);
	}else{
		printf("NO\n");
	}



	return 0;
}
