#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>

#define N 25

using namespace std;

int mem[6][6][6][6][6];

int ways(int *filled, char ch){
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

char str[N+5];

void cons(int k, int *filled, char ch){
	if(ch >= 'Z'){
		return;
	}

	int i,val;

	for(i = 0; i < 5; ++i){
		if(filled[i] >= 5) continue;
		if(i && filled[i] == filled[i-1]) continue;
		++filled[i];
		val = ways(filled,ch+1);
		--filled[i];
		if(k < val){
			break;
		}
		k -= val;
	}

	assert(i < 5);
	str[5*i+filled[i]] = ch;
	++filled[i];
	cons(k,filled,ch+1);
	--filled[i];
}

int get_val(int *filled, int ch){
	if(ch >= 'Z') return 1;

	int i,val;

	val = 0;
	for(i = 0; i < 5; ++i){
		if(filled[i] >= 5) continue;
		if(i && filled[i] == filled[i-1]) continue;

		if(str[5*i+filled[i]] == ch) break;
		++filled[i];
		val += ways(filled,ch+1);
		--filled[i];
	}

	assert(i < 5);

	++filled[i];
	val += get_val(filled,ch+1);
	--filled[i];

	return val;
}

int filled[5];

int main(){
	int i;
	char typ;

	memset(mem,-1,sizeof(mem));
	ways(filled,'A');

	scanf(" %c",&typ);

	if(typ == 'W'){
		scanf("%s",str);
		printf("%d\n",get_val(filled,'A'));
	}else{
		scanf("%d",&i);
		cons(i-1,filled,'A');
		printf("%s\n",str);
	}

	return 0;
}
