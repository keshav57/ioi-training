#include <algorithm>
#include <map>
#include <iostream>
#include <cstdio>
#include <utility>


#define NMAX 1000100

#define x first
#define y second

using namespace std;

typedef pair<int,int> point;

point src;
point pos[NMAX];
int type[NMAX];

int compare(int a, int b){
	long long q1,q2;

	q1 = 1LL*(pos[a].y-src.y)*(pos[b].x-src.x);
	q2 = 1LL*(pos[b].y-src.y)*(pos[a].x-src.x);

	return q1 == q2 ? type[a] < type[b] : q1 < q2;
}

/*
 mirror st = -2
 sc st = -1
 crystal = i
 sc en = NMAX
 mir en =  NMAX+1
*/
map<int,int> blocked;


int order[NMAX];
int lit[NMAX];
int L,P;

void compute(){
	int i,st;

	sort(order,order+P,compare);


	st = 0;
	for(i = 0; i < P; ++i){

		if(type[order[i]] == -2){
			st = 1;
			continue;
		}
		if(type[order[i]] > NMAX){
			break;
		}

		if(type[order[i]] == NMAX){
			blocked[pos[order[i]].x]--;
			if(!blocked[pos[order[i]].x]) blocked.erase(pos[order[i]].x);
			continue;
		}
		if(type[order[i]] < 0){
			blocked[pos[order[i]].x]++;
			continue;
		}

		if(st && (blocked.empty() || pos[order[i]].x < blocked.begin()->first)){
			lit[L++] = type[order[i]];
		}
	}

}

int S,C;

int main(){
	int i;
	point tmp;

	scanf("%d%d",&src.x,&src.y);

	src.y = -src.y;		//reflect

	tmp.y = 0;
	scanf("%d",&tmp.x);
	pos[P] = tmp;
	type[P++] = NMAX+1;

	scanf("%d",&tmp.x);
	pos[P] =tmp;
	type[P++] = -2;

	order[1] = 1;
	sort(order,order+P,compare);

	scanf("%d%d",&S,&C);

	while(S--){

		scanf("%d%d",&tmp.x,&tmp.y);

		pos[P] = tmp;
		type[P++] = -1;

		pos[P] = make_pair(tmp.x,-tmp.y);
		type[P++] =NMAX;


		scanf("%d",&tmp.y);

		pos[P] = tmp;
		type[P++] = NMAX;

		pos[P] = make_pair(tmp.x,-tmp.y);
		type[P++] = -1;
	}

	for(i = 0; i < C; ++i){
		scanf("%d%d",&tmp.x,&tmp.y);
		pos[P] = tmp;
		type[P++] = i;
	}

	for(i = 0; i < P; ++i){
		order[i] = i;
	}

	compute();


	printf("%d\n",L);
	sort(lit,lit+L);
	for(i = 0; i < L; ++i){
		printf("%d\n",lit[i]+1);
	}

	return 0;
}
