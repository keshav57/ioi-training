/*
 Created By: Malvika Joshi
 Problem: WORDHOP
 Link: http://opc.iarcs.org.in/index.php/problems/WORDHOP
*/

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>

using namespace std;


int comp(const void *a, const void *b){
	int d = strlen(*(char**)b) - strlen(*(char**)a);
	if(d != 0) return d;
	return strcmp(*(char**)a, *(char**)b);
}

bool hopr(string a, string b){
	char rep = 0;
	bool seen = false;
	for(int i = 0; a[i]; i++) {
		if(b[i] == rep) seen = true;
		if(a[i] != b[i]){
			if(rep || a[i] > b[i]) return false;
			rep = b[i];
		}
	}
	return seen;
}

bool hopd(string a, string b){
	int i;
	for(i = 0; a[i] == b[i]; i++);
	for(i++; a[i]; i++)
		if(a[i] != b[i-1]) return false;

	return true;
}

int main(){
	int n;
	cin >> n;

	int l[n], f[n], fm;
	string p[n];

	for(int i = 0; i < n; i++) {
		cin >> p[i];
	}

	qsort(p, n, sizeof(string), comp);

	for(int i = 0; i < n; i++)
		l[i] = p[i].length();

	fm = 0;
	for(int i = n-1; i >= 0; i--) {
		f[i] = 1;
		for(int j = i+1; j < n && l[i] - l[j] <= 1; j++) {
			if(((l[i]==l[j] && hopr(p[i], p[j])) || (l[i]==l[j]+1 && hopd(p[i],p[j]))) && f[i] < f[j]+1)
				f[i] = f[j]+1;
		}
		if(f[i] > fm) fm = f[i];
	}

	cout << fm;

	return 0;
}
