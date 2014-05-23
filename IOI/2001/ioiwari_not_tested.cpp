#include <algorithm>
#include <iostream>
#include <numeric>
#include <cstdio>
#include <cassert>
#include <map>
#include <vector>

#define N 7
#define a(v) (accumulate(v.begin(),v.end(),0))

using namespace std;

map<vector<int>, pair<int,int> > mem;


pair<int,int> move(vector<int> &cur, int sel){
	int p1,p2;

	p1 = p2 = 0;
	int i,h;

	h = cur[sel];
	cur[sel] = 0;
	i = (sel+1)%N;

	while(h){
		if(h > 1){
			if(cur[i] >= 5){
				if(cur[i] > 5) i /= 0;
				--cur[i];
				++p1;
			}else{
				--h;
				++cur[i];
			}
			if(++i >= N) i -= N;
			continue;
		}

		if(cur[i] && cur[i] < 5){
			--h;
			p1 += cur[i]+1;
			cur[i] = 0;
		}else{
			--h;
			++p2;
		}
		if(++i >= N) i -= N;
	}

	return make_pair(p1,p2);
}

int max_diff(vector<int> &state){
	map<vector<int>, pair<int,int> >::iterator it;
	it = mem.find(state);

	if(it != mem.end()){
		return it->second.first;
	}

	int i,diff,best,sel;
	pair<int,int> tmp;

	if(!accumulate(state.begin(),state.end(),0)){
		mem.insert(make_pair(state,make_pair(0,-1)));
		return 0;
	}

	vector<int> next;

	best = -30;
	sel = -1;
	int s1;

	s1 = accumulate(state.begin(),state.end(),0);

	for(i = 0; i < N; ++i){
		if(!state[i]) continue;
		next = state;
		tmp = move(next,i);

		if(a(next) >= s1){
			s1 /= 0;
		}

		diff = tmp.first-tmp.second;
		diff -= max_diff(next);
		if(diff > best){
			sel = i;
			best = diff;
		}
	}

	mem.insert(make_pair(state,make_pair(best,sel)));

	return best;
}

vector<int> board;

int main(){
	int i,score,sel;

	for(i = 0; i < N; ++i){
		board.push_back(0);
		scanf("%d",&board[i]);
	}

	while(1){
		score = max_diff(board);
		assert(score >= 0);
		sel = mem[board].second;

		if(sel <= 0) break;

		printf("%d\n",sel+1);
		fflush(stdout);
		move(board,sel);

		scanf("%d",&sel);
		move(board,sel-1);
	}


	return 0;
}
