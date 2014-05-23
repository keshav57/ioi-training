#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>

#define N 25
#define VMAX 300
#define pq(v) printq(v);

using namespace std;

int mem[6][6][6][6][6];

int ways(vector<int> &filled, char ch){
	int &val = mem[filled[0]][filled[1]][filled[2]][filled[3]][filled[4]];
	if(val >= 0) return val;

	if(ch >= 'Z'){
		val = 1;
		return val;
	}

	int k;
	val = 0;

	for(k = 0; k < 5; ++k){
		if(filled[k] >= 5) continue;
		if(k && filled[k] == filled[k-1]) continue;
		++filled[k];
		val += ways(filled,ch+1);
		--filled[k];
	}

	return val;
}

int pos[6][6][6][6][6];

vector<int> Q[VMAX];
int H,T;

char pref[N+2];
char str[N+2];
int row[N+2];

vector<int> states[VMAX];
int S;

void bfs(vector<int> &src, int size){
	assert(size);

	vector<int> v,u;
	int i,c;

	H = T = S = 0;
	memset(pos,0,sizeof(pos));

	Q[T++] = src;
	pos[src[0]][src[1]][src[2]][src[3]][src[4]] = 1;

	while(H < T){

		v = Q[H++];
		c = accumulate(v.begin(),v.end(),0);

		if(c >= size){
			states[S++] = v;
			continue;
		}

		if(row[c] >= 0){											//if c is a part of the prefix then its posiition is fixed
			if(v[row[c]] >= 5) continue;
			if(row[c] && v[row[c]] == v[row[c]-1]) continue;
			u = v;
			++u[row[c]];

			if(pos[u[0]][u[1]][u[2]][u[3]][u[4]]){
				pos[u[0]][u[1]][u[2]][u[3]][u[4]] += pos[v[0]][v[1]][v[2]][v[3]][v[4]];
				continue;
			}

			pos[u[0]][u[1]][u[2]][u[3]][u[4]] += pos[v[0]][v[1]][v[2]][v[3]][v[4]];
			Q[T++] = u;
			continue;
		}

		for(i = 0; i < 5; ++i){
			if(v[i] >= 5) continue;
			if(i && v[i-1] == v[i]) continue;
			if(pref[i*5+v[i]]) continue;
			u = v;
			u[i]++;

			if(pos[u[0]][u[1]][u[2]][u[3]][u[4]]){
				pos[u[0]][u[1]][u[2]][u[3]][u[4]] += pos[v[0]][v[1]][v[2]][v[3]][v[4]];
				continue;
			}

			pos[u[0]][u[1]][u[2]][u[3]][u[4]] += pos[v[0]][v[1]][v[2]][v[3]][v[4]];
			Q[T++] = u;
		}
	}
}

void printq(vector<int> &st){
	int i;
	for(i = 0; i < 5; ++i){
		cout << st[i] << " " ;
	}
	cout << endl;
}

int extend(char last){
	int i,ct,tmp;

	ct = 0;
	for(i = 0; i < S; ++i){
		tmp = (ways(states[i],last)*pos[states[i][0]][states[i][1]][states[i][2]][states[i][3]][states[i][4]]);
		ct += tmp;
	}

	return ct;
}

int compute_rank(){
	int i,rank;
	char c,pl;
	vector<int> st;

	st.resize(5,0);
	memset(pref,0,N+2);
	memset(row,-1,sizeof(row));

	rank = 0;
	pl = -1;
	for(i = 0; i < N; ++i){
		for(c = 'A'; c < str[i]; ++c){
			if(i >= 5 && pref[i-5] >= c) continue;
			if(i%5 && pref[i-1] >= c) continue;
			if(row[c-'A'] >= 0) continue;

			pref[i] = c;
			row[c-'A'] = i/5;
			bfs(st,max(pl,c)-'A'+1);
			rank += extend(max(pl,c)+1);
			pref[i] = 0;
			row[c-'A'] = -1;
		}
		pref[i] = str[i];
		row[str[i]-'A'] = i/5;
		pl = max(pl,str[i]);
	}

	return rank+1;
}

void compute_str(int k){
	int i,rank;
	char c,pl;
	vector<int> st;

	st.resize(5,0);

	memset(pref,0,N+2);
	memset(row,-1,sizeof(row));

	for(i = 0; i < N; ++i){
		for(c = 'A'; c < 'Z'; ++c){
			if(i >= 5 && pref[i-5] >= c) continue;
			if(i%5 && pref[i-1] >= c) continue;
			if(row[c-'A'] >= 0) continue;

			pref[i] = c;
			row[c-'A'] = i/5;
			bfs(st,max(pl,c)-'A'+1);
			rank = extend(max(pl,c)+1);
			pref[i] = 0;
			row[c-'A'] = -1;
			if(rank > k){
				break;
			}
			k -= rank;
		}
		assert(c < 'Z');
		pref[i] = c;
		row[c-'A'] = i/5;
		pl = max(pl,c);
	}
}

int main(){

	char c;
	int k;

	//701149020

	memset(mem,-1,sizeof(mem));

	scanf("%c",&c);
	if(c == 'N'){
		scanf("%d",&k);
		compute_str(k-1);
		printf("%s\n",pref);
	}else{
		scanf("%s",str);
		printf("%d\n",compute_rank());
	}
	return 0;
}
