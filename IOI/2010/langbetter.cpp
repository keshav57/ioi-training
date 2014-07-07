#include <iostream>
#include <algorithm>
#include <cassert>
#include <set>
#include <string>
#include <cstring>
#include "grader.h"
#include <map>
#include <vector>

#define LANG 56
#define CHAR 65535
#define LEN 100
#define N LEN*10000

typedef unsigned long long lli;
using namespace std;

map<lli, int> ch;
map<pair<lli,int>, int> m2;

set<int> occ[N*4+10];
double score[LANG+10];
int tri[LEN*4+10];
double weight[N*4+10];
int n;

int seen[CHAR];
int tot[CHAR];

int ct,space;

void excerpt(int *E) {
	int i,j,sz;
	lli num;
	map<lli,int>::iterator it;
	map<pair<lli,int>,int>::iterator it2;

	++ct;
	for(i = 0 ; i < LEN; ++i){
		seen[E[i]] = ct;
	}

	for(i =0 ; i < LEN; ++i){
		tot[E[i]] += (seen[E[i]] == ct);
		if(tot[E[i]] == ct) space = E[i];
	}

	memset(score,0,sizeof(score));

	sz = 0;

	for(i =0 ; i+4 < LEN ;++i){
		num = ((1LL*E[i])<<48)|((1LL*E[i+1])<<32)|((1LL*E[i+2])<<16)|E[i+3];
		it2 = m2.find(make_pair(num,E[i+4]));
		if(it2 == m2.end()){
			m2.insert(make_pair(make_pair(num,E[i+4]),n++));
			it2 = m2.find(make_pair(num,E[i+4]));
			weight[it2->second] = 10;
		}

		j = it2->second;
		tri[sz++] = j;
	}

	for(i =0 ; i+3 < LEN ;++i){
		if(E[i+1] == space || E[i+2] == space) continue;
		num = ((1LL*E[i])<<48)|((1LL*E[i+1])<<32)|((1LL*E[i+2])<<16)|E[i+3];
		it = ch.find(num);
		if(it == ch.end()){
			ch.insert(make_pair(num,n++));
			it = ch.find(num);
			weight[it->second] = 2.25;
		}

		j = it->second;
		tri[sz++] = j;
	}

	for(i =0 ; i+2 < LEN ;++i){
		if(E[i+1] == space) continue;
		num = ((1LL*E[i])<<32)|((1LL*E[i+1])<<16)|E[i+2];
		it = ch.find(num);
		if(it == ch.end()){
			ch.insert(make_pair(num,n++));
			it = ch.find(num);
			weight[it->second] = 1;
 		}

		j = it->second;
		tri[sz++] = j;
	}

	for(i =0 ; i+1 < LEN ;++i){
//		if(E[i] == space || E[i+1] == space) continue;
		num = ((1LL*E[i])<<16)|E[i+1];
		it = ch.find(num);
		if(it == ch.end()){
			ch.insert(make_pair(num,n++));
			it = ch.find(num);
			weight[it->second] = 0.50;
 		}

		j = it->second;
		tri[sz++] = j;
	}

	sort(tri,tri+sz);
	sz = unique(tri,tri+sz)-tri;

	for(i =0 ; i < sz; ++i){
		j = tri[i];
		for(set<int>::iterator i2 = occ[j].begin(); i2 != occ[j].end(); ++i2){
			score[*i2] += weight[j];
		}
	}

	int l = max_element(score,score+LANG)-score;

	j = language(l);

	for(i =0 ; i < sz; ++i){
		occ[tri[i]].insert(j);
	}

}

