/*
 Created By: Malvika Joshi
 Problem: lgame
 Link: http://cerberus.delos.com:791/usacoprob2?a=eAipUMKWO1o&S=lgame
*/

#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int taken[26] = {0};
string dict[40000];
int D = 0,N = 0,S =0;
string valid[40000];
pair<string,string> sol[40000];
int values[26] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};

int init(){
	int occ[26],add,i,j,n;

	for(i = 0; i < D; i++){
		memset(occ,0,sizeof(int)*26);
		add = 1;
		n = dict[i].length();
		for(j = 0; j < n; ++j){
			occ[dict[i][j]-'a']++;
			if(occ[dict[i][j]-'a'] > taken[dict[i][j]-'a']){
				add = 0;
				break;
			}
		}
		if(add){
			valid[N++] = dict[i];
		}
	}

	return N;
}


inline int value(string str){
	int val = 0,i,n;

	n = str.length();
	for(i = 0;i < n; ++i){
		val += values[str[i]-'a'];
	}
	return val;
}

inline int val_pair(string a, string b){
	int occ[26] = {0},val = 0, i,n;

	n = a.length();

	for(i = 0;i < n; ++i){
		occ[a[i]-'a']++;
		if(occ[a[i]-'a'] > taken[a[i]-'a']) return 0;
		val += values[a[i]-'a'];
	}

	n = b.length();

	for(i = 0;i < n; ++i){
		occ[b[i]-'a']++;
		if(occ[b[i]-'a'] > taken[b[i]-'a']) return 0;
		val += values[b[i]-'a'];
	}

	return val;
}

int find_pairs(){
	int max = 0,i,temp,j;

	for(i = 0; i < N; i++){

		temp = value(valid[i]);
		if(temp > max){
			max = temp;
			S = 0;
			sol[S++] = make_pair(valid[i],"#");
		}else if(temp == max){ sol[S++] = make_pair(valid[i],"#"); }

		for(j = i+1; j < N; j++){
			temp = val_pair(valid[i],valid[j]);
			if(temp > max){
				max = temp;
				S = 0;
				sol[S++] = make_pair(valid[i],valid[j]);
			}else if(temp == max){ sol[S++] = make_pair(valid[i],valid[j]); }
		}
	}

	sort(sol,sol+S);

	return max;
}

int main(){
	string input;
	int max,i;

	freopen("lgame.dict","r",stdin);
	cin >> input;
	while(input != "."){
		dict[D++] = input;
		cin >> input;
	}
	fclose(stdin);

	freopen("lgame.in","r",stdin);

	cin >> input;

	int n = input.length();

	for(i = 0;i < n; i++){
		taken[input[i]-'a']++;
	}

	init();
	max = find_pairs();

	printf("%d\n",max);

	for(i = 0; i < S; i++){
		cout << sol[i].first;
		if(sol[i].second != "#"){
			cout << " " << sol[i].second;
		}
		cout << "\n";
	}

	return 0;
}

