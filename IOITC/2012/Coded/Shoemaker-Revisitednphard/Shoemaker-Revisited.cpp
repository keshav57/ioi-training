/*
 Created By: Malvika Joshi
 Problem: Shoemaker-Revisited (IOITC-2012 Test-11)
*/

#include <algorithm>
#include <cstdio>
#include <vector>

#define MAXN 210

using namespace std;

typedef long long lli;

vector<int> time[MAXN];
int weight[MAXN];
int index[MAXN];

lli pref[MAXN][MAXN];
lli finish[MAXN];

int N,M;

void init(){
	int i,k;

	for(i = 0; i < N; ++i) finish[i] = 0;

	for(k = 0; k < M; ++k){
		pref[k][0] = time[0][k];
		finish[0] = max(finish[0],pref[k][0]);

		for(i = 1; i < N; ++i){
			pref[k][i] = pref[k][i-1]+time[i][k];
			finish[i] = max(finish[i],pref[k][i]);
		}
	}

	for(i = 0; i < N; ++i){
//		printf("%lld ",finish[i]);
		finish[i] *= weight[i];
		if(i) finish[i] += finish[i-1];
	}
//	printf("\n");
}

lli tmp_pref[MAXN];

lli new_time(int j){
	int i;
	lli tot,f;

	tot = j-1 ? finish[j-2] : 0;
	f = 0;
	for(i = 0; i < M; ++i){
		if(j-1)tmp_pref[i] = pref[i][j-2]+time[j][i];
		else tmp_pref[i] = time[j][i];

		f = max(f,tmp_pref[i]);
	}

	tot += f*weight[j];

	f = 0;
	for(i = 0; i < M; ++i){
		tmp_pref[i] += time[j-1][i];
		f = max(f,tmp_pref[i]);
	}

	tot += f*weight[j-1];

	return tot;
}

lli new_time2(int j){
	lli tot,f;
	int i;

	f = 0;
	tot = finish[j];
	for(i = 0; i < M; ++i) f = max(f,pref[i][j]+time[j+1][i]);

	tot += (f*weight[j+1]);

	return tot;
}

void sort(){
	int i,j;
	lli t1,t2;


	for(i = 1; i < N; ++i){
		init();
//		printf("%lld\n",finish[i]);

		for(j = i-1; j >= 0; --j){
			t1 = new_time2(j);
			t2 = new_time(j+1);

//			printf("%d %d %lld %lld l\n",j,j+1,t1,t2);

			if(t2 < t1){
				swap(time[j],time[j+1]);
				swap(weight[j],weight[j+1]);
				swap(index[j],index[j+1]);
				continue;
			}
			break;
		}
	}
}

int main(){
	int i,j;

	scanf("%d%d",&N,&M);

	for(i = 0; i < N; ++i){
		index[i] = i;
		scanf("%d",&weight[i]);
		for(j = 0; j < M; ++j){
			time[i].push_back(0);
			scanf("%d",&time[i][j]);
		}
	}

	sort();
	sort();
	sort();
	sort();
	sort();
	sort();

	while(M--){
		for(i = 0; i < N; ++i) printf("%d ",index[i]+1);
		printf("\n");
	}
	return 0;
}
