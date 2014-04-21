/*
 Created By: Malvika Joshi
 Problem: Flood-It (IOITC-2012 Final-3)
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>

#define WID 2000
#define N_MAX 52
#define COL 6
#define MOVE_MAX 2510

using namespace std;

typedef vector<string> vs;

int N;
const int adj[4][2] = { {0,1} , {1,0}, {0,-1}, {-1,0} };
char visited[N_MAX][N_MAX];

int visit(vs &board, int i, int j, char col){
	if(i < 0 || j < 0 || i >= N || j >= N) return 0;
	if(visited[i][j]) return 0;
	if(board[i][j] != col) return 0;

	visited[i][j] = 1;
	for(int k = 0; k < 4; ++k) visit(board,i+adj[k][0],j+adj[k][1],col);

	return 1;
}

void fill(vs &board, int i, int j, char src, char tar){
	if(i < 0 || j < 0 || i >= N || j >= N) return;
	if(board[i][j] != src) return;
	board[i][j] = tar;
	for(int k = 0; k < 4; ++k) fill(board,i+adj[k][0],j+adj[k][1],src,tar);
}

int conn_comp(vs &board){
	int i,j,con;
	con= 0;
	memset(visited,0,N_MAX*N_MAX);
	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			con += visit(board,i,j,board[i][j]);
		}
	}
	return con;
}

vs Q[WID+10];
string moves[WID+10];
vs wait[WID*5+10];
string tmp[WID*5+10];
pair<int,int> priority[WID*5+10];
int W,T;

string bfs(vs &board){
	int i,col,org,conn;

	Q[T++] = board;

	do{

		W = 0;
		for(i = 0; i < T; ++i){

			org = conn_comp(Q[i]);

			for(col = 0; col < COL; ++col){
				if(col+'A' == Q[i][0][0]) continue;
				wait[W] = Q[i];
				tmp[W] = moves[i];
				fill(wait[W],0,0,Q[i][0][0],col+'A');
				tmp[W].push_back(col+'A');

				conn = conn_comp(wait[W]);
				if(conn >= org) continue;

				priority[W] = make_pair(conn,W);
				++W;
			}
		}

		sort(priority,priority+W);

		T = 0;
		for(i = 0; i < W && i < WID; ++i){
			if(priority[i].first == 1) return tmp[priority[i].second];
			Q[T] = wait[priority[i].second];
			moves[T] = tmp[priority[i].second];
			++T;
		}

		if(!T) return "NO MOVES";


	} while(moves[0].length() < MOVE_MAX);

	return "NOT FOUND";
}

int main(){

	int i;
	string tmp;

	vs board;

	scanf("%d",&N);

	for(i = 0; i < N; ++i){
		cin >> tmp;
		board.push_back(tmp);
	}

	cout << bfs(board) << "\n";

	return 0;
}
