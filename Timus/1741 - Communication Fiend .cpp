/*
 Created By: Malvika Joshi
 Problem: Communication Fiend
 Link: http://acm.timus.ru/problem.aspx?space=1&num=1741
*/

#include <cstdio>
#include <vector>
#include <algorithm>

#define MAXN 10010
#define INF 100000000000LL

using namespace std;
typedef long long lli;

struct pkg{
	int end,typ;
	lli size;
};

pkg make_pkg(int end, char typ, lli size){
	pkg r;
	r.end = end;
	r.typ = typ == 'C' ? 2 : typ == 'L';
	r.size = (lli)size;
	return r;
}

vector<pkg> upd[MAXN];
lli down[MAXN][2];
int N,M;

lli DP(){

	int i,k;

	for(i = 1; i < N; ++i) down[i][0] = down[i][1] = INF;

	for(i = 0; i < N-1; ++i){
		for(k = 0; k < (int)upd[i].size(); ++k){
			if(upd[i][k].typ == 0){
				down[upd[i][k].end][0] = min(down[upd[i][k].end][0],
						min(down[i][0],down[i][1])+upd[i][k].size);
			}

			else if(upd[i][k].typ == 1){
				down[upd[i][k].end][1] = min(down[upd[i][k].end][1],
						down[i][1] + upd[i][k].size);
			}

			else{
				down[upd[i][k].end][1] = min(down[upd[i][k].end][1],
						down[i][1]+upd[i][k].size);

				down[upd[i][k].end][0] = min(down[upd[i][k].end][0],
						min(down[i][0],down[i][1])+upd[i][k].size);
			}

		}
	}

	return min(down[N-1][0],down[N-1][1]);
}

int main(){

	int i,st,en,si;
	char typ[10];

	scanf("%d%d",&N,&M);

	for(i = 0; i < M; i++){
		scanf("%d%d%d%s",&st,&en,&si,typ);
		--st,--en;
		upd[st].push_back(make_pkg(en,typ[0],si));
	}

	lli sol = DP();
	if(sol >= INF){
		printf("Offline\n");
	}else{
#ifdef WINDOWS
		printf("Online\n%I64d\n",sol);
#else
		printf("Online\n%lld\n",sol);
#endif
	}

	return 0;
}


