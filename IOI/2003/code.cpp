#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <string>
#include <map>

#define NMAX 1010
#define INF (1e4)

using namespace std;

pair<int,int> next0[NMAX][3];
pair<int,int> next1[NMAX][3];

string code0[NMAX][3];
string code1[NMAX][3];
int N,M,V0,V1;

int max_extend[NMAX][NMAX][3];
int lcs[NMAX][NMAX];

map<string,pair<int,int> > occ;

void init(){

	int i,b;
	map<string,pair<int,int> >::iterator it;

	for(i = M-1;  i >= 0; --i){
		for(b = 0 ; b < 3; ++b){
			it = occ.find(code0[i][b]);
			next0[i][b] = it == occ.end() ? make_pair(max(M,N)-i,2) : make_pair(it->second.first-i,it->second.second);
//			cout << code0[i][b] << " " << i+next0[i][b].first << "," << next0[i][b].second << " ";
		}

//		cout << endl;

		for(b = 0; b < 3; ++b){
			occ[code0[i][b]] = make_pair(i,b);
		}
	}
//	cout << endl;

	occ.clear();
	for(i = N-1;  i >= 0; --i){
		for(b = 0 ; b < 3; ++b){
			it = occ.find(code1[i][b]);
			next1[i][b] = it == occ.end() ? make_pair(max(M,N)-i,2) : make_pair(it->second.first-i,it->second.second);
//			cout << code1[i][b] << " " << i+next0[i][b].first << "," << next0[i][b].second << " ";
		}
//		cout << endl;

		for(b = 0; b < 3; ++b){
			occ[code1[i][b]] = make_pair(i,b);
		}
	}

//	cout <<endl;
}

void extend(){
	int i,j,b,r,k,l;

	for(i = M-1; i >= 0; --i){
		for(j = N-1; j >= 0; --j){
			for(b = 0; b < 2; ++b){
				max_extend[i][j][b] = INF;

				//i j don't match
				if((code0[i][0] == code0[i][1]) != (code1[j][b] == code1[j][!b])) max_extend[i][j][b] = -INF;
				if((code0[i][0] == code0[i][2]) != (code1[j][b] == code1[j][2])) max_extend[i][j][b] = -INF;
				if((code0[i][1] == code0[i][2]) != (code1[j][!b] == code1[j][2])) max_extend[i][j][b] = -INF;

				for(k = 0; k < 3; ++k){
					l = k == 2 ? k : (b^k);

					if(next0[i][k].first^next1[j][l].first){
						max_extend[i][j][b] = min(max_extend[i][j][b], min(next0[i][k].first,next1[j][l].first));
						continue;
					}

					if((next0[i][k].second==2)^(next1[j][l].second==2)){
						max_extend[i][j][b] = min(max_extend[i][j][b], next0[i][k].first);
						continue;
					}

					r = next0[i][k].second == 2 ? 2 : next0[i][k].second^next1[j][l].second;

					max_extend[i][j][b] = min(max_extend[i][j][b],
							next0[i][k].first + max_extend[i+next0[i][k].first][j+next1[j][l].first][r]);
				}
			}
			max_extend[i][j][b] = max(max_extend[i][j][0],max_extend[i][j][1]);
//			cout << i << " " << j << " " << max_extend[i][j][b] << endl;
		}

//		cout << endl;
	}
}

int dp(){
	int i,j,len;

	len = 0;

	for(i = M-1; i >= 0; --i){
		for(j = N-1; j >= 0; --j){
			lcs[i][j] = min(lcs[i+1][j+1]+1,max_extend[i][j][2]);
			lcs[i][j]= max(lcs[i][j],0);
			len = max(len, lcs[i][j]);
		}
	}

	return len;
}

/*
4 3
RA = RB + RC
RC = D + RE
RF = RF + RJ
RE = RF + RF
HD = HE + HF
HM = HN + D
HN = HA + HB

*/

int main(){

	int i;
	char c;

	ios_base::sync_with_stdio(false);

	cin >> M >> N;

	for(i = 0; i < M; ++i){
		cin >> code0[i][2] >> c;
		cin >> code0[i][1] >> c;
		cin >> code0[i][0];
	}

	for(i = 0; i < N; ++i){
		cin >> code1[i][2] >> c;
		cin >> code1[i][1] >> c;
		cin >> code1[i][0];
	}

	init();
	extend();

	cout << dp() << endl;

	return 0;
}
