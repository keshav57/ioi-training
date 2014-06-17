#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>

#define LARGE 400
#define st first
#define en second
#define NMAX 200000
#define RMAX 25000

using namespace std;

int sttime[NMAX];
int ftime[NMAX];

int region[NMAX];

pair<int,int> all[NMAX];			//second is reg
pair<int, pair<int,int> > all_ranges[NMAX*2];

//end is always open

vector<int> of_region[NMAX];
vector<pair<int,int> > reg_ranges[RMAX];

int large_r1[510][RMAX];
int large_r2[RMAX][510];

int N,R,L;

int large[RMAX];
int idx[RMAX];

void gen_large(){
	int reg,i,k,sum;

	for(reg = 0; reg < R; ++reg){
		if(!large[reg]) continue;
		idx[reg] = L;

		k = 0;
		sum = 0;
		for(i = 0; i < N; ++i){
			while(k < reg_ranges[reg].size() && reg_ranges[reg][k].first <= all[i].first){
				sum += reg_ranges[reg][k].second;
				++k;
			}
			large_r1[L][all[i].second] += sum;
		}
		++L;
	}

	for(reg = 0; reg < R; ++reg){
		if(!large[reg]) continue;
		L = idx[reg];

		k = 0;

		for(i = 0; i < N*2; ++i){
			while(k < of_region[reg].size() && of_region[reg][k] < all_ranges[i].first){
				++k;
			}
			large_r2[all_ranges[i].second.second][L] -= k*all_ranges[i].second.first;
		}
	}

}

vector<int> child[NMAX];
int cur_time;

void dfs(int v){
	int i;

	sttime[v] = cur_time++;

	for(i =0 ; i < child[v].size(); ++i){
		dfs(child[v][i]);
	}

	ftime[v] = cur_time;
}

int ct[NMAX];

void init(){
	int reg,i;
	dfs(0);

//	for(i =0 ; i < N; ++i){
//		cout << sttime[i] << " " << ftime[i] << endl;
//	}

	for(i = 0; i < N; ++i){
		reg = region[i];
		all[i] = make_pair(sttime[i],reg);
		all_ranges[i*2] = make_pair(sttime[i], make_pair(1,reg) );
		all_ranges[i*2+1] = make_pair(ftime[i], make_pair(-1,reg) );

		reg_ranges[reg].push_back(make_pair(sttime[i],1));
		reg_ranges[reg].push_back(make_pair(ftime[i],-1));
		of_region[reg].push_back(sttime[i]);
		++ct[reg];
	}

	sort(all,all+N);
	sort(all_ranges,all_ranges+N*2);

	for(reg = 0; reg < R; ++reg){
		large[reg] = ct[reg] >= LARGE;
		sort(reg_ranges[reg].begin(),reg_ranges[reg].end());
		sort(of_region[reg].begin(),of_region[reg].end());
	}

	gen_large();
}


int compute(int r1, int r2){
	int i,k,sum,tot;


	k = 0;
	sum = 0;
	tot = 0;
	for(i = 0; i < of_region[r2].size(); ++i){
		while(k < reg_ranges[r1].size() && reg_ranges[r1][k].first <= of_region[r2][i]){
			sum += reg_ranges[r1][k].second;
			++k;
		}
		tot += sum;
	}
	return tot;
}

int main(){
	int i,q,p;

	scanf("%d%d%d",&N,&R,&q);

	scanf("%d",&region[0]);
	--region[0];
	for(i = 1; i < N; ++i){
		scanf("%d%d",&p,&region[i]);
		--region[i];
		--p;
		child[p].push_back(i);
	}

	init();

	int r1,r2;
	while(q--){
		scanf("%d%d",&r1,&r2);
		--r1,--r2;
		if(large[r1]){
			printf("%d\n",large_r1[idx[r1]][r2]);
		}else if(large[r2]){
			printf("%d\n",large_r2[r1][idx[r2]]);
		}else{
			printf("%d\n",compute(r1,r2));
		}
	}

	return 0;
}
