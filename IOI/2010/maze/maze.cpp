#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>

#define SEL 400
#define x first
#define y second

using namespace std;

typedef vector<string> vs;

const pair<int,int> adj[4] = { make_pair(0,1), make_pair(0,-1), make_pair(1,0), make_pair(-1,0) };

vs Q[SEL+10];
pair<int,int> core[SEL+10];
int T,C;

vs extend[SEL*4+10];
pair<int,int> c2[SEL*4+10];
int order[SEL*4+10];
int block[SEL*4+10];

int compare(int a, int b){
	return block[a] == block[b] ? a%7 < b%7 : block[a] > block[b];
}

int visited[210][210];
int N,M,len;

int dfs(vs &A, int i, int j){
	if(i < 0 || j < 0 || i >= M || j >= N) return 0;
	if(A[i][j] != '#') return 0;
	if(visited[i][j]) return visited[i][j];
	visited[i][j] = -1;

	int ct,k;
	ct = 0;

	for(k =0; k < 4; ++k){
		ct = max(ct,dfs(A,adj[k].x+i,adj[k].y+j));
	}
	
	visited[i][j] = ct+1;

	return ct+1;
}

int get_block(vs &A, pair<int,int> out){
	memset(visited,0,sizeof(visited));
	A[out.x][out.y] = '#';
	int bl = dfs(A,out.x,out.y);
	A[out.x][out.y] = '.';
	return bl;
}



vs bfs(){
	int i,k,j;
	pair<int,int> out,ex,bl;

	while(T){

		++len;

		//first branch
		C = 0;
		for(i = 0; i < T; ++i){
			out = core[i];

			vs &F = Q[i];

			for(k = 0; k < 4; ++k){
				ex = make_pair(out.x+adj[k].x,out.y+adj[k].y);
				if(ex.x < 0 || ex.y < 0 || ex.x >= M || ex.y >= N || F[ex.x][ex.y] != '#') continue;

				extend[C] = F;
				extend[C][ex.x][ex.y] = '.';

				for(j = 0; j < 4; ++j){
					bl = make_pair(out.x+adj[j].x,out.y+adj[j].y);
					if(bl.x < 0 || bl.y < 0 || bl.x >= M || bl.y >= N || extend[C][bl.x][bl.y] == '.') continue;
					extend[C][bl.x][bl.y] = 'X';
				}
				order[C] = C;
				c2[C] = ex;
				block[C] = get_block(extend[C],c2[C]);
				++C;
			}	
		}

		if(!C) return Q[0];

		sort(order,order+C,compare);
		
 		//random_shuffle(order+C/2,order+C);
		//then them to queue
		T = 0;
		for(i = 0; i < C && i < SEL; ++i){
			Q[T] = extend[order[i]];
			core[T++] = c2[order[i]];
		}
	}


	cerr << "Failed\n";
	return Q[0];
}

int main(){
	int i,j,k;
	pair<int,int> bl;
	string str;
	vs field;

	ios_base::sync_with_stdio(0);

	while(cin >> str){
		field.push_back(str);
	}

	M = field.size();
	N = field[0].length();

	for(i = 0; i < M; ++i){
		for(j  = 0; j < N; ++j){
			if(i && j && i < M-1 && j < N-1) continue;
			if(T > SEL) break;
			if(field[i][j] == 'X') continue;
			Q[T] = field;
			Q[T][i][j] = '.';
			core[T++] = make_pair(i,j);
		}
	}

	for(k = 0; k < T; ++k){
		for(i = 0; i < M; ++i){
			for(j  = 0; j < N; ++j){
				if(i && j && i < M-1 && j < N-1) continue;
				if(Q[k][i][j] == '.') continue;
				Q[k][i][j] = 'X';
			}
		}
	}

	vs sol = bfs();

	for(i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			if(sol[i][j] ^ 'X') continue;
			sol[i][j]=field[i][j];
		}
	}

	for(i =0 ; i < M; ++i){
		cout << sol[i] << "\n";
	}

	return 0;
}

