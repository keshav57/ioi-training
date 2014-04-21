/*
 Created By: Malvika Joshi
 Problem: msquare
 Link: http://cerberus.delos.com:791/usacoprob2?a=M1sjMcmpoAb&S=msquare
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

string move_a(string str){
	string temp = str;
	int i,j;
	for(i = 0,j = 7;i < 8; i++,j--){
		str[i] = temp[j];
	}
	return str;
}

string move_b(string str){
	string temp = str;
	str[0] = temp[3];
	str[7] = temp[4];
	int i,j;
	for(i = 1,j = 0;i < 7; i++,j++){
		if(j == 3) j+=2;
		str[i] = temp[j];
	}
	return str;
}

string move_c(string str){
	string temp = str;
	str[1] = temp[6];
	str[5] = temp[2];
	int i,j;
	for(i = 0,j = 0; i < 8; i++,j++){
		if(i == 1 || i == 5) i++;
		if(j == 6 || j == 2) j++;
		str[i] = temp[j];
	}
	return str;
}

string Q[50000];
map<string,int > dist;
map<string,string > p;
int H,T;

void bfs(string src,string target){
	string v,i;
	H = 0;
	T = 0;
	Q[T++] = src;
	dist[src] = 0;

	while(H < T){
		v = Q[H++];
		i = move_a(v);
		if(!dist.count(i)){
			dist[i] = dist[v]+1;
			p[i] = p[v];
			p[i].push_back('A');
			Q[T++] = i;
		}

		if(i == target) return;

		i = move_b(v);
		if(!dist.count(i)){
			dist[i] = dist[v]+1;
			p[i] = p[v];
			p[i].push_back('B');
			Q[T++] = i;
		}

		if(i == target) return;

		i = move_c(v);
		if(!dist.count(i)){
			dist[i] = dist[v]+1;
			p[i] = p[v];
			p[i].push_back('C');
			Q[T++] = i;
		}

		if(i == target) return;
	}

}

int main(){
	int i,k;
	string tar,org = "12345678";

	for(i = 0;i < 8; i++){
		scanf("%d",&k);
		tar.push_back(k+'0');
	}

	bfs(org,tar);

	printf("%d\n",dist[tar]);
	cout << p[tar] << "\n";
	return 0;
}
