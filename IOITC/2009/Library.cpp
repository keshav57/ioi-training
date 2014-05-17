#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>

#define NMAX 40010
#define SQRT 310

using namespace std;

vector<int> lists[SQRT*2];
int next[SQRT*2];
int prev[SQRT*2];
int inc[SQRT*2];

int A[NMAX];
int L,N,st,en;

void print_list(){
	int i,j,h,t;

	for(i = next[st]; i != en; i = next[i]){
		h = inc[i] > 0 ? 0 :  lists[i].size()-1;
		t = inc[i] > 0 ? lists[i].size()-1 : 0;

		for(j = h; j != t+inc[i]; j += inc[i]){
			cout << lists[i][j]+1 << " ";
		}

//		cout << endl;
		//	assert(k <= N);
	}
	cout << endl;
}

void create_list(){
	int i,j,k,h,t;

	k = 0;

//	cout << "1" << endl;
	int visited[NMAX] = {0};

	if(L){
		for(i = next[st]; i != en; i = next[i]){
			assert(!visited[i]);
			visited[i] = 1;
			h = inc[i] > 0 ? 0 :  lists[i].size()-1;
			t = inc[i] > 0 ? lists[i].size()-1 : 0;

			for(j = h; j != t+inc[i]; j += inc[i]){
				A[k++] = lists[i][j];
			}
			//	assert(k <= N);
		}
	}

	while(L--){
		lists[L].clear();
	}

	L = 1;
	st = 0;
	inc[st] = 1;
	next[st] = 1;
	prev[st] = -1;
	for(i = 0; i < N; ++i){
		for(k = 1; k*k <= N && i+k <= N; ++k){
			lists[L].push_back(A[i+k-1]);
		}
		i = i+k-2;
		next[L] = L+1;
		prev[L] = L-1;
		inc[L] = 1;
		++L;
	}
	en = L;
	++L;
	inc[en] = 1;
	prev[en] = en-1;
	next[en] = -1;
}

pair<int,int> find(int idx){
	int i;

	for(i = next[st]; i != en; i = next[i]){
//		cout << i << " " << lists[i].size() << " " << inc << endl;
		if(lists[i].size() <= idx){
			idx -= lists[i].size();
			continue;
		}
		if(inc[i] < 0) idx = lists[i].size()-idx-1;
		break;
	}

	return make_pair(i,idx);
}

void reverse(int i, int j){
	pair<int,int> tmp;
	int li,lj,posi,posj,k,h,t;

	tmp = find(i);
	li = tmp.first,posi = tmp.second;
	tmp = find(j);
	lj = tmp.first,posj = tmp.second;

//	cout << posi << " " << posj << " " << li << " " << lj << endl;

	while(posj < lists[lj].size() && posj >= 0 && posi < lists[li].size() && posi >= 0){
		if(li == lj && posi*inc[li] >= posj*inc[lj]) break;
		swap(lists[lj][posj],lists[li][posi]);
		posj -= inc[lj];
		posi += inc[li];
	}


//	cout << posi << " " << posj << " " << li << " " << lj << endl;

	vector<int> t1,t2;

	if(li != lj && posj < lists[lj].size() && posj >= 0){
		posj += inc[lj];

		h = inc[lj] > 0 ? 0 : lists[lj].size()-1;
		t = inc[lj] > 0 ? lists[lj].size()-1 : 0;

		for(k = h; k != posj; k += inc[lj]){
			t1.push_back(lists[lj][k]);
		}

		for(k = posj; k != t+inc[lj]; k += inc[lj]){
			t2.push_back(lists[lj][k]);
		}

		lists[lj] = t2;
		lists[L] = t1;
		inc[L] = 1;
		inc[lj] = 1;

		next[L] = lj;
		prev[L] = prev[lj];

		next[prev[lj]] = L;
		prev[lj] = L;
		++L;
	}

	else if(li != lj && posi < lists[li].size() && posi >= 0){
		h = inc[li] > 0 ? 0 :  lists[li].size()-1;
		t = inc[li] > 0 ? lists[li].size()-1 : 0;

		for(k = h; k != posi; k += inc[li]){
			t1.push_back(lists[li][k]);
		}

		for(k = posi; k != t+inc[li]; k += inc[li]){
			t2.push_back(lists[li][k]);
		}

		lists[li] = t1;
		lists[L] = t2;
		inc[L] = 1;
		inc[li] = 1;

		prev[L] = li;
		next[L] = next[li];

		prev[next[li]] = L;
		next[li] = L;
		++L;
	}


//	print_list();

	if(li != lj && next[li] != lj){
		prev[next[li]] = lj;
		next[prev[lj]] = li;
		swap(next[li],prev[lj]);
	}

	int visited[NMAX] = {0};
	if(li != lj){
		for(k = next[li]; k != lj; k = next[k]){
			assert(!visited[k]);
			visited[k] = 1;
			swap(next[k],prev[k]);
			inc[k] *= -1;
		}
	}
}

int Q;

/*
 10
1 7 8
*/

int main(){
	int i,k,t,j;
	pair<int,int> tmp;

	scanf("%d",&N);

	for(i =0 ; i < N; ++i) A[i] = i;
	create_list();

	k = 0;

	t = 0;
	while(1){

		scanf("%d",&t);

		if(t == 3){
			print_list();
			continue;
		}

		if(t == 2) break;

		scanf("%d",&i);
		if(t) scanf("%d",&j);

		--i,--j;
		if(t){
			reverse(i,j);
		}else{
			tmp = find(i);
			printf("%d\n",lists[tmp.first][tmp.second]+1);
		}

		++k;
		if(k*k >= N){
			k = 0;
			create_list();
		}
	}

	return 0;
}
